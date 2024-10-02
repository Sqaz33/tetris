#ifndef SRC_INCLUDE_TETROMINO_HPP
#define SRC_INCLUDE_TETROMINO_HPP

#include <algorithm>
#include <climits>
#include <initializer_list>
#include <utility>
#include <vector>


namespace tetrominoes {

using Block = std::pair<int, int>;

class Tetromino {
public:
    Tetromino(std::initializer_list<Block> shape) :
        m_shape(shape),
        m_greatestSide(INT_MIN)
    {
        for (const auto& p : shape) {
            m_greatestSide = std::max(m_greatestSide, std::max(p.first + 1, p.second + 1));    
        }
        setShapeBoundaries();
    }

    Tetromino(const Tetromino& other) {
        m_shape = other.m_shape;
        m_greatestSide = other.m_greatestSide;
        m_highestPointOnY = other.m_highestPointOnY;
        m_lowestPointOnY = other.m_lowestPointOnY;
        m_leftmostPointOnX = other.m_leftmostPointOnX;
        m_rightmostPointOnX = other.m_rightmostPointOnX;
    }

    Tetromino(Tetromino&& other) noexcept {
        m_shape = std::move(other.m_shape);
        m_greatestSide = other.m_greatestSide;
        m_highestPointOnY = other.m_highestPointOnY;
        m_lowestPointOnY = other.m_lowestPointOnY;
        m_leftmostPointOnX = other.m_leftmostPointOnX;
        m_rightmostPointOnX = other.m_rightmostPointOnX;
    }

    Tetromino& operator=(const Tetromino& other) noexcept {
        m_shape = other.m_shape;
        m_greatestSide = other.m_greatestSide;
        m_highestPointOnY = other.m_highestPointOnY;
        m_lowestPointOnY = other.m_lowestPointOnY;
        m_leftmostPointOnX = other.m_leftmostPointOnX;
        m_rightmostPointOnX = other.m_rightmostPointOnX;
        return *this;
    }
    Tetromino& operator=(Tetromino&& other) noexcept {
        m_shape = std::move(other.m_shape);
        m_greatestSide = other.m_greatestSide;
        m_highestPointOnY = other.m_highestPointOnY;
        m_lowestPointOnY = other.m_lowestPointOnY;
        m_leftmostPointOnX = other.m_leftmostPointOnX;
        m_rightmostPointOnX = other.m_rightmostPointOnX;
        return *this;
    }

public:
    inline const auto& shape() const noexcept {
        return m_shape;
    }

    inline int greatestSide() const {
        return m_greatestSide;
    }

    inline int lowestPointOnY() const {
        return m_lowestPointOnY;
    }

    inline int highestPointOnY() const {
        return m_highestPointOnY;
    }

    inline int leftmostPointOnX() const {
        return m_leftmostPointOnX;
    }

    inline int rightmostPointOnX() const {
        return m_rightmostPointOnX;
    }
        
    void moveDownOneSquare() noexcept;
    void moveLeftOneSquare() noexcept;
    void moveRightOneSquare() noexcept;

    void rotateRigth() noexcept;

    bool containsBlock(Block block) const noexcept;

    virtual ~Tetromino() {}

protected:
    std::vector<Block> m_shape ;
    int m_greatestSide;
    int m_lowestPointOnY;
    int m_leftmostPointOnX;
    int m_rightmostPointOnX;
    int m_highestPointOnY;
    
private:
    void swapShapeAxis() noexcept;
    void reflectShape() noexcept;


    void setShapeBoundaries() noexcept;
};

class O_shape : public Tetromino {
public:
    O_shape() :
        Tetromino(
            {
                {0, 0}, {0, 1},
                {1, 0}, {1, 1}
            }
        )
    {}
};

class I_shape : public Tetromino {
public:
    I_shape() :
        Tetromino(
            {
                {0, 0},
                {1, 0},
                {2, 0},
                {3, 0}
            }
        )
    {}
};

class S_shape : public Tetromino {
public:    
    S_shape() :
        Tetromino(
            {           {0, 1}, {0, 2},
                {1, 0}, {1, 1}
            }
        )
    {}
};

class Z_shape : public Tetromino {
public:    
    Z_shape() :
        Tetromino(
            {
                {0, 0}, {0, 1},
                        {1, 1}, {1, 2}
            }
        )
    {}
};

class L_shape : public Tetromino {
public:    
    L_shape() :
        Tetromino(
            {
                {0, 0},
                {1, 0},
                {2, 0}, {2, 1}
            }
        )
    {}
};


class J_shape : public Tetromino {
public:    
    J_shape() :
        Tetromino(
            {
                        {0, 1},
                        {1, 1},
                {2, 0}, {2, 1} 
            }
        )
    {}
};

class T_shape : public Tetromino {
public:    
    T_shape() :
        Tetromino(
            {
                {0, 0}, {0, 1}, {0, 2},
                        {1, 1} 
            }
        )
    {}
};

Tetromino getRandomTetromino();
 
} // namespace tetrominoes

#endif // SRC_INCLUDE_TETROMINO_HPP