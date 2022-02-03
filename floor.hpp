//
// Created by Kevin Schmidt on 2/2/22.
//

#ifndef TREETEST_FLOOR_HPP
#define TREETEST_FLOOR_HPP
#include "shape.hpp"
#include "glut_manager.hpp"

class Floor : public Shape
{
public:
    virtual ~Floor(){};

    Floor(float r, float g, float b)
            :Shape{0, 0, 0, r, g, b}{};
    void draw() override
    {
        glColor3f(r_, g_, b_);
        glPushMatrix();
        glTranslatef(0,-11,0);
        glutSolidSphere(10, 300, 300);
        glPopMatrix();
        glEnd();
    }
};


#endif //TREETEST_FLOOR_HPP
