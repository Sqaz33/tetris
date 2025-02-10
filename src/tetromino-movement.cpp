#include "../include/tetromino-movement.hpp"


#include <unordered_map>

namespace {
    using namespace tetrominoes;
    using namespace tetris_game_model;
    BlockType TetrominoTypeToBlockType(TetrominoType type) {
        return static_cast<BlockType>(type);
    }
} // namespace

namespace tetromino_movement {

// ##################################################
// TetrominoMovementWithGhostTetromino
void TetrominoMovementWithGhostTetromino::setField(
    std::shared_ptr<std::vector<std::vector<tetris_game_model::BlockType>>> field) {
    field_ = field;
}

bool TetrominoMovementWithGhostTetromino::moveDown() {
    if (!canMoveDownTetromino_(curTetromino_)) {
        return false;
    }
    deleteCurTetrominoOnField_();
    curTetromino_.moveDownOneSquare();
    setCurTetrominoOnField_();
    updateTetrominoGhost_();
    return true;
}

bool TetrominoMovementWithGhostTetromino::moveLeft() {
    if (!canMoveLeftTetromino_(curTetromino_)) {
        return false;
    }
    deleteCurTetrominoOnField_();
    curTetromino_.moveLeftOneSquare();
    setCurTetrominoOnField_();
    updateTetrominoGhost_();
    return true;
}

bool TetrominoMovementWithGhostTetromino::moveRight() {
    if (!canMoveRightTetromino_(curTetromino_)) {
        return false;
    }
    deleteCurTetrominoOnField_();
    curTetromino_.moveRightOneSquare();
    setCurTetrominoOnField_();
    updateTetrominoGhost_();
    return true;
}

bool TetrominoMovementWithGhostTetromino::rotateRight() {
    if (!canRotateRightTetromino_(curTetromino_)) {
        return false;
    }
    deleteCurTetrominoOnField_();
    curTetromino_.rotateRigth();
    setCurTetrominoOnField_();
    updateTetrominoGhost_();
    return true;
}

bool TetrominoMovementWithGhostTetromino::setTetromino(tetrominoes::Tetromino tetromino) {
    if (!canMoveDownTetromino_(tetromino)) {
        return false;
    }
    deleteCurTetrominoOnField_();
    curTetromino_ = tetromino;
    setCurTetrominoOnField_();
    updateTetrominoGhost_();
    return true;
}

bool TetrominoMovementWithGhostTetromino::canMoveDownTetromino_(const tetrominoes::Tetromino& tetromino) const {
    for (const auto& p : tetromino.shape()) {
        if (p.first < fieldHeight_() - 1  &&
            fieldHasBlockAt_(p.first + 1, p.second) &&
            !tetromino.containsBlock({p.first + 1, p.second})) 
        {
            return false;
        }
    }
    return tetromino.lowestPointOnY() < fieldHeight_() - 1;
}

bool TetrominoMovementWithGhostTetromino::canMoveLeftTetromino_(const tetrominoes::Tetromino& tetromino) const {
    for (const auto& p : tetromino.shape()) {
        if (p.second > 0  &&
            fieldHasBlockAt_(p.first, p.second - 1) &&
            !tetromino.containsBlock({p.first, p.second - 1})) 
        {
            return false;
        }
    }
    return tetromino.leftmostPointOnX() > 0;
}

bool TetrominoMovementWithGhostTetromino::canMoveRightTetromino_(const tetrominoes::Tetromino& tetromino) const {
    for (const auto& p : tetromino.shape()) {
        if (p.second < fieldWidth_() - 1 &&
            fieldHasBlockAt_(p.first, p.second + 1) &&
            !tetromino.containsBlock({p.first, p.second + 1})) 
        {
            return false;
        }
    }
    return tetromino.rightmostPointOnX() < fieldWidth_() - 1;
}

bool TetrominoMovementWithGhostTetromino::canRotateRightTetromino_(const tetrominoes::Tetromino& tetromino) const {
    auto tempTetromino = tetromino;
    tempTetromino.rotateRigth();

    for (auto& p : tempTetromino.shape()) {
        bool canRotate = p.first >= 0 && p.first < fieldHeight_() &&
                            p.second >= 0 && p.second < fieldWidth_() &&
                            (tetromino.containsBlock(p) || !fieldHasBlockAt_(p.first, p.second));
        if (!canRotate) return false;
    }
    return true;
}

bool TetrominoMovementWithGhostTetromino::fieldHasBlockAt_(std::size_t x, std::size_t y) const {
    auto block = field_->operator[](y)[x];
    return block != tetris_game_model::BlockType::VOID 
            && block != tetris_game_model::BlockType::GHOST; 
}
void TetrominoMovementWithGhostTetromino::setBlockAt_(std::size_t x, std::size_t y, tetris_game_model::BlockType block) {
    decltype(auto) blockAt = field_->operator[](y)[x];
    blockAt = block;
}

void TetrominoMovementWithGhostTetromino::deleteBlockAt_(std::size_t x, std::size_t y) {
    setBlockAt_(x, y, tetris_game_model::BlockType::VOID);
}

void TetrominoMovementWithGhostTetromino::setGhostBlockAt_(std::size_t x, std::size_t y) {
    setBlockAt_(x, y, tetris_game_model::BlockType::GHOST);
}

void TetrominoMovementWithGhostTetromino::deleteGhostBlockAt_(std::size_t x, std::size_t y) {
    deleteBlockAt_(x, y);
}

void TetrominoMovementWithGhostTetromino::setCurTetrominoOnField_() {
    for (auto b : curTetromino_.shape()) {
        setBlockAt_(
            b.first, b.second, TetrominoTypeToBlockType(curTetromino_.type()));
    }
}

void TetrominoMovementWithGhostTetromino::deleteCurTetrominoOnField_() {
    for (auto b : curTetromino_.shape()) {
        setBlockAt_(
            b.first, b.second, BlockType::VOID);
    }
}

void TetrominoMovementWithGhostTetromino::setCurTetrominoGhostOnField_() {
    for (auto b : curTetrominoGhost_.shape()) {
        setBlockAt_(
            b.first, b.second, BlockType::GHOST);
    }
}

void TetrominoMovementWithGhostTetromino::deleteCurTetrominoGhostOnField_() {
    for (auto b : curTetrominoGhost_.shape()) {
        setBlockAt_(
            b.first, b.second, BlockType::VOID);
    }
}

void TetrominoMovementWithGhostTetromino::updateTetrominoGhost_() {
    deleteCurTetrominoGhostOnField_();
    curTetrominoGhost_ = curTetromino_;
    while (canMoveDownTetromino_(curTetrominoGhost_)) {
        curTetrominoGhost_.moveDownOneSquare();
    }
    setCurTetrominoGhostOnField_();
}

std::size_t TetrominoMovementWithGhostTetromino::fieldWidth_() const {
    return field_->at(0).size();
}

std::size_t TetrominoMovementWithGhostTetromino::fieldHeight_() const {
    return field_->size();
}

} // namespace tetromino_movement