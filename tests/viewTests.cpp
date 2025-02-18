#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <chrono>
#include <thread>

#include "../include/view.hpp"


int main() {
    auto grid = std::make_shared<view::DrawableGridCanvas>(
        530.f, 1030.f, 21, 41, 5.f);
        
    grid->paintCell({1, 1}, sf::Color::Red);
    grid->paintCell({2, 2}, sf::Color::Red);
    grid->paintCell({3, 3}, sf::Color::Red);
    grid->paintCell({4, 4}, sf::Color::Red);

    auto frame = std::make_shared<view::DrawableFrame>(
        550.f, 1050.f, 5.f, sf::Color::White);

    auto nestedL = std::make_shared<view::DrawableNestedLayout>(10.f, 10.f);
    nestedL->addComponent(frame);
    nestedL->addComponent(grid);
    
    auto stackL = std::make_shared<view::DrawableStackLayout>();
    stackL->addComponent(nestedL);

    auto text = std::make_shared<view::DrawableText>(
        "Your score:", 40, "calibri.ttf", sf::Color::Black, sf::Vector2f(10.f, 0.f));
    stackL->addComponent(text);

    std::pair<unsigned int, unsigned int> sz = stackL->size();
    sf::RenderWindow window(sf::VideoMode({sz.first, sz.second}), "Test Window");
    window.clear(sf::Color::White);
    stackL->draw(window, {0.f, 0.f});
    window.display();
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event && event->is<sf::Event::Closed>()) 
                window.close();
        }
    }
}
