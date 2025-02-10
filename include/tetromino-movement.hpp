#ifndef TETROMINO_MOVEMENT_HPP
#define TETROMINO_MOVEMENT_HPP

#include <cstddef>
#include <utility>
#include <vector>

#include "tetris-game-model.hpp"
#include "tetromino.hpp"


namespace tetromino_movement {

class TetrominoMovement {
public:
    virtual void setField(
        std::shared_ptr<std::vector<std::vector<tetris_game_model::BlockType>>> field
    ) = 0;

    virtual bool rotateRight() = 0;
    virtual bool moveDown() = 0;
    virtual bool moveLeft() = 0;
    virtual bool moveRight() = 0;
    virtual bool setTetromino(tetrominoes::Tetromino tetromino) = 0;

    virtual ~TetrominoMovement() { }

protected:
    std::shared_ptr<std::vector<std::vector<tetris_game_model::BlockType>>> field_;
    tetrominoes::Tetromino curTetromino_;
};

class TetrominoMovementWithGhostTetromino final : public TetrominoMovement {
public:
    void setField(
        std::shared_ptr<std::vector<std::vector<tetris_game_model::BlockType>>> field
    ) override;
    bool rotateRight() override;
    bool moveDown() override;
    bool moveLeft() override;
    bool moveRight() override;
    bool setTetromino(tetrominoes::Tetromino tetromino) override;

private:
    bool canMoveDownTetromino_(const tetrominoes::Tetromino& tetromino) const;
    bool canMoveLeftTetromino_(const tetrominoes::Tetromino& tetromino) const;
    bool canMoveRightTetromino_(const tetrominoes::Tetromino& tetromino) const;
    bool canRotateRightTetromino_(const tetrominoes::Tetromino& tetromino) const; 

    bool fieldHasBlockAt_(std::size_t x, std::size_t y) const;

    void setBlockAt_(std::size_t x, std::size_t y, tetris_game_model::BlockType block);
    void deleteBlockAt_(std::size_t x, std::size_t y);
    void setGhostBlockAt_(std::size_t x, std::size_t y);
    void deleteGhostBlockAt_(std::size_t x, std::size_t y);

    void setCurTetrominoOnField_();    
    void deleteCurTetrominoOnField_();

    void setCurTetrominoGhostOnField_();
    void deleteCurTetrominoGhostOnField_();

    void updateTetrominoGhost_();

    std::size_t fieldWidth_() const; 
    std::size_t fieldHeight_() const;

private:
    tetrominoes::Tetromino curTetrominoGhost_;

};

} // namespace tetromino_movement 



#endif // TETROMINO_MOVEMENT_HPP
