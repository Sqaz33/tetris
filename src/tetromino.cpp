#include "include/shapes.hpp"

#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <utility>

namespace tetrominoes {

void Shape::moveDownOneSquare() {
    setPreShape();
    for (auto& p : m_curShape) {
        ++p.first;
    }
}

void Shape::moveLeftOneSquare() {
    setPreShape();
    for (auto& p : m_curShape) {
        --p.second;
    }
}

void Shape::moveRightOneSquare() {
    setPreShape();
    for (auto& p : m_curShape) {
        ++p.second;
    }
}

void Shape::reflectShape() {
    std::unordered_map<int, std::vector<std::pair<int, int>>> lines;
    for (auto& )
}

void Shape::rotateRigth() {
    setPreShape();
    for (auto& p : m_curShape) {
        std::swap(p.first, p.second);
    }
    reflectShape();
}

} // namespace shapes 