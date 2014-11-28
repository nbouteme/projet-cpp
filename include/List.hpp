#pragma once

namespace nsSdD
{
    template <typename T>
    class List
    {
        struct base_node
        {
            typedef node* pointer;
    
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
            node (const T& val) : val(data) {};
        };

        void init()
        {
            sentinel.next = &sentinel;
            sentinel.prev = &sentinel;
        }

        void _clear()
        {
            while(begin() != end())
            {
                erase (begin());
            }
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

        void insert(node_iterator position, const T& val)
        {
            node *elem = new node(val);
            elem->hook(position.node_ptr);
        }

        void erase(node_iterator position)
        {
            position.node_ptr->unhook();
            delete position.node_ptr;
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
            return &sentinel == sentinel->prev;   
        }
    
        size_type size()
        {
            return std::distance(begin,end);
        }

        size_type max_size()
        {
            return std::numeric_limits<size_type>::max();
        }

    };
}


