#include "../include/tetris.hpp"

#include <cmath>

namespace tetris {

TetrisGameModel::TetrisGameModel(size_t width, size_t height) :
    m_field(height, Line(width, BlockType::VOID))
    , m_fieldWidth(width)
    , m_fieldHeight(height)
{   
    setNextTetromino();
    setCurTetrominoOnField();
    setCurTetrominoGhostOnField();
}

const TetrisGameField& TetrisGameModel::field() const noexcept {
    return m_field;
} 

size_t TetrisGameModel::fieldWidth() const noexcept {
    return m_fieldWidth;
}

size_t TetrisGameModel::fieldHieght() const noexcept {
    return m_fieldHeight;
}

size_t TetrisGameModel::score() const noexcept {
    return m_score;
}

const tetrominoes::Tetromino& TetrisGameModel::curTetromino() const {
    return m_curTetromino;
}

const tetrominoes::Tetromino& TetrisGameModel::curTetrominoGhost() const {
    return m_curTetrominoGhost;
}

bool TetrisGameModel::hasBlockAt(size_t i, size_t j) const noexcept {
    return m_field[i][j] == BlockType::FILLED;
}

bool TetrisGameModel::hasGhostBlockAt(size_t i, size_t j) const noexcept {
    return m_field[i][j] == BlockType::GHOST;
}

bool TetrisGameModel::canMovedDownTetromino(const tetrominoes::Tetromino& tetromino) const {
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

bool TetrisGameModel::canMovedLeftTetromino(const tetrominoes::Tetromino& tetromino) const {
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

bool TetrisGameModel::canMovedRightTetromino(const tetrominoes::Tetromino& tetromino) const {
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

bool TetrisGameModel::canRotateRightTetromino(const tetrominoes::Tetromino& tetromino) const {
    auto tempTetromino = tetromino;
    tempTetromino.rotateRigth();

    bool canRotate = true;
    for (auto& p : tempTetromino.shape()) {
        canRotate = canRotate && p.first >= 0 && p.first < m_fieldHeight &&
                                    p.second >= 0 && p.second < m_fieldWidth &&
                                    (tetromino.containsBlock(p) || !hasBlockAt(p.first, p.second));
                                
    }
    return canRotate;
}

bool TetrisGameModel::moveLeftCurTetromino() {
    if (!canMovedLeftTetromino(m_curTetromino)) {
        return false;
    }
    deleteCurTetrominoOnField();
    m_curTetromino.moveLeftOneSquare();
    setCurTetrominoOnField();
    return true;
}

bool TetrisGameModel::moveRightCurTetromino() {
    if (!canMovedRightTetromino(m_curTetromino)) {
        return false;
    }
    deleteCurTetrominoOnField();
    m_curTetromino.moveRightOneSquare();
    setCurTetrominoOnField();
    return true;
}

bool TetrisGameModel::rotateRightCurTetromino() {
    if (canRotateRightTetromino(m_curTetromino)) {
        deleteCurTetrominoOnField();
        m_curTetromino.rotateRigth();
        setCurTetrominoOnField();
    }
    return false;
} 


void TetrisGameModel::setBlockAt(size_t i, size_t j) {
    m_field[i][j] = BlockType::FILLED;
}

void TetrisGameModel::deleteBlockAt(size_t i, size_t j) {
    m_field[i][j] = BlockType::VOID;
}

void TetrisGameModel::setGhostBlockAt(size_t i, size_t j) {
    m_field[i][j] = BlockType::GHOST;
}

void TetrisGameModel::deleteGhostBlockAt(size_t i, size_t j) {
    m_field[i][j] = BlockType::VOID;
}

void TetrisGameModel::setCurTetrominoOnField() {
    setCurTetrominoGhostOnField();
    for (const auto& p : m_curTetromino.shape()) {
        setBlockAt(p.first, p.second);
    }
}

void TetrisGameModel::setCurTetrominoGhostOnField() {
    deleteCurTetrominoGhostOnField();
    m_curTetrominoGhost = m_curTetromino;
    while (canMovedDownTetromino(m_curTetrominoGhost)) {
        m_curTetrominoGhost.moveDownOneSquare();
    }
    for (const auto& p : m_curTetrominoGhost.shape()) {
        setGhostBlockAt(p.first, p.second);
    }
}

void TetrisGameModel::deleteCurTetrominoOnField() {
    for (const auto& p : m_curTetromino.shape()) {
        deleteBlockAt(p.first, p.second);
    }
}

void TetrisGameModel::deleteCurTetrominoGhostOnField() {
    for (const auto& p : m_curTetrominoGhost.shape()) {
        if (!hasBlockAt(p.first, p.second)) {
            deleteGhostBlockAt(p.first, p.second);
        }
    }
}

void TetrisGameModel::updateScore() noexcept {
    m_score += linesDestroyed ? std::pow(2, linesDestroyed) : 0;
}

static void shiftColumn(TetrisGameField& matrix, int startRow, int column) {
    for (int i = startRow; i > 0; --i) {
        matrix[i][column] = matrix[i - 1][column];
    }
    matrix[0][column] = BlockType::VOID;
}

void TetrisGameModel::lowerAllLinesUnder(size_t start) {
    for (int j = 0; j < m_fieldWidth; ++j) {
        shiftColumn(m_field, start, j);
    }
}

void TetrisGameModel::deleteFullLines() {
    for (int i = m_fieldHeight - 1; i >= 0; --i) {
        if (
            std::find_if(
                m_field[i].begin(), m_field[i].end(), 
                [](BlockType x){return x == BlockType::VOID || x == BlockType::GHOST;}
            ) == m_field[i].end()
        )  {
            std::for_each(
                m_field[i].begin(), m_field[i].end(), 
                [](auto& c) {c = BlockType::VOID;}
            );
            lowerAllLinesUnder(i);
            ++linesDestroyed;
        }
    }
}

bool TetrisGameModel::setNextTetromino() {
    m_curTetromino = tetrominoes::getRandomTetromino();
    for (int i = 0; i < m_fieldWidth / 2; ++i) {
        m_curTetromino.moveRightOneSquare();
    }
    return canMovedDownTetromino(m_curTetromino);
}

bool TetrisGameModel::update() {
    if (canMovedDownTetromino(m_curTetromino)) {
        deleteCurTetrominoOnField();
        m_curTetromino.moveDownOneSquare();
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