//
// Created by Kevin Schmidt on 1/27/22.
//

#ifndef TREETEST_RECT_HPP
#define TREETEST_RECT_HPP
#include "shape.hpp"
#include <vector>

struct Rect
{
    float x1_, y1_, x2_, y2_;
    Rect(float x1, float y1, float x2, float y2);
};

struct RectNode
{
    Rect r_;
    std::unique_ptr<RectNode> r1_ {};
    std::unique_ptr<RectNode> r2_ {};

    explicit RectNode(Rect const & r);

    void make_grid(float max_length);

    template<typename Callback>
    void visit(Callback cb) const
    {
        if(r1_)
        {
            r1_->visit(cb);
            r2_->visit(cb);
        } else {
            cb(r_);
        }
    }

    std::vector<Shape> get_shapes();
};





#endif //TREETEST_RECT_HPP
