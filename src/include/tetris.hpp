#ifndef SRC_INCLUDE_TETRIS_HPP
#define SRC_INCLUDE_TETRIS_HPP

#include <vector>
#include <memory>

#include "tetromino.hpp"


namespace tetris {

using Line = std::vector<int>;
using TetirsGameField = std::vector<Line>;

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

    bool updateGameField();

    bool rotateRightCurTetromino();
    bool moveLeftCurTetromino() noexcept;
    bool moveRightCurTetromino() noexcept;
protected:
    TetirsGameField m_field;
    size_t fieldWidth, fieldHeight;
    std::unique_ptr<tetrominoes::Tetromino> m_curTetromino;

private:
    bool canMovedDownCurTetromino() const noexcept;
    bool canMovedLeftCurTetromino() const noexcept;
    bool canMovedRightCurTetromino() const noexcept;
 
    bool setNextTetromino();

    void setCurTetrominoOnField() noexcept;    
    void deleteCurTetrominoOnField() noexcept;

    // TODO: rename
    void lower_dummy(size_t start) noexcept;
    void deleteFullLines() noexcept;

};

inline int maxTetrominoSide() { return 4; }

} // namespace tetris


#endif // SRC_INCLUDE_TETRIS_HPP

