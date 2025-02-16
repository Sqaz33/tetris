#ifndef TETRIS_GAME_CONTROLLER_HPP
#define TETRIS_GAME_CONTROLLER_HPP

#include <atomic>
#include <memory>
#include <mutex>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "lock-based-queue.hpp"
#include "observer-n-subject.hpp"
#include "player-input.hpp"
#include "tetris-game-model.hpp"
#include "view.hpp"

namespace tetris_game_controller {

class TetrisGameController : public observer_n_subject::IObserver,  
                             public std::enable_shared_from_this<TetrisGameController> {
public:
    TetrisGameController(
        std::shared_ptr<tetris_game_model::TetrisGameModel> gameModel,
        std::shared_ptr<player_input::IPlayerInput> playerInput,
        std::shared_ptr<sf::RenderWindow> window,
        std::shared_ptr<view::IDrawable> view);

    void registerAsObserver();
    void runModel(std::mutex& modelMut, std::atomic_bool& isGameRun, std::atomic_bool& isGamePause);
    std::shared_ptr<TetrisGameController> getThis();
    
private:
    void gameLoop_(std::mutex& modelMut, std::atomic_bool& isGameRun, std::atomic_bool& isGamePause);
    void handleEvent_(
        std::mutex& modelMut, std::atomic_bool& isGameRun, 
        std::atomic_bool& isGamePause,  observer_n_subject::EventType event);

//observer
public:
    void update(
        observer_n_subject::ISubject& subject, observer_n_subject::EventType event) override;
        
private:
    std::shared_ptr<tetris_game_model::TetrisGameModel> gameModel_;
    std::shared_ptr<player_input::IPlayerInput> playerInput_;
    lock_based_queue::LockBasedQueue<observer_n_subject::EventType> eventQueue_;
    std::shared_ptr<sf::RenderWindow> window_;
    std::shared_ptr<view::IDrawable> view_;
}; 

} // namespace tetris_game_controller

#endif 