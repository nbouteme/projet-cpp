#pragma once

#include <base_node.hpp>

namespace nsSdD
{
    template<typename T>
    struct node : public base_node
    {
        T data;
        node (const T& val) : data(val) {}
    };
}
