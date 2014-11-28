#pragma once

namespace nsSdD
{
    template <typename T>
    class List
    {
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

    };
}
