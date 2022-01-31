#include <iostream>
#include "rect.hpp"
#include "variant"
#include "glut_manager.hpp"
#include <math.h>
#include <random>
#include "shape.hpp"
#include "shape_mst.hpp"

int main(int argc, char **argv)
{
    class Sphere : public Shape
    {
        float radius_;
    public:
        virtual ~Sphere(){};
        Sphere(float x, float y, float z, float r)
        :Shape{x, y, z}, radius_{r}{};
        void draw() override
        {
            glPushMatrix();
            glTranslatef(x_, y_, z_);
            glColor3f(r_, g_, b_);
            glutSolidSphere(radius_, 20, 20);
            glPopMatrix();
        }
    };

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

    class ShapesDraw : public GlutManager
    {
        int seed = 0;
        std::vector<std::unique_ptr<Shape>> shapes_;
    public:
        ShapesDraw(std::vector<std::unique_ptr<Shape>> && shapes):shapes_{std::move(shapes)}{};
        void draw() override
        {
            for(auto const & s : shapes_)
            {
                s->draw();
            }
        }
    };

    std::vector<std::unique_ptr<Shape>> stuff;

    std::default_random_engine generator;
    for(int i = 0; i < 10000 ; ++i)
    {
        std::uniform_real_distribution<float> distribution(-1,1);
        float x = distribution(generator);
        float y = distribution(generator)+1;
        float z = distribution(generator);
        if(y > 0 && x*x+y*y+z*z < 1 && x*x+(y-0.5)*(y-0.5)>0.1)
        {
            stuff.push_back(std::make_unique<Sphere>(x, y, z, 0.01));
        }
    }

    stuff.push_back(std::make_unique<Sphere>(0, -1, 0, 0.01));

    class TreeMST : public ShapeMST
    {
        float cost(Shape const & s1, Shape const & s2) override
        {
            float dx = s1.x_-s2.x_;
            float dy = s1.y_-s2.y_;
            float dz = s1.z_-s2.z_;
            return sqrt(dx*dx + dy*dy + dz*dz);
        }
    };
    auto edges = TreeMST{}.get_mst(stuff);

    for(auto & edge : edges)
    {
        stuff.push_back(std::make_unique<Branch>(
                edge.first->x_, edge.first->y_, edge.first->z_,
                edge.second->x_, edge.second->y_, edge.second->z_));
    }

    ShapesDraw sd{std::move(stuff)};
    sd.start(&argc, argv);
}
