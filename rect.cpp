//
// Created by Kevin Schmidt on 1/27/22.
//

#include "rect.hpp"

Rect::Rect(float x1, float y1, float x2, float y2)
    :x1_{x1}, y1_{y1}, x2_{x2}, y2_{y2}{}

RectNode::RectNode(Rect const & r)
    :r_(r){};


void RectNode::make_grid(float max_length)
{
    if(r_.x2_ - r_.x1_ > max_length)
    {
        r1_ = std::make_unique<RectNode>(Rect{r_.x1_, r_.y1_, (r_.x1_ + r_.x2_) / 2, r_.y2_});
        r2_ = std::make_unique<RectNode>(Rect{(r_.x1_ + r_.x2_) / 2, r_.y1_, r_.x2_, r_.y2_});
    } else if(r_.y2_ - r_.y1_ > max_length) {
        r1_ = std::make_unique<RectNode>(Rect{r_.x1_, r_.y1_, r_.x2_, (r_.y1_+r_.y2_)/2});
        r2_ = std::make_unique<RectNode>(Rect{r_.x1_, (r_.y1_+r_.y2_)/2, r_.x2_, r_.y2_});
    } else {
        return;
    }

    r1_->make_grid(max_length);
    r2_->make_grid(max_length);
}

