//
// Created by Kevin Schmidt on 1/30/22.
//

#ifndef TREETEST_SHAPE_MST_HPP
#define TREETEST_SHAPE_MST_HPP
#include "shape.hpp"
#include <tuple>
#include <memory>
#include <vector>
#include <iostream>

class Vertex
{
public:
    Vertex(Shape const * shape) : me_{shape}, parent_{this}
    {
        parent_ = this;
    }
    Vertex &operator=(Vertex const &other) = delete;
    Vertex(Vertex const & other)
    {
        //std::cout << "copying Vertex\n";
        me_ = other.me_;
        parent_ = this;
    }

    Shape const * me_;
    Vertex * parent_;
    Vertex * get_head();

    friend std::ostream &operator<<(std::ostream &os, Vertex const &vertex);
};

using Edge = std::pair<Vertex *, Vertex *>;
std::ostream &operator<<(std::ostream &os, Edge const &edge);

class ShapeMST
{
public:
    virtual float cost(Shape const & s1, Shape const & s2);
    std::vector<std::pair<Shape const *, Shape const *>> get_mst(std::vector<std::unique_ptr<Shape>> const & shapes);
};


#endif //TREETEST_SHAPE_MST_HPP
