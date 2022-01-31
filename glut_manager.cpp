//
// Created by Kevin Schmidt on 1/28/22.
//

#include "glut_manager.hpp"
static GlutManager * gm;
void g_display(){gm->display();}
void g_mouse(int button, int state, int x, int y) {gm->mouse(button, state, x, y); }
void g_motion(int x, int y) {gm->motion(x, y);}
void g_keys(unsigned char c, int x, int y) { gm->keys(c, x, y); }
void g_keysup(unsigned char c, int x, int y) { gm->keysup(c, x, y); }


void GlutManager::start(int * argc, char **argv)
{
    gm = this;
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("test");

    glutDisplayFunc(g_display);

    glutMouseFunc(g_mouse);
    glutMotionFunc(g_motion);

    glutKeyboardFunc(g_keys);
    glutKeyboardUpFunc(g_keysup);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glClearColor(dr_, dg_, db_, 1);


    glutMainLoop();
}


void GlutManager::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, static_cast<float>(glutGet(GLUT_WINDOW_WIDTH))/glutGet(GLUT_WINDOW_HEIGHT),  0.01, 100);
    auto e = eye_ * Matrix<3,1>{{0},{0},{2}};
    auto up = Matrix<3,1>{{0},{1},{0}};
    gluLookAt(e.data_[0][0], e.data_[1][0], e.data_[2][0], 0, 0, 0, up.data_[0][0], up.data_[1][0], up.data_[2][0]);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    draw();

    glutSwapBuffers();
}

void GlutManager::draw()
{
    glutWireTeapot(1);
}

void GlutManager::mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        left = (state == GLUT_DOWN);
        leftx = x;
        lefty = y;
    }
}

void GlutManager::motion(int x, int y)
{
    if(left)
    {
        float rotate = 0.5;
        eye_ = rotate_na(rotate*(leftx-x), 0, 1, 0) * eye_;
        leftx = x;
        eye_ = rotate_na(rotate*(lefty-y), 1, 0, 0) * eye_;
        lefty = y;
        //glutGet(GLUT_WINDOW_WIDTH)
    }
    glutPostRedisplay();
}

void GlutManager::keys(unsigned char c, int x, int y)
{
    if(c=='-')
    {
        eye_ = eye_ * 1.1;
    }
    if(c=='+')
    {
        eye_ = eye_ / 1.1;
    }
    glutPostRedisplay();
}
void GlutManager::keysup(unsigned char c, int x, int y)
{

}
