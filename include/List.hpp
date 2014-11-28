#pragma once

namespace nsSdD
{
    template <typename T>
    class List
    {
        struct node
        {
    	    typedef node* pointer;
    
        	pointer prev = nullptr;
        	pointer next = nullptr;
        	T data;
        
        	void hook (pointer elem)
        	{
        		pointer tmp = elem->prev;
        		next = elem;
        		prev = elem->prev;
        		elem->prev = this;
        		if(tmp)
        		tmp->next = this;
        	}
        };

        struct node_iterator
        {
			typedef T         value_type;
			typedef ptrdiff_t difference_type;
			typedef base_node* pointer;
			typedef node_iterator& reference;
			typedef std::bidirectional_iterator_tag	iterator_category;
			
			node_iterator(const base_node* val = nullptr) : node_ptr(val) {}	
			pointer node_ptr;
			
			node_iterator& operator++() ()
			{
				node_ptr = node_ptr->next;
				return *this;
			}
			
			node_iterator operator++() (int)
			{
				base_node* tmp = node_ptr;
				node_ptr = node_ptr->next;
				return tmp;
			}
			
			node_iterator operator--() (int)
			{
				base_node* tmp = node_ptr;
				node_ptr = node_ptr->prev;
				return tmp;
			}
			
			bool operator ==() (node_iterator node)
			{
				return node_ptr == node.node_ptr;
			}	
			
			bool operator!=() (node_iterator node)
			{
				return node_ptr != node.node_ptr;
			}	
			
			node_iterator& operator--() ()
			{
				node_ptr = node_ptr->prev;
				return *this;
			}
			
			value_type& operator*() ()
			{
				return reinterpret_cast<node*>(node_ptr)->data;
			}
			
		};	
    };
}
