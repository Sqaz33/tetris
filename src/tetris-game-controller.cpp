#include "../include/tetris-game-controller.hpp"

#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>
#include <cassert>

namespace tetris_game_controller {

TetrisGameController::TetrisGameController(
    std::shared_ptr<tetris_game_model::TetrisGameModel> gameModel,
    std::shared_ptr<player_input::IPlayerInput> playerInput,
    std::shared_ptr<sf::RenderWindow> window,
    std::shared_ptr<view::IDrawableComposite> compositeView) :
    gameModel_(gameModel)
    , playerInput_(playerInput)
    , window_(window)
    , compositeView_(compositeView)
{ updateScoreView_(); }

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
    playerInput_->attach(getThis(), EventType::USER_ASKED_PAUSE_GAME);
}

void TetrisGameController::runModel(
    std::mutex& modelMut, std::atomic_bool& isGameRun, std::atomic_bool& isGamePause) {
    gameLoop_(modelMut, isGameRun, isGamePause);
} 

std::shared_ptr<TetrisGameController> TetrisGameController::getThis() {
    return shared_from_this();
}

void TetrisGameController::gameLoop_(
    std::mutex& modelMut, std::atomic_bool& isGameRun, std::atomic_bool& isGamePause) {
    observer_n_subject::EventType event;
    while (isGameRun) {
        while (!eventQueue_.tryPop(event)) {
            playerInput_->pollInput();
            std::this_thread::yield();
        }
        handleEvent_(modelMut, isGameRun, isGamePause, event);
    }
}

void TetrisGameController::handleEvent_(
    std::mutex& modelMut, std::atomic_bool& isGameRun, 
    std::atomic_bool& isGamePause, observer_n_subject::EventType event) {
    using namespace observer_n_subject;
    switch (event) {
        case EventType::GAME_FIELD_UPDATE: {
            std::lock_guard<std::mutex> lk{modelMut};
            updateFieldView_();
            redrawWindowNDisplay_();
            break;
        } 
        case EventType::GAME_SCORE_UPDATE: {
            std::lock_guard<std::mutex> lk{modelMut};
            updateScoreView_();
            redrawWindowNDisplay_();
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
        case EventType::USER_ASKED_PAUSE_GAME: {
            isGamePause = !isGamePause;
            break;
        }
    }
}

void TetrisGameController::updateScoreView_() {
    std::stringstream ss;
    ss << "Your Score: ";
    ss << gameModel_->score();
    auto textView = std::dynamic_pointer_cast<view::DrawableText>(
        compositeView_->getComponent("score_text")
    );
    assert(textView);
    textView->setText(ss.str());
}

void TetrisGameController::updateFieldView_() {
    auto fieldView = std::dynamic_pointer_cast<view::DrawableGridCanvas>(
        compositeView_->getComponent("grid")
    );
    assert(fieldView);
    fieldView->clear();
    decltype(auto) field = gameModel_->field();
    for (std::size_t i = 0; i < gameModel_->fieldHeight(); ++i) {
        for (std::size_t j = 0; j < gameModel_->fieldWidth(); ++j) {
            auto color = tetrominoBlockColor_(field[i][j]);
            fieldView->paintCell({j, i}, color);
        }
    }
}

void TetrisGameController::redrawWindowNDisplay_() {
    window_->clear(sf::Color::White);
    compositeView_->draw(*window_, {0, 0});
    window_->display();
}

sf::Color TetrisGameController::tetrominoBlockColor_(tetris_game_model::BlockType block) const {
    using namespace tetris_game_model;
    switch (block) {
        case BlockType::O: return sf::Color::Blue;
        case BlockType::I: return sf::Color::Cyan;
        case BlockType::S: return sf::Color::Green;
        case BlockType::Z: return sf::Color::Magenta;
        case BlockType::L: return sf::Color::Red;
        case BlockType::J: return sf::Color(128, 0, 128); // Фиолетовый
        case BlockType::T: return sf::Color(255, 127, 80); // Коралловый
        case BlockType::VOID: return sf::Color::White;
        default: return sf::Color(128, 128, 128); // Серый
    }
}


void TetrisGameController::update(
    observer_n_subject::ISubject& subject, observer_n_subject::EventType event) {
    eventQueue_.push(event);
}

} // namespace tetris_game_controller