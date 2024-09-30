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
        m_greatestSide(INT_MIN),
        m_lowestPointOnY(INT_MIN),
        m_leftmostPointOnX(INT_MAX),
        m_rightmostPointOnX(INT_MIN)
        
    {
        for (const auto& p : shape) {
            m_greatestSide = std::max(m_greatestSide, std::max(p.first + 1, p.second + 1));    
            m_lowestPointOnY = std::max(m_lowestPointOnY, p.first);
            m_leftmostPointOnX = std::min(m_leftmostPointOnX, p.second);
            m_rightmostPointOnX = std::max(m_rightmostPointOnX, p.second);
        }
    }

    Tetromino(const Tetromino&) = default;
    Tetromino(Tetromino&&) noexcept = default;
    Tetromino& operator=(const Tetromino&) noexcept = default; 
    Tetromino& operator=(Tetromino&&) noexcept = default;

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

    inline int leftmostPointOnX() const {
        return m_leftmostPointOnX;
    }

    inline int rightmostPointOnX() const {
        return m_rightmostPointOnX;
    }
        
    void moveDownOneSquare() noexcept;
    void moveLeftOneSquare() noexcept;
    void moveRightOneSquare() noexcept;

    // TODO: 
    void rotateRigth() {};

    bool containsBlock(Block block) const noexcept;

    virtual ~Tetromino() {}

protected:
    std::vector<Block> m_shape ;
    int m_greatestSide;
    int m_lowestPointOnY;
    int m_leftmostPointOnX;
    int m_rightmostPointOnX;

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