#include "include/shapes.hpp"

#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <utility>

namespace shapes {

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
    // TODO: 
    std::unordered_map<int, std::vector<std::pair<int, int>>>
}

void Shape::rotateRigth() {
    setPreShape();
    for (auto& p : m_curShape) {
        std::swap(p.first, p.second);
    }
    reflectShape();
}

} // namespace shapes 