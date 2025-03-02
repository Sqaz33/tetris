#include "../include/player-input.hpp"

#include <optional>

#include <SFML/Window.hpp>

namespace player_input {

KeyBoardInput::KeyBoardInput(std::shared_ptr<sf::RenderWindow> window) :
    window_(window)
{}

void KeyBoardInput::pollInput() {
    using namespace sf::Keyboard;
    while (const std::optional event = window_->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            fireUserAskedCloseGame_();
        }
        
        if (!event->is<sf::Event::KeyPressed>()) continue;

        auto keyCode = event->getIf<sf::Event::KeyPressed>()->code;

        switch (keyCode) {
            case Key::Left:
                fireUserAskedLeft_();
                break;
            case Key::Right:
                fireUserAskedRight_();
                break;
            case Key::Up:
                fireUserAskedRotateRight_();
                break;
            case Key::Down:
                fireUserAskedDown_();
                fireUserAskedDown_();
                fireUserAskedDown_();
                break;
            case Key::Tab:
                fireUserAskedPauseGame_();
                break;
        }
    }
}

void KeyBoardInput::fireUserAskedLeft_() {
    notify(observer_n_subject::EventType::USER_ASKED_LEFT);
}

void KeyBoardInput::fireUserAskedRight_() {
    notify(observer_n_subject::EventType::USER_ASKED_RIGHT);
}

void KeyBoardInput::fireUserAskedDown_() {
    notify(observer_n_subject::EventType::USER_ASKED_DOWN);
}

void KeyBoardInput::fireUserAskedRotateRight_() {
    notify(observer_n_subject::EventType::USER_ASKED_ROTATE_RIGHT);
}

void KeyBoardInput::fireUserAskedCloseGame_() {
    notify(observer_n_subject::EventType::USER_ASKED_CLOSE_GAME);
}

void KeyBoardInput::fireUserAskedPauseGame_() {
    notify(observer_n_subject::EventType::USER_ASKED_PAUSE_GAME);
}


} // namespace player_input