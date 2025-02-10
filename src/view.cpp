#include <iostream>

#include "../include/view.hpp"

#include <SFML/System/Angle.hpp>

#include "../include/tetris-game-model.hpp"

using namespace tetris_game_model;

namespace {

void drawVerticaBlacklLine(sf::RenderWindow& window, 
                           sf::Vector2f start, 
                           float lenght, 
                           float thickness) 
{
    sf::RectangleShape line({lenght, thickness});
    line.setPosition({start.x + thickness, start.y});
    line.setFillColor(sf::Color::Black);
    line.rotate(sf::degrees(90));
    window.draw(line);
}

void drawHorizontalBlackLine(sf::RenderWindow& window, 
                             sf::Vector2f start, 
                             float lenght, 
                             float thickness) 
{
    sf::RectangleShape line({lenght, thickness});
    line.setPosition(start);
    line.setFillColor(sf::Color::Black);
    window.draw(line);
}


} // namespace 

namespace view {
void IDrawableComposite::pushComponent(std::shared_ptr<IDrawable> comp) {
    components_.emplace_back(comp);
}

void IDrawableComposite::draw(sf::RenderWindow& window, sf::Vector2f start) {
    for (auto comp : components_) {
        comp->draw(window, start);
    }
}


// #######################################
DrawableFrame::DrawableFrame(float width, float height, float thickness, sf::Color color) :
        thickness_(thickness)
        , externalRect_({width, height})
        , color_(color)
{
    if (thickness > std::min(width, height)) {
        throw std::logic_error("thickness > min(width, height)");
    }
        
    auto interWidth = width - thickness * 2;
    auto interHeigh = height - thickness * 2;
    internalRect_ = sf::RectangleShape({interWidth, interHeigh});

    externalRect_.setFillColor(color_);
}

void DrawableFrame::draw(sf::RenderWindow& window, sf::Vector2f start) {
    sf::Vector2f interPos(
        start.x + thickness_,
        start.y + thickness_  
    );
    externalRect_.setPosition(start);
    internalRect_.setPosition(interPos);
    window.draw(externalRect_);
    window.draw(internalRect_);
}

float DrawableFrame::thickness() const { return thickness_; }


// #######################################
DrawableFramedWindow::DrawableFramedWindow(sf::RenderWindow& window, float thickness, sf::Color color) :
    frame_(window.getSize().x, window.getSize().y, thickness, color)
{}

void DrawableFramedWindow::draw(sf::RenderWindow& window, sf::Vector2f start) {
    frame_.draw(window, start);
    drawComponents_(window, start);
}

void DrawableFramedWindow::drawComponents_(sf::RenderWindow& window, sf::Vector2f start) {
    auto thickness = frame_.thickness();
    sf::Vector2f compStart(
        start.x + thickness,
        start.y + thickness
    );
    IDrawableComposite::draw(window, compStart);
} 

// #######################################
DrawableTetrisField::DrawableTetrisField(float width, 
                                         float height, 
                                         float gridThickness, 
                                         std::shared_ptr<TetrisGameModel> model) : 
    gridThickness_(gridThickness)
    , model_(model)
    , width_(width)
    , height_(height)
{   
    auto modelWidth = model_->fieldWidth();
    auto modelHeight = model_->fieldHeight();
    blockWidth_ = ((width - gridThickness_) - (gridThickness_ * modelWidth)) / modelWidth;
    blockHeight_ = ((height - gridThickness_) - (gridThickness_ * modelHeight)) / modelHeight;
}

void DrawableTetrisField::draw(sf::RenderWindow& window, sf::Vector2f start) {
    // using namespace tetris;
    using namespace sf;
    
    drawGrid_(window, start);
    
    decltype(auto) field = model_->field(); 
    for (std::size_t y = 0; y < model_->fieldHeight(); ++y) {
        for (std::size_t x = 0; x < model_->fieldWidth(); ++x) {
            auto block = field[y][x];
            if (block != BlockType::VOID) {
                auto blockColor = block == BlockType::GHOST ? Color::Magenta : Color::Red;
                drawBlockAt_(x, y, start, window, blockColor);
            }
        }
    }

}

void DrawableTetrisField::drawBlockAt_(std::size_t blockX, 
                                       std::size_t blockY,
                                       sf::Vector2f start,
                                       sf::RenderWindow& window,
                                       sf::Color blockColor) 
{   
    float x = start.x 
              + blockX * blockWidth_ 
              + gridThickness_ * (blockX + 1);
    float y = start.y
            + blockY * blockHeight_ 
            + gridThickness_ * (blockY + 1);
    sf::Vector2f pos {x , y};

    sf::RectangleShape block({blockWidth_, blockHeight_});
    block.setPosition(pos);

    block.setFillColor(blockColor);

    window.draw(block);
}


void DrawableTetrisField::drawGrid_(sf::RenderWindow& window, sf::Vector2f start) {
    float limX = start.x + width_;
    int c = 0;
    for (float x = start.x; x < limX; x += blockWidth_ + gridThickness_) {
        drawVerticaBlacklLine(window, {x, start.y}, height_, gridThickness_);
    }

    float limY = start.y + height_;
    for (float y = start.y; y < limY; y += blockHeight_ + gridThickness_) {
        drawHorizontalBlackLine(window, {start.x, y}, width_, gridThickness_);
    }
}

// void DrawableTetrisField::eraseCurTetromino_(sf::RenderWindow& window, sf::Vector2f start) {
//     for (const auto& b : model_->curTetromino().shape()) {
//         drawBlockAt_(b.first, b.second, start, window, sf::Color::White);
//     }
// }

// void DrawableTetrisField::eraseCurTetrominoGhost_(sf::RenderWindow& window, sf::Vector2f start) {
//     for (const auto& b : model_->curTetrominoGhost().shape()) {
//         drawBlockAt_(b.first, b.second, start, window, sf::Color::White);
//     }
// }


} // namespace view