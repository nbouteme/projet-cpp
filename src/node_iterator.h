#pragma once 
#include <cstddef> // ptrdiff_t
template<typename T> class node_iterator;
class node_iterator
{
    public:
        ptrdiff_t difference_type;
        //iterator_category?
        template<typename T>
        T value_type;
        T* pointer;// I Dunno
        T& reference;// I Dunno
        template<typename T>
        T Data; //The Data of the node
		
		
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

        node_iterator::node_iterator()
		{
			//ctor
		}

		node_iterator::~node_iterator()
		{
			//dtor
				
		}
    protected:
    private:
};


