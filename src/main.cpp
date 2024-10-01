#include <iostream>
#include <vector>
#include <string>

// TODO: когда-нибудь перделать всю хрень

#include <termios.h>
#include <unistd.h>

#include "include/tetromino.hpp"
#include "include/tetris.hpp"

using namespace tetris;
using namespace tetrominoes;

namespace {

void setTerminalMode(bool enable)
{
    static struct termios oldt, newt;
    if (enable)
    {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    else
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}


void printField(const TetrisGameField& field, size_t score) {
    // clearScreen();
    std::cout << std::string(field.size(), '\n');
    std::cout << "Your score: " << score << '\n';
    std::cout << std::string(field[0].size() * 2 - 1, '-') << '\n';
    for (const auto& row : field) {
        for (const auto& n : row) {
            std::cout << (n == 1 ? '@' : n == 2 ? '#' : '\'') << ' '; 
        }
        std::cout << '\n';
    }
}



} // namespace

int main() {
    Tetris tetris;
    char c;
    setTerminalMode(true);

    std::cout << "Press arrow keys (ESC to quit):\n";
    while (tetris.updateGameField())
    {
        c = getchar();
        if (c == '\033') // ESC
        {
            getchar();    // Skip [
            switch (getchar())
            {
            case 'A':
                tetris.rotateRightCurTetromino();
                break;
            case 'B':
                tetris.updateGameField();
                printField(tetris.gameField(), tetris.score());
                break;
            case 'C':
                tetris.moveRightCurTetromino();
                break;
            case 'D':
                tetris.moveLeftCurTetromino();
                break;
            }
        }
        else if (c == 'q') // Press 'q' to quit
        {
            break;
        }
        printField(tetris.gameField(), tetris.score());
    }

    setTerminalMode(false);
    std::cout << "Game Over!\n";
    return 0;
}
