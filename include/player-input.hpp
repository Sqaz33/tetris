#ifndef PLAYER_INPUT_HPP
#define PLAYER_INPUT_HPP

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "observer-n-subject.hpp"

namespace player_input {

class IPlayerInput : public observer_n_subject::SubjectImpl { 
public:
    virtual void pollInput() = 0;
    virtual ~IPlayerInput() { }
};

class KeyBoardInput final : public IPlayerInput {
public:
    KeyBoardInput(std::shared_ptr<sf::RenderWindow> window);

public:
    void pollInput() override;

private:

    void fireUserAskedLeft_();
    void fireUserAskedRight_();
    void fireUserAskedDown_();
    void fireUserAskedRotateRight_();
    void fireUserAskedCloseGame_();
    void fireUserAskedPauseGame_();

private:
    std::shared_ptr<sf::RenderWindow> window_;
};

} // namespace player_input

#endif // PLAYER_INPUT_HPP