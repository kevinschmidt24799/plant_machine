//
// Created by Kevin Schmidt on 1/30/22.
//

#include "shape.hpp"

Shape::Shape(float x, float y, float z)
:x_{x}, y_{y}, z_{z}{}

Shape::Shape(float x, float y, float z, float r, float g, float b)
:x_{x}, y_{y}, z_{z}, r_{r}, g_{g}, b_{b}{}

ConnectedShape::ConnectedShape(float x, float y, float z)
:Shape{x,y,z}{}

ConnectedShape::ConnectedShape(float x, float y, float z, float r, float g, float b)
:Shape{x, y, z, r, g, b}{}


void generate_neighbors(std::vector<std::pair<Shape *, Shape*>> & edges)
{
    for(auto & e : edges)
    {
        auto s1  = dynamic_cast<ConnectedShape *>(e.first);
        auto s2  = dynamic_cast<ConnectedShape *>(e.second);
        if(s1 && s2)
        {
            s1->connections_.push_back(s2);
            s2->connections_.push_back(s1);
        }
    }
}

