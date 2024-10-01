#include "include/tetromino.hpp"

#include <algorithm>
#include <cmath>
#include <random>
#include <unordered_map>
#include <utility>

namespace tetrominoes {

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
    int x_c = m_leftmostPointOnX, y_c = m_highestPointOnY;
    int x, y;
    for (auto& p : m_shape) {
        x = p.second - x_c;
        y = p.first - y_c;
        p.second = x_c + y;
        p.first = y_c + x;
    }
}

void Tetromino::reflectShape() noexcept {
    int relX;
    int maxXLen = m_rightmostPointOnX - m_leftmostPointOnX + 1;
    for (auto& p : m_shape) {
        relX = p.second - m_leftmostPointOnX;
        p.second = m_leftmostPointOnX + maxXLen - relX - 1;
    }
}

void Tetromino::rotateRigth() noexcept {
    swapShapeAxis();
    setShapeBoundaries();
    reflectShape();
}

Tetromino getRandomTetromino() {
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(0, 6);
    int r = distrib(gen);
    return r == 0 ? O_shape() :
           r == 1 ? I_shape() :
           r == 2 ? S_shape() :
           r == 3 ? Z_shape() :
           r == 4 ? L_shape() :
           r == 5 ? J_shape() :
           r == 6 ? T_shape() :
           Tetromino({});
}

} // namespace shapes 