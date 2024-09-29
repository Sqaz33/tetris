#include <iostream>
#include <vector>

#include "include/shapes.hpp"

using namespace shapes;

namespace {
using Row = std::vector<int>;
using Field = std::vector<Row>;

void printField(const Field& field) {
    for (const auto& row : field) {
        for (const auto& n : row) {
            std::cout << (n ? '@' : '\'') << ' '; 
        }
        std::cout << '\n';
    }
    std::cout << "--------------------------------------------\n";
}

void setShapeAtField(Field& field, const Shape& shape) {
    for (const auto& p : shape.currentShape()) {
        field[p.first][p.second] = 1;
    }
}

void clearShapeAtField(Field& field, const Shape& shape) {
    for (const auto& p : shape.previouShape()) {
        field[p.first][p.second] = 0;
    }
}


} // namespace

int main() {
    Field field(42, Row(21, 0));
    L_shape L;

    for (int i = 0; i < 10; ++i) {
        L.moveRightOneSquare();
        L.moveDownOneSquare();
    }
    setShapeAtField(field, L);
    printField(field);

    L.rotateRigth();
    clearShapeAtField(field, L);
    setShapeAtField(field, L);
    printField(field);
}