#include <thread>
#include <chrono>
#include <memory>
#include <optional>
#include <mutex>
#include <atomic>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../include/tetromino.hpp"
#include "../include/tetris.hpp"
#include "../include/view.hpp"

using namespace tetris;
using namespace tetrominoes;

std::mutex mut;
std::atomic<bool> isGameRun = true;

int main() {
    using namespace std::chrono_literals;
    sf::RenderWindow window(sf::VideoMode({550, 1050}), "Tetris");
    view::DrawableFramedWindow comp(window, 10, sf::Color::White);

    auto model = std::make_shared<TetrisGameModel>();
    auto drawableField = std::make_shared<view::DrawableTetrisField>(530.f, 1030.f, 5.f, model); 

    comp.pushComponent(drawableField);

    auto modelUpdater = [&] {
        while (window.isOpen()) {
            {
                std::lock_guard<std::mutex> lk{mut};
                isGameRun =  model->update();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200ms));
        }
    };

    std::thread t2(modelUpdater);

    auto handleEvents = [&] {
        using namespace sf::Keyboard;
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>() || !isGameRun) {
                window.close(); 
                exit(0);
            }
            
            if (!event->is<sf::Event::KeyPressed>()) continue;

            auto keyCode = event->getIf<sf::Event::KeyPressed>()->code;

            switch (keyCode) {
                case Key::Left:
                    model->moveLeftCurTetromino();
                    break;
                case Key::Right:
                    model->moveRightCurTetromino();
                    break;
                case Key::Up:
                    model->rotateRightCurTetromino();
                    break;
                case Key::Down:
                    model->update();
                    model->update();
                    model->update();
                    break;
            }

        }   
    };

    while (window.isOpen()) { 
        {   
            std::lock_guard<std::mutex> lk{mut};
            
            handleEvents();

            window.clear();
            comp.draw(window, {0.f, 0.f});
            window.display();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50ms));

    }

    t2.join();

}