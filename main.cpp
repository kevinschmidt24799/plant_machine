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
        std::vector<std::vector<std::unique_ptr<Shape>>> shapes_list_list_;

    public:
        ShapesDraw(std::vector<std::vector<std::unique_ptr<Shape>>> && shapes): shapes_list_list_{std::move(shapes)}
        {
            dr_ = 0.3;
            dg_ = 0.4;
            db_ = 0.5;
        };
        void draw() override
        {
            for(auto const & shapes_list : shapes_list_list_)
            {
                for(auto const & s : shapes_list)
                {
                    s->draw();
                }
            }
        }
    };

    std::vector<std::unique_ptr<Shape>> leaves;
    std::vector<std::unique_ptr<Shape>> branches;
    std::vector<std::unique_ptr<Shape>> world;

    world.push_back(std::make_unique<Floor>(0.05, 0.2, 0.1));

    std::default_random_engine generator;
    for(int i = 0; i < 3000 ; ++i)
    {
        std::uniform_real_distribution<float> distribution(-1,1);
        float x = distribution(generator);
        float y = distribution(generator)+1;
        float z = distribution(generator);
        if(y > 0 && x*x+y*y+z*z < 1)
        {
            //if(x*x+(y-0.5)*(y-0.5)>0.1)
            {
                leaves.push_back(std::make_unique<Leaf>(x, y, z, 1, 0.8, 0.8, 0.005));
            }
        }
    }

    auto trunk = std::make_unique<Leaf>(0, -1, 0, 0, 0, 0, 0);
    auto trunk_ptr = trunk.get();
    leaves.push_back(std::move(trunk));

    class TreeMST : public ShapeMST
    {
        float cost(Shape const & s1, Shape const & s2) override
        {
            float dx = s1.x_-s2.x_;
            float dy = s1.y_-s2.y_;
            float dz = s1.z_-s2.z_;
            return sqrt(dx*dx+dz*dz+dy*dy);
            //return sqrt(dx*dx + dy*dy + dz*dz);
        }
    };
    auto edges = TreeMST{}.get_mst(leaves);
    generate_neighbors(edges);

    trunk_ptr->set_weight();


    for(auto & l : leaves)
    {
        auto lp = dynamic_cast<Leaf *>(l.get());
        if(lp)
        {
            lp->radius_ *= logf(lp->weight_);
        }
    }


    for(auto & edge : edges)
    {
        branches.push_back(std::make_unique<Branch>(
                edge.first->x_, edge.first->y_, edge.first->z_,
                edge.second->x_, edge.second->y_, edge.second->z_,
                0.3, 0.6, 0.0));
    }

    std::vector<std::vector<std::unique_ptr<Shape>>> all_shapes;
    all_shapes.push_back(std::move(leaves));
    all_shapes.push_back(std::move(world));
    all_shapes.push_back(std::move(branches));

    ShapesDraw sd {std::move(all_shapes)};
    sd.start(&argc, argv);
}
