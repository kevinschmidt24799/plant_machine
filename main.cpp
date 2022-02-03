#include <iostream>
#include "rect.hpp"
#include "variant"
#include "glut_manager.hpp"
#include <math.h>
#include <random>
#include "shape.hpp"
#include "shape_mst.hpp"
#include "leaf.hpp"
#include "branch.hpp"
#include "floor.hpp"

int main(int argc, char **argv)
{
    class ShapesDraw : public GlutManager
    {
        int seed = 0;
        std::vector<std::unique_ptr<Shape>> shapes_;

    public:
        ShapesDraw(std::vector<std::unique_ptr<Shape>> && shapes):shapes_{std::move(shapes)}
        {
            dr_ = 0.3;
            dg_ = 0.4;
            db_ = 0.5;
        };
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
    for(int i = 0; i < 1000 ; ++i)
    {
        std::uniform_real_distribution<float> distribution(-1,1);
        float x = distribution(generator);
        float y = distribution(generator)+1;
        float z = distribution(generator);
        if(y > 0 && x*x+y*y+z*z < 1)
        {
            //if(x*x+(y-0.5)*(y-0.5)>0.1)
            {
                stuff.push_back(std::make_unique<Leaf>(x, y, z, 1, 0.8, 0.8, 0.005));
            }
        }
    }

    stuff.push_back(std::make_unique<Leaf>(0, -1, 0, 0, 0, 0, 0));

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

    stuff.push_back(std::make_unique<Floor>(0.05, 0.2, 0.1));


    for(auto & edge : edges)
    {
        stuff.push_back(std::make_unique<Branch>(
                edge.first->x_, edge.first->y_, edge.first->z_,
                edge.second->x_, edge.second->y_, edge.second->z_,
                0.3, 0.6, 0.0));
    }

    ShapesDraw sd{std::move(stuff)};
    sd.start(&argc, argv);
}
