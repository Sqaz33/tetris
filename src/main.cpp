#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <string>

#include "include/tetromino.hpp"
#include "include/tetris.hpp"

using namespace tetris;
using namespace tetrominoes;

namespace {

void printField(const TetirsGameField& field) {
    std::cout << std::string(field.size(), '\n');
    for (const auto& row : field) {
        for (const auto& n : row) {
            std::cout << (n ? '@' : '\'') << ' '; 
        }
        std::cout << '\n';
    }
    // std::cout << "--------------------------------------------\n";
}


} // namespace

int main() {
    Tetris tetris;
    bool f = true;
    while (tetris.updateGameField()) {
        printField(tetris.gameField());
        f = f ? tetris.moveRightCurTetromino() : !tetris.moveLeftCurTetromino();
        tetris.rotateRightCurTetromino();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
