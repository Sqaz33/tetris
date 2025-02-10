#include "../include/tetris-game-model.hpp"

#include <memory>

#include "../include/tetromino-movement.hpp"
#include "../include/score-strategy.hpp"

using observer_n_subject::Observer;
using observer_n_subject::Subject;
using observer_n_subject::EventType;

namespace tetris_game_model {

// ##################################################
// TetrisGameModelImpl
class TetrisGameModelImpl__ : public observer_n_subject::Subject { 
public:
    TetrisGameModelImpl__(
        std::size_t fieldWidth, std::size_t fieldHeight,
        std::unique_ptr<tetromino_movement::TetrominoMovement> movement,
        std::unique_ptr<score_strategy::ScoreStrategy> scoreStrategy);

    using field_ptr_t = std::shared_ptr<std::vector<std::vector<BlockType>>>;

public:
    void attach(
        std::shared_ptr<observer_n_subject::Observer> observer, 
        observer_n_subject::EventType event) override;

    void detach(std::shared_ptr<observer_n_subject::Observer> observer) override;

public:
    void updateModel();

    const field_ptr_t field() const;
    int score() const;
    std::size_t fieldWidth() const; 
    std::size_t fieldHeight() const;

    bool rotateRightTetromino();     
    bool moveLeftTetromino();
    bool moveRightTetromino();

private:
    void notify(observer_n_subject::EventType event) override;
    
    void fireFieldUpdate_();
    void fireScoreUpdate_();
    void fireGameFinish_();

private:
    field_ptr_t field_;
    int score_;
    std::unique_ptr<tetromino_movement::TetrominoMovement> movement_;
    std::unique_ptr<score_strategy::ScoreStrategy> scoreStrategy_;
};


// definitions
TetrisGameModelImpl__::TetrisGameModelImpl__(
    std::size_t fieldWidth, std::size_t fieldHeight,
    std::unique_ptr<tetromino_movement::TetrominoMovement> movement,
    std::unique_ptr<score_strategy::ScoreStrategy> scoreStrategy) {
    movement_ = std::move(movement);
    scoreStrategy_ = std::move(scoreStrategy);
    field_ = std::make_shared<std::vector<std::vector<BlockType>>>(
        fieldHeight, std::vector<BlockType>(fieldWidth, BlockType::VOID));
}

// observer defs
void TetrisGameModelImpl__::attach(
    std::shared_ptr<observer_n_subject::Observer> observer, 
    observer_n_subject::EventType event) {
        Subject::attach(observer, event);
}   

void TetrisGameModelImpl__::detach(std::shared_ptr<observer_n_subject::Observer> observer) {
    Subject::detach(observer);
}

void TetrisGameModelImpl__::notify(observer_n_subject::EventType event) {
    Subject::notify(event);
}

void TetrisGameModelImpl__::updateModel() {
    if (movement_->moveDown()) {

    }
}

const TetrisGameModelImpl__::field_ptr_t TetrisGameModelImpl__::field() const {
    return field_;
}

int TetrisGameModelImpl__::score() const {
    return score_;
}

std::size_t TetrisGameModelImpl__::fieldWidth() const {
    return field_->at(0).size();
} 
std::size_t TetrisGameModelImpl__::fieldHeight() const {
    return field_->size();
}


void TetrisGameModelImpl__::fireFieldUpdate_() {
    notify(observer_n_subject::EventType::GAME_FIELD_UPDATE);
}

void TetrisGameModelImpl__::fireScoreUpdate_() {
    notify(observer_n_subject::EventType::GAME_SCORE_UPDATE);
}

void TetrisGameModelImpl__::fireGameFinish_() {
    notify(observer_n_subject::EventType::GAME_FINISH);
}


// ##################################################
// TetrisGameModelImplDeleter
void TetrisGameModelImplDeleter::operator()(TetrisGameModelImpl__* ptr) {
    ptr->~TetrisGameModelImpl__();
} 


// ##################################################
// TetrisGameModel
TetrisGameModel::TetrisGameModel(std::size_t fieldWidth, std::size_t fieldHeight) 
    : impl_(new TetrisGameModelImpl__(
        fieldWidth, fieldHeight,
        std::unique_ptr(new tetromino_movement::TetrominoMovementWithGhostTetromino()),
        std::unique_ptr
        new score_strategy::DoubleScorePerLineStrategy()
    ))
{}

void TetrisGameModel::attach(std::shared_ptr<Observer> observer, EventType event) {
    impl_->attach(observer, event);
}

void TetrisGameModel::detach(std::shared_ptr<Observer> observer) {
    impl_->detach(observer);
}

// TODO: empty def?
void TetrisGameModel::notify(EventType event) { }

const TetrisGameModel::field_ptr_t TetrisGameModel::field() const {
    return impl_->field();
}

void TetrisGameModel::updateModel() {
    impl_->updateModel();
}

int TetrisGameModel::score() const {
    return impl_->score();
}

std::size_t TetrisGameModel::fieldWidth() const {
    return impl_->fieldWidth();
} 
std::size_t TetrisGameModel::fieldHeight() const {
    return impl_->fieldHeight();
}

bool TetrisGameModel::rotateRightTetromino() {
    return impl_->rotateRightTetromino();
}

bool TetrisGameModel::moveLeftTetromino() {
    return impl_->moveLeftTetromino();
}

bool TetrisGameModel::moveRightTetromino() {
    return impl_->moveRightTetromino();
}

} // namespace tetris_game_model 
