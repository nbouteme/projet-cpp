#pragma once

/**
 * \file CNode.hpp
 * \brief Definition of a generic list node
 */


#include <CBaseNode.hpp>

namespace nsSdD
{
    /// Doubly linked node that can hold a value
    template<typename T>
    class CNode : public CBaseNode
    {
    public:
        /// The data contained in the node
        T m_data;
        /// Instantiates a CNode from a copied value \a val
        CNode (const T& val) : m_data(val) {}
    };
}
