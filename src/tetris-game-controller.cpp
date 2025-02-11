#include "../include/tetris-game-controller.hpp"

#include <thread>
#include <iostream>
#include <chrono>

namespace tetris_game_controller {

TetrisGameController::TetrisGameController(
    std::shared_ptr<tetris_game_model::TetrisGameModel> gameModel,
    std::shared_ptr<player_input::IPlayerInput> playerInput,
    std::shared_ptr<sf::RenderWindow> window,
    std::shared_ptr<view::IDrawable> view) :
    gameModel_(gameModel)
    , playerInput_(playerInput)
    , window_(window)
    , view_(view)
{}

void TetrisGameController::registerAsObserver() {
    using namespace observer_n_subject;

    gameModel_->attach(getThis(), EventType::GAME_FIELD_UPDATE);
    gameModel_->attach(getThis(), EventType::GAME_SCORE_UPDATE);
    gameModel_->attach(getThis(), EventType::GAME_FINISH);

    playerInput_->attach(getThis(), EventType::USER_ASKED_LEFT);
    playerInput_->attach(getThis(), EventType::USER_ASKED_RIGHT);
    playerInput_->attach(getThis(), EventType::USER_ASKED_DOWN);
    playerInput_->attach(getThis(), EventType::USER_ASKED_ROTATE_RIGHT);
    playerInput_->attach(getThis(), EventType::USER_ASKED_CLOSE_GAME);
}

void TetrisGameController::runModel(std::mutex& modelMut, std::atomic_bool& isGameRun) {
    gameLoop_(modelMut, isGameRun);
} 

std::shared_ptr<TetrisGameController> TetrisGameController::getThis() {
    return shared_from_this();
}

void TetrisGameController::gameLoop_(std::mutex& modelMut, std::atomic_bool& isGameRun) {
    observer_n_subject::EventType event;
    while (isGameRun) {
        while (!eventQueue_.tryPop(event)) {
            playerInput_->pollInput();
            std::this_thread::yield();
        }
        handleEvent_(modelMut, isGameRun, event);
    }
}

void TetrisGameController::handleEvent_(
    std::mutex& modelMut, std::atomic_bool& isGameRun, observer_n_subject::EventType event) {
    using namespace observer_n_subject;
    switch (event) {
        case EventType::GAME_FIELD_UPDATE: {
            std::lock_guard<std::mutex> lk{modelMut};
            window_->clear();
            view_->draw(*window_, {0, 0});
            window_->display();
            break;
        } 
        case EventType::GAME_SCORE_UPDATE: {
            std::lock_guard<std::mutex> lk{modelMut};
            std::cout << "Your score: " << gameModel_->score() << '\n';
            break;
        }
        case EventType::GAME_FINISH: {
            isGameRun = false;
            break;
        } 
        case EventType::USER_ASKED_LEFT: {
            std::lock_guard<std::mutex> lk{modelMut};
            gameModel_->moveLeftTetromino();
            break;
        } 
        case EventType::USER_ASKED_RIGHT: {
            std::lock_guard<std::mutex> lk{modelMut};
            gameModel_->moveRightTetromino();
            break;
        } 
        case EventType::USER_ASKED_DOWN: {
            std::lock_guard<std::mutex> lk{modelMut};
            gameModel_->updateModel();
            break;
        }
        case EventType::USER_ASKED_ROTATE_RIGHT: {
            std::lock_guard<std::mutex> lk{modelMut};
            gameModel_->rotateRightTetromino();
            break;
        } 
        case EventType::USER_ASKED_CLOSE_GAME: {
            std::lock_guard<std::mutex> lk{modelMut};
            isGameRun = false;
            break;
        }   
    }
}

void TetrisGameController::update(
    observer_n_subject::Subject& subject, observer_n_subject::EventType event) {
    eventQueue_.push(event);
}

} // namespace tetris_game_controller