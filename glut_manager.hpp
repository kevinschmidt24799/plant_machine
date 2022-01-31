//
// Created by Kevin Schmidt on 1/28/22.
//

#ifndef TREETEST_GLUT_MANAGER_HPP
#define TREETEST_GLUT_MANAGER_HPP
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "matrix/matrix.hpp"

class GlutManager
{
    Matrix<3,3,float> eye_{};
    int leftx, lefty;
    bool left = false;

public:
    float dr_=0, dg_=0, db_=0;
    void start(int * argc, char **argv);
    virtual void draw();

    void display();
    virtual void mouse(int button, int state, int x, int y);
    virtual void motion(int x, int y);
    virtual void keys(unsigned char c, int x, int y);
    virtual void keysup(unsigned char c, int x, int y);


};


#endif //TREETEST_GLUT_MANAGER_HPP
