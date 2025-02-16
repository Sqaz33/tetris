#ifndef SRC_INCLUDE_TETROMINO_HPP
#define SRC_INCLUDE_TETROMINO_HPP

#include <algorithm>
#include <cstddef>
#include <climits>
#include <initializer_list>
#include <utility>
#include <vector>
#include <cstdint>

namespace tetrominoes {

using Block = std::pair<int, int>;

enum class TetrominoType : std::uint8_t;
enum class TetrominoType : std::uint8_t {
    O = 0, I, S, Z, L, J, T
};

class Tetromino {
public:
    Tetromino(std::initializer_list<Block> shape, TetrominoType type); 
    Tetromino() = default;

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
    void swapShapeAxis_() noexcept;
    void reflectShape_() noexcept;
    void setShapeBoundaries_() noexcept;

private:
    std::vector<Block> shape_ ;
    int greatestSide_;
    int lowestPointOnY_;
    int leftmostPointOnX_;
    int rightmostPointOnX_;
    int highestPointOnY_;
    TetrominoType type_;
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