#pragma once

#include <base_node.hpp>

namespace nsSdD
{
    template<typename T>
    struct CNode : public CBaseNode
    {
        T m_data;
        CNode (const T& val) : m_data(val) {}
    };
}
