#include <atomic>
#include <chrono>
#include <memory>
#include <mutex>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../include/player-input.hpp"
#include "../include/tetris-game-controller.hpp"
#include "../include/tetris-game-model.hpp"
#include "../include/view.hpp"

int main() {
    using namespace std::chrono_literals;

    auto grid = std::make_shared<view::DrawableGridCanvas>(
        530.f, 1030.f, 21, 41, 5.f);
    auto frame = std::make_shared<view::DrawableFrame>(
        550.f, 1050.f, 5.f, sf::Color::White);

    auto nestedL = std::make_shared<view::DrawableNestedLayout>(10.f, 10.f);
    nestedL->addComponent(frame);
    nestedL->addComponent(grid);

    
    auto text = std::make_shared<view::DrawableText>(
        "Your score:", 40, "calibri.ttf", sf::Color::Black, sf::Vector2f(10.f, 0.f));

    auto stackL = std::make_shared<view::DrawableStackLayout>();
    stackL->addComponent(nestedL);
    stackL->addComponent(text);
    
    std::pair<unsigned, unsigned> windowSz = stackL->size();
    auto window = std::make_shared<sf::RenderWindow>(
            sf::VideoMode({windowSz.first, windowSz.second}), "Tetris");

    auto model = std::make_shared<TetrisGameModel>();

    auto input = std::make_shared<player_input::KeyBoardInput>(window);

    auto controller 
        = std::make_shared<tetris_game_controller::TetrisGameController>(model, input, window, text, grid, stackL);
    controller->registerAsObserver();

    std::atomic_bool isGameRun = true;
    std::atomic_bool isGamePause = false;
    std::mutex modelMut;

    auto modelUpdater = [&] {
        while (isGameRun) {
            {
                std::lock_guard<std::mutex> lk{modelMut};
                model->updateModel();
            }
            std::this_thread::sleep_for(200ms);

            while (isGamePause && isGameRun)
                std::this_thread::yield(); 
        };
    };

    std::thread t1(modelUpdater);
    model->updateModel();


    controller->runModel(modelMut, isGameRun, isGamePause);

    t1.join();
}