#ifndef TETRIS_GAME_MODEL_HPP
#define TETRIS_GAME_MODEL_HPP

#include <cstddef>
#include <memory>
#include <vector>

#include "observer-n-subject.hpp"

namespace tetris_game_model {

enum class BlockType: std::uint8_t { 
    O = 0, 
    I,
    S, 
    Z, 
    L, 
    J, 
    T,
    VOID,
    GHOST,
};

class TetrisGameModelImpl__;
class TetrisGameModelImplDeleter {
public:
    void operator()(TetrisGameModelImpl__* ptr);
};

class TetrisGameModel final : public observer_n_subject::ISubject {
public:
    TetrisGameModel(std::size_t fieldWidth = 21, std::size_t fieldHeight = 41);

    using field_t = std::vector<std::vector<BlockType>>;
    
public:
    // observer
    void attach(
        std::shared_ptr<observer_n_subject::IObserver> observer, 
        observer_n_subject::EventType event) override;

    void detach(std::shared_ptr<observer_n_subject::IObserver> observer) override;

public:
    // game interaction
    void updateModel();
    const field_t& field() const;
    int score() const;
    std::size_t fieldWidth() const; 
    std::size_t fieldHeight() const;

    bool rotateRightTetromino();     
    bool moveLeftTetromino();
    bool moveRightTetromino();

private:
    std::unique_ptr<TetrisGameModelImpl__, TetrisGameModelImplDeleter> impl_;
};

} // namespace tetris_game_model

#endif // TETRIS_GAME_MODEL_HPP