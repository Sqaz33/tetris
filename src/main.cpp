#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

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


void printGame(const Tetris& tetris) {
    // clearScreen();
    std::cout << std::string(tetris.gameFieldHieght(), '\n');
    std::cout << "Your score: " << tetris.score() << '\n';
    std::cout << std::string(tetris.gameFieldWidth() * 2 - 1, '-') << '\n';
    for (const auto& row : tetris.gameField()) {
        for (const auto& n : row) {
            std::cout << (n == 1 ? '@' : n == 2 ? '#' : '\'') << ' '; 
        }
        std::cout << '\n';
    }
}

Tetris tetris;
bool running = true;
std::mutex mtx;

void input() {
    char c;
    setTerminalMode(true);
    std::cout << "Press arrow keys:\n";
    while (true)
    {
        c = getchar();
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (!running) break;  // Поток завершится, если running == false
        }

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
        printGame(tetris);
    }
    setTerminalMode(false);
}

void updater() {
    while (true) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (!running) break;  // Остановка потока
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        running = tetris.updateGameField();
        printGame(tetris);
    } 
}

} // namespace


int main() {
    std::thread game(updater);
    std::thread in(input);
    game.join();
    in.join();

    std::cout << "Game Over!\n";
    return 0;
}
