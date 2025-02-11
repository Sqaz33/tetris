#include "../include/tetromino.hpp"

#include <algorithm>
#include <cmath>
#include <random>
#include <unordered_map>
#include <utility>

namespace tetrominoes {

Tetromino::Tetromino(std::initializer_list<Block> shape, TetrominoType type) :
    shape_(shape)
    , greatestSide_(INT_MIN)
    , type_(type)
{
    for (const auto& p : shape) {
        greatestSide_ = std::max(greatestSide_, std::max(p.first + 1, p.second + 1));    
    }
    setShapeBoundaries();
}

const std::vector<Block>& Tetromino::shape() const noexcept {
    return shape_;
}

TetrominoType Tetromino::type() const {
    return type_;
}

int Tetromino::greatestSide() const {
    return greatestSide_;
}

int Tetromino::lowestPointOnY() const {
    return lowestPointOnY_;
}

int Tetromino::highestPointOnY() const {
    return highestPointOnY_;
}

int Tetromino::leftmostPointOnX() const {
    return leftmostPointOnX_;
}

int Tetromino::rightmostPointOnX() const {
    return rightmostPointOnX_;
}
        
void Tetromino::moveDownOneSquare() noexcept {
    for (auto& p : shape_) {
        ++p.second;
    }
    ++lowestPointOnY_;
    ++highestPointOnY_;
}

void Tetromino::moveLeftOneSquare() noexcept {
    for (auto& p : shape_) {
        --p.first;
    }
    --leftmostPointOnX_;
    --rightmostPointOnX_;
}

void Tetromino::moveRightOneSquare() noexcept {
    for (auto& p : shape_) {
        ++p.first;
    }
    ++leftmostPointOnX_;
    ++rightmostPointOnX_;
}

bool Tetromino::containsBlock(Block block) const noexcept {
    for (const auto& p : shape_) {
        if (block == p) {
            return true;
        }
    }
    return false;
}

void Tetromino::swapShapeAxis() noexcept {
    int x_c = leftmostPointOnX_, y_c = highestPointOnY_ ;
    int x, y;
    for (auto& p : shape_) {
        x = p.first - x_c;
        y = p.second - y_c;
        p.first = x_c + y;
        p.second = y_c + x;
    }
}

void Tetromino::setShapeBoundaries() noexcept {  
    lowestPointOnY_ = INT_MIN;
    highestPointOnY_ = INT_MAX;
    leftmostPointOnX_ = INT_MAX;
    rightmostPointOnX_ = INT_MIN;
    for (const auto& p : shape_) {
        lowestPointOnY_ = std::max(lowestPointOnY_, p.second);
        highestPointOnY_ = std::min(highestPointOnY_, p.second);

        leftmostPointOnX_ = std::min(leftmostPointOnX_, p.first);
        rightmostPointOnX_ = std::max(rightmostPointOnX_, p.first);
    }   
}

void Tetromino::reflectShape() noexcept {
    for (auto& p : shape_) {
        p.first = rightmostPointOnX_ + leftmostPointOnX_ - p.first ;
    }
}

void Tetromino::rotateRigth() noexcept {
    swapShapeAxis();
    setShapeBoundaries();
    reflectShape();
}

Tetromino create_O_shape() {
    return Tetromino(
            {
                {0, 0}, {0, 1},
                {1, 0}, {1, 1}
            },
            TetrominoType::O);
}

Tetromino create_I_shape() {
    return Tetromino(
            {
                {0, 0},
                {1, 0},
                {2, 0},
                {3, 0}
            },
            TetrominoType::I);
}

Tetromino create_S_shape() {
    return Tetromino(
            {           {0, 1}, {0, 2},
                {1, 0}, {1, 1}
            },
            TetrominoType::S);
}

Tetromino create_Z_shape() {
    return Tetromino(
            {
                {0, 0}, {0, 1},
                        {1, 1}, {1, 2}
            },
            TetrominoType::Z);
}

Tetromino create_L_shape() {
    return Tetromino(
            {
                {0, 0},
                {1, 0},
                {2, 0}, {2, 1}
            },
            TetrominoType::L);
}

Tetromino create_J_shape() {
    return Tetromino(
            {
                        {0, 1},
                        {1, 1},
                {2, 0}, {2, 1} 
            },
            TetrominoType::J);
}

Tetromino create_T_shape() {
    return Tetromino(
            {
                {0, 0}, {0, 1}, {0, 2},
                        {1, 1} 
            },
            TetrominoType::T);
}

Tetromino getRandomTetromino() {
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(0, 6);
    return create_I_shape();
    int r = distrib(gen);
    switch (r) {
        case 0: 
            return create_O_shape();
            break;
        case 1:
            return create_I_shape();
            break;
        case 2:
            return create_S_shape();
            break;
        case 3:
            return create_Z_shape();
            break;
        case 4:
            return create_L_shape();
            break;
        case 5:
            return create_J_shape();
            break;
        case 6:
            return create_T_shape();
            break;
    }
}

} // namespace shapes 