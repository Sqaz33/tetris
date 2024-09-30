#ifndef SRC_INCLUDE_TETROMINO_HPP
#define SRC_INCLUDE_TETROMINO_HPP

#include <algorithm>
#include <initializer_list>
#include <utility>
#include <vector>

namespace tetrominoes {

class Shape {
public:
    Shape(std::initializer_list<std::pair<int, int>> shape) :
        m_curShape(shape),
        greatestLen(0)
    {
        for (const auto& p : m_curShape) {
            const_cast<int&>(greatestLen) = std::max(p.first + 1, p.second + 1);    
        }
    }

    inline const auto& previouShape() const {
        return m_preShape;
    }

    inline const auto& currentShape() const {
        return m_curShape;
    }
    
    virtual void moveDownOneSquare() final;
    virtual void moveLeftOneSquare() final;
    virtual void moveRightOneSquare() final;

    virtual void rotateRigth() final;

    virtual ~Shape() {}
protected:
    std::vector<std::pair<int, int>> m_preShape, m_curShape ;

private:
    const int greatestLen;

private:
    void reflectShape();
    void setPreShape() {
        m_preShape = m_curShape;
    };
    
};

class O_shape : public Shape {
public:
    O_shape() :
        Shape(
            {
                {0, 0}, {0, 1},
                {1, 0}, {1, 1}
            }
        )
    {}
};

class I_shape : public Shape {
public:
    I_shape() :
        Shape(
            {
                {0, 0},
                {1, 0},
                {2, 0},
                {3, 0}
            }
        )
    {}
};

class S_shape : public Shape {
public:    
    S_shape() :
        Shape(
            {           {0, 1}, {0, 2},
                {1, 0}, {1, 1}
            }
        )
    {}
};

class Z_shape : public Shape {
public:    
    Z_shape() :
        Shape(
            {
                {0, 0}, {0, 1},
                        {1, 1}, {1, 2}
            }
        )
    {}
};

class L_shape : public Shape {
public:    
    L_shape() :
        Shape(
            {
                {0, 0},
                {1, 0},
                {2, 0}, {2, 1}
            }
        )
    {}
};


class J_shape : public Shape {
public:    
    J_shape() :
        Shape(
            {
                        {0, 1},
                        {1, 1},
                {2, 0}, {2, 1} 
            }
        )
    {}
};

class T_shape : public Shape {
public:    
    T_shape() :
        Shape(
            {
                {0, 0}, {0, 1}, {0, 2},
                        {1, 1} 
            }
        )
    {}
};


} // namespace tetrominoes



#endif // SRC_INCLUDE_TETROMINO_HPP