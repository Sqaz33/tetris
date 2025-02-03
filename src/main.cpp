#include <thread>
#include <chrono>
#include <memory>
#include <optional>
#include <mutex>


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../include/tetromino.hpp"
#include "../include/tetris.hpp"
#include "../include/view.hpp"

using namespace tetris;
using namespace tetrominoes;

std::mutex mut;


void dummyKeyboardHendler(std::shared_ptr<TetrisGameModel> model, sf::RenderWindow& window) {
    using namespace sf::Keyboard;
    using namespace std::chrono_literals;
    // while (window.isOpen()) {
        {
            // std::lock_guard<std::mutex> lk{mut};
            if (isKeyPressed(Key::Left)) {
                model->moveLeftCurTetromino();
            } else if (isKeyPressed(Key::Right)) {
                model->moveRightCurTetromino();
            } else if (isKeyPressed(Key::Up)) {
                model->rotateRightCurTetromino();
            } else if (isKeyPressed(Key::Down)) { 
                model->update();
                model->update();
                model->update();
            }
        }
        // std::this_thread::sleep_for(70ms);
    // }
}

int main() {
    using namespace std::chrono_literals;
    sf::RenderWindow window(sf::VideoMode({550, 1050}), "Tetris");
    view::DrawableFramedWindow comp(window, 10, sf::Color::White);

    auto model = std::make_shared<TetrisGameModel>();
    auto drawableField = std::make_shared<view::DrawableTetrisField>(530.f, 1030.f, 5.f, model); 

    comp.pushComponent(drawableField);

    auto closeHandle = [&window] {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            }   
    };


    // std::thread t1(dummyKeyboardHendler, model, std::ref(window));

    auto modelUpdater = [&] {
        while (window.isOpen()) {
            {
                std::lock_guard<std::mutex> lk{mut};
                model->update();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200ms));
        }
    };

    std::thread t2(modelUpdater);


    while (window.isOpen()) { 
        {   
            std::lock_guard<std::mutex> lk{mut};
            closeHandle();
            dummyKeyboardHendler(model, window);
            window.clear();
            comp.draw(window, {0.f, 0.f});
            window.display();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50ms));

    }

    t2.join();

}