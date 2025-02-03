#include <thread>
#include <chrono>
#include <memory>
#include <optional>

#include <SFML/Window.hpp>


#include "../include/tetromino.hpp"
#include "../include/tetris.hpp"
#include "../include/view.hpp"

using namespace tetris;
using namespace tetrominoes;



int main() {

    sf::RenderWindow window(sf::VideoMode({550, 1050}), "Tetris");
    view::DrawableFramedWindow comp(window, 10, sf::Color::White);

    auto model = std::make_shared<TetrisGameModel>();
    auto drawableField = std::make_shared<view::DrawableTetrisField>(530.f, 1030.f, 5.f, model); 

    comp.pushComponent(drawableField);

    window.clear();
    comp.draw(window, {0.f, 0.f});
    window.display();


    auto closeHandle = [&window] {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            }   
    };
    model->update();
    model->update();
    model->update();
    model->update();

    while (window.isOpen()) { 
        closeHandle();
        window.clear();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        comp.draw(window, {0.f, 0.f});
        window.display();
    }

}