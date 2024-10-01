#include "include/tetris.hpp"

namespace tetris {

bool Tetris::canMovedDownCurTetromino() const noexcept {
    for (const auto& p : m_curTetromino->shape()) {
        if (p.first < fieldHeight - 1  &&
            hasBlockAt(p.first + 1, p.second) &&
            !m_curTetromino->containsBlock({p.first + 1, p.second})) 
        {
            return false;
        }
    }
    return m_curTetromino->lowestPointOnY() < fieldHeight - 1;
}

bool Tetris::canMovedLeftCurTetromino() const noexcept {
    for (const auto& p : m_curTetromino->shape()) {
        if (p.second > 0  &&
            hasBlockAt(p.first, p.second - 1) &&
            !m_curTetromino->containsBlock({p.first, p.second - 1})) 
        {
            return false;
        }
    }
    return m_curTetromino->leftmostPointOnX() > 0;
}

bool Tetris::canMovedRightCurTetromino() const noexcept {
    for (const auto& p : m_curTetromino->shape()) {
        if (p.second < fieldWidth - 1 &&
            hasBlockAt(p.first, p.second + 1) &&
            !m_curTetromino->containsBlock({p.first, p.second + 1})) 
        {
            return false;
        }
    }
    return m_curTetromino->rightmostPointOnX() < fieldWidth - 1;
}

bool Tetris::moveLeftCurTetromino() noexcept {
    if (!canMovedLeftCurTetromino()) {
        return false;
    }
    deleteCurTetrominoOnField();
    m_curTetromino->moveLeftOneSquare();
    setCurTetrominoOnField();
    return true;
}

bool Tetris::moveRightCurTetromino() noexcept {
    if (!canMovedRightCurTetromino()) {
        return false;
    }
    deleteCurTetrominoOnField();
    m_curTetromino->moveRightOneSquare();
    setCurTetrominoOnField();
    return true;
}

 bool Tetris::rotateRightCurTetromino() {
    auto tempTetromino = *m_curTetromino.get();
    tempTetromino.rotateRigth();
    
    bool canRotate = true;
    for (auto& p : tempTetromino.shape()) {
        canRotate = canRotate && p.first >= 0 && p.first < fieldHeight &&
                                 p.second >= 0 && p.second < fieldWidth &&
                                 (m_curTetromino->containsBlock(p) || !hasBlockAt(p.first, p.second));
                                
    }
    
    if (canRotate) {
        deleteCurTetrominoOnField();
        m_curTetromino = 
            std::make_unique<tetrominoes::Tetromino>(std::move(tempTetromino));
        setCurTetrominoOnField();
    }
    
    return canRotate;
 } 


void Tetris::setCurTetrominoOnField() noexcept {
    setCurTetrominoGhostOnField();
    for (const auto& p : m_curTetromino->shape()) {
        m_field[p.first][p.second] = 1;
    }
}

void Tetris::setCurTetrominoGhostOnField() noexcept {
    deleteCurTetrominoGhostOnField();
    auto cpy = *m_curTetromino.get();
    while (canMovedDownCurTetromino()) {
        m_curTetromino->moveDownOneSquare();
    }
    for (const auto& p : m_curTetromino->shape()) {
        m_field[p.first][p.second] = 2;
    }
    m_curTetrominoGhost = std::move(m_curTetromino);
    m_curTetromino = std::make_unique<decltype(cpy)>(cpy);
}

void Tetris::deleteCurTetrominoOnField() noexcept {
    if (!m_curTetromino) {
        return;
    }
    for (const auto& p : m_curTetromino->shape()) {
        m_field[p.first][p.second] = 0;
    }
}

void Tetris::deleteCurTetrominoGhostOnField() noexcept {
    if (!m_curTetrominoGhost) {
        return;
    }
    for (const auto& p : m_curTetrominoGhost->shape()) {
        m_field[p.first][p.second] = m_field[p.first][p.second] == 1 ? 1 : 0;
    }
}


static void shiftColumn(TetirsGameField& matrix, int startRow, int column) {
    for (int i = startRow; i > 0; --i) {
        matrix[i][column] = matrix[i - 1][column];
    }
    matrix[0][column] = 0;
}

void Tetris::lowerAllLinesUnder(size_t start) noexcept {
    for (int j = 0; j < fieldWidth; ++j) {
        shiftColumn(m_field, start, j);
    }
}

void Tetris::deleteFullLines() noexcept {
    for (int i = fieldHeight - 1; i >= 0; --i) {
        if (std::find_if(m_field[i].begin(), m_field[i].end(), [](int x){return x == 0 || x == 2;}) == m_field[i].end())  {
            std::transform(
                m_field[i].begin(), m_field[i].end(), m_field[i].begin(), 
                [](int) {return 0;}
            );
            lowerAllLinesUnder(i);
        }
    }
}

bool Tetris::setNextTetromino() {
    m_curTetromino = 
        std::make_unique<tetrominoes::Tetromino>(tetrominoes::getRandomTetromino());
    for (int i = 0; i < fieldWidth / 2; ++i) {
        m_curTetromino->moveRightOneSquare();
    }
    setCurTetrominoOnField();
    return canMovedDownCurTetromino();
}

bool Tetris::updateGameField() {
    if (m_curTetromino && canMovedDownCurTetromino()) {
        deleteCurTetrominoOnField();
        m_curTetromino->moveDownOneSquare();
        setCurTetrominoOnField();
    } else {
        return setNextTetromino();
    }
    deleteFullLines();
    return true;
}


} // namespace tetris