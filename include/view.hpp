#ifndef INCLUDE_VIEW_HPP
#define INCLUDE_VIEW_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// #include "tetris.hpp"
#include "tetromino.hpp"
#include "tetris-game-model.hpp"

using namespace tetris_game_model;

namespace view {

class IDrawable {
public:
    virtual void draw(sf::RenderWindow& window, sf::Vector2f start) = 0;
    virtual ~IDrawable() { }
};

class IDrawableComposite : public IDrawable {
public:
    void pushComponent(std::shared_ptr<IDrawable> comp);
    virtual void draw(sf::RenderWindow& window, sf::Vector2f start) = 0;

private:
    std::vector<std::shared_ptr<IDrawable>> components_;
};

/**
 * @brief 
 * 
 */
class DrawableFrame final : public IDrawable {
public:
    DrawableFrame(float width, float height, float thickness, sf::Color color);

public:
    void draw(sf::RenderWindow& window, sf::Vector2f start) override;
    float thickness() const;

private:
    float thickness_;
    sf::Color color_;
    sf::RectangleShape externalRect_;
    sf::RectangleShape internalRect_;
};

/**
 * @brief
 *
 */
class DrawableFramedWindow final : public IDrawableComposite {
public:
    DrawableFramedWindow(sf::RenderWindow& window, float thickness, sf::Color color);

public:
    void draw(sf::RenderWindow& window, sf::Vector2f start = { 0, 0 }) override;

private:
    DrawableFrame frame_;

private:
    void drawComponents_(sf::RenderWindow& window, sf::Vector2f start);
};

/**
 * @brief 
 * 
 */
class DrawableTetrisField final : public IDrawable {
public:
    DrawableTetrisField(float width, 
                        float height, 
                        float gridThickness, 
                        std::shared_ptr<TetrisGameModel> model);

public:
    void draw(sf::RenderWindow& window, sf::Vector2f start) override;
    std::shared_ptr<TetrisGameModel> model();

private:
    void drawBlockAt_(std::size_t blockX, 
                      std::size_t blockY,
                      sf::Vector2f start,
                      sf::RenderWindow& window,
                      sf::Color blockColor);
    void drawGrid_(sf::RenderWindow& window, sf::Vector2f start);

    // void drawCurTetromino_(sf::RenderWindow& window, sf::Vector2f start);
    // void drawCurTetrominoGhost_(sf::RenderWindow& window, sf::Vector2f start);
    // void eraseCurTetromino_(sf::RenderWindow& window, sf::Vector2f start);
    // void eraseCurTetrominoGhost_(sf::RenderWindow& window, sf::Vector2f start);
private:    
    std::shared_ptr<TetrisGameModel> model_;
    const float gridThickness_;
    float blockWidth_;
    float blockHeight_;
    float width_;
    float height_;
};

} // namespace view

#endif // INCLUDE_VIEW_HPP