#ifndef PLAYER_INPUT_HPP
#define PLAYER_INPUT_HPP

#include <SFML/Window.hpp>

#include "observer-n-subject.hpp"

namespace player_input {

class IPlayerInput : public observer_n_subject::Subject { 
public:
    virtual void pollInput() = 0;
    virtual ~IPlayerInput() { }
};

class KeyBoardInput final : public IPlayerInput {
public:
    KeyBoardInput(std::shared_ptr<sf::RenderWindow> window);

public:
    void pollInput() override;

// Subject methods
public:
    void attach(
        std::shared_ptr<observer_n_subject::Observer> observer, observer_n_subject::EventType event) override;
    void detach(std::shared_ptr<observer_n_subject::Observer> observer) override;

private:
    void notify(observer_n_subject::EventType event) override;

private:

    void fireUserAskedLeft_();
    void fireUserAskedRight_();
    void fireUserAskedDown_();
    void fireUserAskedRotateRight_();
    void fireUserAskedCloseGame_();

private:
    std::shared_ptr<sf::RenderWindow> window_;
};

} // namespace player_input

#endif // PLAYER_INPUT_HPP