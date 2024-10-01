#ifndef SRC_INCLUDE_TETRIS_HPP
#define SRC_INCLUDE_TETRIS_HPP

#include <vector>
#include <memory>

#include "tetromino.hpp"


namespace tetris {

using Line = std::vector<int>;
using TetrisGameField = std::vector<Line>;

class Tetris {
public:
    Tetris(size_t width = 21, size_t height = 41) :
        m_field(height, Line(width, 0)),
        fieldWidth(width), fieldHeight(height)
    {}

public:
    inline const auto& gameField() const noexcept {
        return m_field;
    } 

    inline size_t gameFieldWidth() const noexcept {
        return fieldWidth;
    }
    
    inline size_t gameFieldHieght() const noexcept {
        return fieldHeight;
    }

    inline bool hasBlockAt(size_t x, size_t y) const noexcept {
        return m_field[x][y] == 1;
    }

    inline size_t score() const noexcept {
        return m_score;
    }

    bool updateGameField();

    bool rotateRightCurTetromino();
    bool moveLeftCurTetromino() noexcept;
    bool moveRightCurTetromino() noexcept;
protected:
    TetrisGameField m_field;
    size_t fieldWidth, fieldHeight;
    std::unique_ptr<tetrominoes::Tetromino> m_curTetromino;
    std::unique_ptr<tetrominoes::Tetromino> m_curTetrominoGhost;
    int lineDestroy = 0;
    size_t m_score = 0;


private:
    bool canMovedDownCurTetromino() const noexcept;
    bool canMovedLeftCurTetromino() const noexcept;
    bool canMovedRightCurTetromino() const noexcept;
 
    bool setNextTetromino();

    void setCurTetrominoOnField() noexcept;    
    void deleteCurTetrominoOnField() noexcept;
    void setCurTetrominoGhostOnField() noexcept;
    void deleteCurTetrominoGhostOnField() noexcept;

    void lowerAllLinesUnder(size_t start) noexcept;
    void deleteFullLines() noexcept;

    void updateScore();

};

inline int maxTetrominoSide() { return 4; }

} // namespace tetris


#endif // SRC_INCLUDE_TETRIS_HPP

