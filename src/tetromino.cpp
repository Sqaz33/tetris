#include "../include/tetromino.hpp"

#include <algorithm>
#include <cmath>
#include <random>
#include <unordered_map>
#include <utility>

namespace tetrominoes {

Tetromino::Tetromino(std::initializer_list<Block> shape, TetrominoType type) :
    m_shape(shape)
    , m_greatestSide(INT_MIN)
    , type_(type)
{
    for (const auto& p : shape) {
        m_greatestSide = std::max(m_greatestSide, std::max(p.first + 1, p.second + 1));    
    }
    setShapeBoundaries();
}

const std::vector<Block>& Tetromino::shape() const noexcept {
    return m_shape;
}

TetrominoType Tetromino::type() const {
    return type_;
}

int Tetromino::greatestSide() const {
    return m_greatestSide;
}

int Tetromino::lowestPointOnY() const {
    return m_lowestPointOnY;
}

int Tetromino::highestPointOnY() const {
    return m_highestPointOnY;
}

int Tetromino::leftmostPointOnX() const {
    return m_leftmostPointOnX;
}

int Tetromino::rightmostPointOnX() const {
    return m_rightmostPointOnX;
}
        

void Tetromino::moveDownOneSquare() noexcept {
    for (auto& p : m_shape) {
        ++p.first;
    }
    ++m_lowestPointOnY;
    ++m_highestPointOnY;
}

void Tetromino::moveLeftOneSquare() noexcept {
    for (auto& p : m_shape) {
        --p.second;
    }
    --m_leftmostPointOnX;
    --m_rightmostPointOnX;
}

void Tetromino::moveRightOneSquare() noexcept {
    for (auto& p : m_shape) {
        ++p.second;
    }
    ++m_leftmostPointOnX;
    ++m_rightmostPointOnX;
}

bool Tetromino::containsBlock(Block block) const noexcept {
    for (const auto& p : m_shape) {
        if (block == p) {
            return true;
        }
    }
    return false;
}

void Tetromino::swapShapeAxis() noexcept {
    int x_c = m_leftmostPointOnX, y_c = m_highestPointOnY ;
    int x, y;
    for (auto& p : m_shape) {
        x = p.second - x_c;
        y = p.first - y_c;
        p.second = x_c + y;
        p.first = y_c + x;
    }
}

void Tetromino::setShapeBoundaries() noexcept {  
    m_lowestPointOnY = INT_MIN;
    m_highestPointOnY = INT_MAX;
    m_leftmostPointOnX = INT_MAX;
    m_rightmostPointOnX = INT_MIN;
    for (const auto& p : m_shape) {
        m_lowestPointOnY = std::max(m_lowestPointOnY, p.first);
        m_highestPointOnY = std::min(m_highestPointOnY, p.first);

        m_leftmostPointOnX = std::min(m_leftmostPointOnX, p.second);
        m_rightmostPointOnX = std::max(m_rightmostPointOnX, p.second);
    }   
}

void Tetromino::reflectShape() noexcept {
    for (auto& p : m_shape) {
        p.second = m_rightmostPointOnX + m_leftmostPointOnX - p.second ;
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
    int r = distrib(gen);
    return r == 0 ? create_O_shape() :
           r == 1 ? create_I_shape() :
           r == 2 ? create_S_shape() :
           r == 3 ? create_Z_shape() :
           r == 4 ? create_L_shape() :
           r == 5 ? create_J_shape() :
           r == 6 ? create_T_shape() :
           Tetromino({}, TetrominoType::O);
}

} // namespace shapes 