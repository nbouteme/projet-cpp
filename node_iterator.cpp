#include "node_iterator.h"

node_iterator::node_iterator()
{
    //ctor
}

node_iterator::~node_iterator()
{
    //dtor
}
/*

Ensuite, cette classe doit se comporter comme un iterateur normal,
il faut donc surcharger les operateurs , ->, ++ et -- (post et pre)
et les operateur de comparaison == et <. La classe const_node_iterator est une version const.

*/


template <class node_iterator>
node_iterator sum (node_iterator a, node_iterator b)
{
  // WIP
}

template <class node_iterator>
node_iterator multiply (node_iterator a, node_iterator b)
{
  // WIP
}



template <class node_iterator>
bool are_equal (node_iterator node1, node_iterator node2)
{
  //WIP
}

template <class node_iterator>
bool is_lower (node_iterator node1, node_iterator node2)
{
  //WIP
}

template <class node_iterator>
bool is_bigger (node_iterator node1, node_iterator node2)
{
  //WIP
}



