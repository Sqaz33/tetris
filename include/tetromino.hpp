#ifndef SRC_INCLUDE_TETROMINO_HPP
#define SRC_INCLUDE_TETROMINO_HPP

#include <algorithm>
#include <climits>
#include <initializer_list>
#include <utility>
#include <vector>

namespace tetrominoes {

using Block = std::pair<int, int>;

enum class TetrominoType {
    O, I, S, Z, L, J, T
};

class Tetromino {
public:
    Tetromino(std::initializer_list<Block> shape, TetrominoType type); 

public:
    const std::vector<Block>& shape() const noexcept;
    TetrominoType type() const;

    int greatestSide() const;
    int lowestPointOnY() const;
    int highestPointOnY() const;
    int leftmostPointOnX() const;
    int rightmostPointOnX() const;

    void moveDownOneSquare() noexcept;
    void moveLeftOneSquare() noexcept;
    void moveRightOneSquare() noexcept;

    void rotateRigth() noexcept;

    bool containsBlock(Block block) const noexcept;
private:
    std::vector<Block> m_shape ;
    int m_greatestSide;
    int m_lowestPointOnY;
    int m_leftmostPointOnX;
    int m_rightmostPointOnX;
    int m_highestPointOnY;
    TetrominoType type_;
    
private:
    void swapShapeAxis() noexcept;
    void reflectShape() noexcept;

    void setShapeBoundaries() noexcept;
};

Tetromino create_O_shape();
Tetromino create_I_shape();
Tetromino create_S_shape();
Tetromino create_Z_shape();
Tetromino create_L_shape();
Tetromino create_J_shape();
Tetromino create_T_shape();
Tetromino getRandomTetromino();
 
} // namespace tetrominoes

#endif // SRC_INCLUDE_TETROMINO_HPP