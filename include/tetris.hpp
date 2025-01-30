#ifndef SRC_INCLUDE_TETRIS_HPP
#define SRC_INCLUDE_TETRIS_HPP

#include <vector>
#include <memory>
#include <cstddef>

#include "tetromino.hpp"

namespace tetris {

enum class BlockType : std::uint8_t {
    FILLED = 0,
    VOID,
    GHOST
};

using Line = std::vector<BlockType>;
using TetrisGameField = std::vector<Line>;

class Tetris {
public:
    Tetris(size_t width = 21, size_t height = 41);

public:
    const TetrisGameField& field() const noexcept;
    size_t fieldWidth() const noexcept;
    size_t fieldHieght() const noexcept;
    size_t score() const noexcept;
    bool hasBlockAt(size_t i, size_t j) const noexcept;
    bool hasGhostBlockAt(size_t i, size_t j) const noexcept;
    

    bool updateGameField();

    bool rotateRightCurTetromino();
    bool moveLeftCurTetromino();
    bool moveRightCurTetromino();

protected:

    TetrisGameField m_field;
    size_t m_fieldWidth, m_fieldHeight;
    std::unique_ptr<tetrominoes::Tetromino> m_curTetromino;
    std::unique_ptr<tetrominoes::Tetromino> m_curTetrominoGhost;

    int linesDestroyed = 0;
    size_t m_score = 0;

private:
    bool canMovedDownTetromino(const tetrominoes::Tetromino& tetromino) const;
    bool canMovedLeftTetromino(const tetrominoes::Tetromino& tetromino) const;
    bool canMovedRightTetromino(const tetrominoes::Tetromino& tetromino) const;
    bool canRotateRightTetromino(const tetrominoes::Tetromino& tetromino) const; 
 
    bool setNextTetromino();

    void setBlockAt(size_t i, size_t j)  ;
    void deleteBlockAt(size_t i, size_t j);

    void setGhostBlockAt(size_t i, size_t j);
    void deleteGhostBlockAt(size_t i, size_t j);

    void setCurTetrominoOnField();    
    void deleteCurTetrominoOnField();

    void setCurTetrominoGhostOnField();
    void deleteCurTetrominoGhostOnField();

    void lowerAllLinesUnder(size_t start);
    void deleteFullLines();

    void updateScore() noexcept;
};

} // namespace tetris

#endif // SRC_INCLUDE_TETRIS_HPP

