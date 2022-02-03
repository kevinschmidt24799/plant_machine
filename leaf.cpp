//
// Created by Kevin Schmidt on 2/2/22.
//

#include "leaf.hpp"
int Leaf::set_weight(Leaf * parent)
{
    for(auto c : connections_)
    {
        auto cp = dynamic_cast<Leaf *>(c);
        if(cp != parent)
        {
            weight_+= cp->set_weight(this);
        }
    }
    return weight_;
}