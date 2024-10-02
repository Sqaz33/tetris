#include "include/tetris.hpp"

#include <cmath>

namespace tetris {

bool Tetris::canMovedDownTetromino(const tetrominoes::Tetromino& tetromino) const {
    for (const auto& p : tetromino.shape()) {
        if (p.first < m_fieldHeight - 1  &&
            hasBlockAt(p.first + 1, p.second) &&
            !tetromino.containsBlock({p.first + 1, p.second})) 
        {
            return false;
        }
    }
    return tetromino.lowestPointOnY() < m_fieldHeight - 1;
}

bool Tetris::canMovedLeftTetromino(const tetrominoes::Tetromino& tetromino) const {
    for (const auto& p : tetromino.shape()) {
        if (p.second > 0  &&
            hasBlockAt(p.first, p.second - 1) &&
            !tetromino.containsBlock({p.first, p.second - 1})) 
        {
            return false;
        }
    }
    return tetromino.leftmostPointOnX() > 0;
}

bool Tetris::canMovedRightTetromino(const tetrominoes::Tetromino& tetromino) const {
    for (const auto& p : tetromino.shape()) {
        if (p.second < m_fieldWidth - 1 &&
            hasBlockAt(p.first, p.second + 1) &&
            !tetromino.containsBlock({p.first, p.second + 1})) 
        {
            return false;
        }
    }
    return tetromino.rightmostPointOnX() < m_fieldWidth - 1;
}

bool Tetris::moveLeftCurTetromino() {
    if (!canMovedLeftTetromino(*m_curTetromino.get())) {
        return false;
    }
    deleteCurTetrominoOnField();
    m_curTetromino->moveLeftOneSquare();
    setCurTetrominoOnField();
    return true;
}

bool Tetris::moveRightCurTetromino() {
    if (!canMovedRightTetromino(*m_curTetromino.get())) {
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
        canRotate = canRotate && p.first >= 0 && p.first < m_fieldHeight &&
                                    p.second >= 0 && p.second < m_fieldWidth &&
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


void Tetris::setBlockAt(size_t i, size_t j) {
    m_field[i][j] = blockVal();
}

void Tetris::deleteBlockAt(size_t i, size_t j) {
    m_field[i][j] = voidBlockVal();
}

void Tetris::setGhostBlockAt(size_t i, size_t j) {
    m_field[i][j] = ghostBlockVal();
}

void Tetris::deleteGhostBlockAt(size_t i, size_t j) {
    m_field[i][j] = voidBlockVal();
}

void Tetris::setCurTetrominoOnField() {
    if (!m_curTetromino) {
        return;
    }
    setCurTetrominoGhostOnField();
    for (const auto& p : m_curTetromino->shape()) {
        setBlockAt(p.first, p.second);
    }
}

void Tetris::setCurTetrominoGhostOnField() {
    deleteCurTetrominoGhostOnField();
    m_curTetrominoGhost = 
        std::make_unique<tetrominoes::Tetromino>(*m_curTetromino.get());
    while (canMovedDownTetromino(*m_curTetrominoGhost.get())) {
        m_curTetrominoGhost->moveDownOneSquare();
    }
    for (const auto& p : m_curTetrominoGhost->shape()) {
        setGhostBlockAt(p.first, p.second);
    }
}

void Tetris::deleteCurTetrominoOnField() {
    if (!m_curTetromino) {
        return;
    }
    for (const auto& p : m_curTetromino->shape()) {
        deleteBlockAt(p.first, p.second);
    }
}

void Tetris::deleteCurTetrominoGhostOnField() {
    if (!m_curTetrominoGhost) {
        return;
    }
    for (const auto& p : m_curTetrominoGhost->shape()) {
        if (!hasBlockAt(p.first, p.second)) {
            deleteGhostBlockAt(p.first, p.second);
        }
    }
}

void Tetris::updateScore() noexcept {
    m_score += linesDestroyed ? std::pow(2, linesDestroyed) : 0;
}

static void shiftColumn(TetrisGameField& matrix, int startRow, int column) {
    for (int i = startRow; i > 0; --i) {
        matrix[i][column] = matrix[i - 1][column];
    }
    matrix[0][column] = Tetris::voidBlockVal();
}

void Tetris::lowerAllLinesUnder(size_t start) {
    for (int j = 0; j < m_fieldWidth; ++j) {
        shiftColumn(m_field, start, j);
    }
}

void Tetris::deleteFullLines() {
    for (int i = m_fieldHeight - 1; i >= 0; --i) {
        if (
            std::find_if(
                m_field[i].begin(), m_field[i].end(), 
                [](int x){return x == voidBlockVal() || x == ghostBlockVal();}
            ) == m_field[i].end()
        )  
        {
            std::transform(
                m_field[i].begin(), m_field[i].end(), m_field[i].begin(), 
                [](int) {return voidBlockVal();}
            );
            lowerAllLinesUnder(i);
            ++linesDestroyed;
        }
    }
}

bool Tetris::setNextTetromino() {
    m_curTetromino = 
        std::make_unique<tetrominoes::Tetromino>(tetrominoes::getRandomTetromino());
    for (int i = 0; i < m_fieldWidth / 2; ++i) {
        m_curTetromino->moveRightOneSquare();
    }
    setCurTetrominoOnField();
    return canMovedDownTetromino(*m_curTetromino.get());
}

bool Tetris::updateGameField() {
    if (m_curTetromino && canMovedDownTetromino(*m_curTetromino.get())) {
        deleteCurTetrominoOnField();
        m_curTetromino->moveDownOneSquare();
        setCurTetrominoOnField();
    } else {
        deleteFullLines();
        updateScore();
        linesDestroyed = 0;
        return setNextTetromino();
    }
    return true;
}

} // namespace tetris