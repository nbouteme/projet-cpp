#pragma once

#include<cstddef>
#include<iterator>
#include<limits>

namespace nsSdD
{
    template <typename T>
    class List
    {
        typedef size_t size_type;

        struct base_node
        {
            typedef base_node* pointer;
    
            pointer prev = nullptr;
            pointer next = nullptr;

            void hook (pointer elem)
            {
                elem->prev->next = this;
                next = elem;
                prev = elem->prev;
                elem->prev = this;
            }

            void unhook ()
            {                
                next->prev = prev;
                prev->next = next;
                prev = nullptr;
                next = nullptr;
            }
        };
        
        struct node : public base_node
        {
            T data;
            node (const T& val) : data(val) {};
        };
        
        struct node_iterator
        {
			typedef T         value_type;
			typedef ptrdiff_t difference_type;
			typedef base_node* pointer;
			typedef node_iterator& reference;
			typedef std::bidirectional_iterator_tag	iterator_category;
			
			node_iterator(base_node* val = nullptr) : node_ptr(val) {}	
			pointer node_ptr;
			
			node_iterator& operator++()
			{
				node_ptr = node_ptr->next;
				return *this;
			}
			
			node_iterator operator++(int)
			{
				base_node* tmp = node_ptr;
				node_ptr = node_ptr->next;
				return tmp;
			}
			
			node_iterator operator--(int)
			{
				base_node* tmp = node_ptr;
				node_ptr = node_ptr->prev;
				return tmp;
			}
			
            node_iterator& operator--()
            {
                node_ptr = node_ptr->prev;
                return *this;
            }

			bool operator == (node_iterator node)
			{
				return node_ptr == node.node_ptr;
			}	
			
			bool operator!= (node_iterator node)
			{
				return node_ptr != node.node_ptr;
			}	
			
			value_type& operator*()
			{
				return reinterpret_cast<node*>(node_ptr)->data;
			}
			
		};	

        void init()
        {
            sentinel.next = &sentinel;
            sentinel.prev = &sentinel;
        }

        void _clear()
        {
            while(begin() != end())
                erase (begin());
        }

        base_node sentinel;

    public:

        List ()
        {
            init();
        }

        ~List ()
        {
            _clear();
        }

        void clear()
        {
            _clear();
            init();
        }

        node_iterator insert(node_iterator position, const T& val)
        {
            node *elem = new node(val);
            elem->hook(position.node_ptr);
            return elem;
        }

        node_iterator erase(node_iterator position)
        {
            node_iterator tmp(position.node_ptr->next);
            position.node_ptr->unhook();
            delete position.node_ptr;
            return tmp;
        }

        void push_front(const T& val)
        {
            insert(begin(), val);
        }

        void push_back(const T& val)
        {
            insert(end(), val);
        }

        void pop_front()
        {
            erase(begin());
        }

        void pop_back()
        {
            node_iterator tmp = end();
            erase(--tmp);
        }

        bool empty()
        {
            return &sentinel == sentinel.prev;   
        }
    
        size_type size()
        {
            return std::distance(begin(), end());
        }

        node_iterator begin()
        {
            return sentinel.next;
        }

        node_iterator end()
        {
            return &sentinel;
        }

        size_type max_size()
        {
            return std::numeric_limits<size_type>::max();
        }
        
        T& front()
        {
            return *begin();
        }
        
        T& back ()
        {
            node_iterator tmp;
            tmp = end();
            return *(--tmp);
        }
        
        void assign (node_iterator first, node_iterator last)
        {
            node_iterator frst = begin();
            node_iterator lst = end();

            while (first != last && frst != lst)
            {
    
                *first = *frst;
                ++first;
                ++frst;
            }
            if(first == last)
            {
               while (frst != lst)
               {
                    erase(frst);
                    ++frst;
               }
            }   
            else
            {
                while (first != last)
                {
                    push_back(*first);
                    ++first;
                }
            }
        }  
        
        void assign (size_type n, const value_type& val)
        {
            while (!empty())
            {
                data = val;
                if (n > size())
                {
                    push_back(val);
                }
                
           }

        }
.3
    };



