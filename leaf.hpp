//
// Created by Kevin Schmidt on 2/2/22.
//

#ifndef TREETEST_LEAF_HPP
#define TREETEST_LEAF_HPP

#include "shape.hpp"
#include "glut_manager.hpp"

class Leaf : public ConnectedShape
{
public:

    float radius_;
    int weight_{1};
    virtual ~Leaf(){};
    Leaf(float x, float y, float z, float r, float g, float b, float radius)
            : ConnectedShape{x, y, z, r, g, b}, radius_{radius}{};
    void draw() override
    {
        glPushMatrix();
        glTranslatef(x_, y_, z_);
        glColor3f(r_, g_, b_);
        glutSolidSphere(radius_, 20, 20);
        glPopMatrix();
    }
    int set_weight(Leaf * parent = nullptr);
};


#endif //TREETEST_LEAF_HPP
