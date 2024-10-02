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
        m_fieldWidth(width), m_fieldHeight(height)
    {}

public:
    inline const auto& field() const noexcept {
        return m_field;
    } 

    inline size_t fieldWidth() const noexcept {
        return m_fieldWidth;
    }
    
    inline size_t fieldHieght() const noexcept {
        return m_fieldHeight;
    }

    inline size_t score() const noexcept {
        return m_score;
    }

    inline bool hasBlockAt(size_t i, size_t j) const noexcept {
        return m_field[i][j] == blockVal();
    }

    inline bool hasGhostBlockAt(size_t i, size_t j) const noexcept {
        return m_field[i][j] == ghostBlockVal();
    }
    
    static constexpr int voidBlockVal() {
        return 0;
    } 

    static constexpr int blockVal() {
        return 1;
    } 

    static constexpr int ghostBlockVal() {
        return 2;
    } 

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

    inline void setBlockAt(size_t i, size_t j)  ;
    inline void deleteBlockAt(size_t i, size_t j);

    inline void setGhostBlockAt(size_t i, size_t j);
    inline void deleteGhostBlockAt(size_t i, size_t j);

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

