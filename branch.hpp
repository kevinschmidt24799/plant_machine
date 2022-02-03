//
// Created by Kevin Schmidt on 2/2/22.
//

#ifndef TREETEST_BRANCH_HPP
#define TREETEST_BRANCH_HPP
#include "glut_manager.hpp"
#include "shape.hpp"


class Branch : public Shape
{
    float x2_, y2_, z2_;
    float radius_;
public:
    virtual ~Branch(){};
    Branch(float x, float y, float z, float x2, float y2, float z2, float radius = 0)
            :Shape{x, y, z}, x2_{x2}, y2_{y2}, z2_{z2}, radius_{radius}{};
    Branch(float x, float y, float z, float x2, float y2, float z2, float r, float g, float b, float radius = 0)
            :Shape{x, y, z, r, g, b}, x2_{x2}, y2_{y2}, z2_{z2}, radius_{radius}{};
    void draw() override
    {
        glBegin(GL_LINES);
        glColor3f(r_, g_, b_);
        glVertex3f(x_, y_, z_);
        glVertex3f(x2_, y2_, z2_);
        glEnd();
    }
};


#endif //TREETEST_BRANCH_HPP
