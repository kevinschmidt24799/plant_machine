//
// Created by Kevin Schmidt on 1/30/22.
//

#ifndef TREETEST_SHAPE_HPP
#define TREETEST_SHAPE_HPP
#include <vector>

struct Shape
{
    float x_, y_, z_;
    float r_ {1};
    float g_ {0};
    float b_ {0};
    virtual void draw() = 0;
    Shape(float x, float y, float z);
    Shape(float x, float y, float z, float r, float g, float b);
    virtual ~Shape() {};
};

struct ConnectedShape : public Shape
{
    std::vector<ConnectedShape *> connections_;
    ConnectedShape(float x, float y, float z);
    ConnectedShape(float x, float y, float z, float r, float g, float b);
};

void generate_neighbors(std::vector<std::pair<Shape *, Shape*>> & edges);

#endif //TREETEST_SHAPE_HPP
