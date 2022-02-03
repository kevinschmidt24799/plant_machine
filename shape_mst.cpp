//
// Created by Kevin Schmidt on 1/30/22.
//

#include "shape_mst.hpp"
#include <math.h>

float ShapeMST::cost(Shape const & s1, Shape const & s2)
{
    float dx = s1.x_-s2.x_;
    float dy = s1.y_-s2.y_;
    float dz = s1.z_-s2.z_;
    return sqrt(dx*dx + dy*dy + dz*dz);
}


Vertex * Vertex::get_head()
{
    auto p = this;
    while(p->parent_ != p)
    {
        p = p->parent_;
    }
    return p;
}

std::ostream &operator<<(std::ostream &os, Vertex const &vertex)
{
    os << "this: " << &vertex << " parent_: " << vertex.parent_;
    return os;
}

std::ostream &operator<<(std::ostream &os, Edge const &edge)
{
    os << "(" << edge.first << ", " << edge.second << ")";
    return os;
}

std::vector<std::pair<Shape const *, Shape const *>> ShapeMST::get_mst(std::vector<std::unique_ptr<Shape>> const & shapes)
{
    std::vector<Vertex> vertices;
    for (auto const & shape : shapes)
    {
        vertices.emplace_back(shape.get());
    }

    //std::cout << "Vertices:\n"; for (auto const &v:vertices) std::cout << v << "\n";

    std::vector<Edge> edges;
    for(auto v1 = vertices.begin(); v1 != vertices.end(); ++v1)
    {
        for(auto v2 = v1+1; v2 != vertices.end(); ++v2)
        {
            if(v1->me_->y_ >= v2->me_->y_)
            {
                edges.emplace_back(&*v1, &*v2);
            } else {
                edges.emplace_back(&*v2, &*v1);
            }
        }
    }

    //std::cout << "Edges:\n"; for (auto const &e:edges) std::cout << e << "\n";

    std::make_heap(edges.begin(), edges.end(), [this](Edge const & e1, Edge const & e2){return cost(*e1.first->me_, *e1.second->me_) > cost(*e2.first->me_, *e2.second->me_);});

    //std::cout << "Edges:\n"; for (auto const &e:edges) std::cout << e << "\n";

    std::vector<std::pair<Shape const *, Shape const *>> output;

    for(int edge_count = 0; edge_count < shapes.size()-1; )
    {
        auto e = edges.front();
        std::pop_heap(edges.begin(), edges.end(), [this](Edge e1, Edge e2){return cost(*e1.first->me_, *e1.second->me_) > cost(*e2.first->me_, *e2.second->me_);});
        edges.pop_back();

        if(e.first->get_head() == e.second->get_head())
        {
            //std::cout << "skipping edge\n";
            continue;
        }
        //std::cout << "adding edge "<< e <<'\n';
        output.emplace_back(e.first->me_, e.second->me_);
        e.second->get_head()->parent_ = (e.first);
        ++edge_count;
    }

    return output;
}

