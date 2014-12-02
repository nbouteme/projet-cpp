#pragma once

#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>

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

            void transfer(node_iterator first, node_iterator last)
            {
                if (last.node_ptr != this)
                {
                       last->prev->next = this;
                       first->prev->next = last;
                       this->prev->next = first;
                       pointer tmp_this = this->prev;
                       this->prev = last->prev;
                       first->prev = last->prev->next;
                       first->prev = tmp_this;
                }
            }

            void reverse()
            {
                base_node* tmp = this;
                do
                {
                    std::swap(tmp->prev, tmp->next);
                    tmp = tmp->prev;
                } while(this != tmp);
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
            typedef std::bidirectional_iterator_tag     iterator_category;
            typedef const base_node* const_pointer;
            typedef const node_iterator& const_reference;

            node_iterator(base_node* val = nullptr) : node_ptr(val) {}
            pointer node_ptr;

            const_reference operator++()
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

            const_reference operator--()
            {
                node_ptr = node_ptr->prev;
                return *this;
            }

            bool operator == (node_iterator node)
            {
                return node_ptr == node.node_ptr;
            }

            value_type* operator->()
                {
                    return &reinterpret_cast<node*>(node_ptr)->data;
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

        struct const_node_iterator
        {
            typedef T         value_type;
            typedef ptrdiff_t difference_type;
            typedef base_node* pointer;
            typedef node_iterator& reference;
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef const base_node* const_pointer;
            typedef const node_iterator& const_reference;

            const_node_iterator(const base_node* val = nullptr) : node_ptr(val) {}
            const_node_iterator(const node_iterator& val) : node_ptr(val.node_ptr) {}
            const pointer node_ptr;

            const_reference operator++()
            {
                node_ptr = node_ptr->next;
                return *this;
            }

            const node_iterator operator++(int)
            {
                base_node* tmp = node_ptr;
                node_ptr = node_ptr->next;
                return tmp;
            }

            const node_iterator operator--(int)
            {
                base_node* tmp = node_ptr;
                node_ptr = node_ptr->prev;
                return tmp;
            }

            const_reference operator--()
            {
                node_ptr = node_ptr->prev;
                return *this;
            }

            bool operator  == (node_iterator node) const
            {
                return node_ptr == node.node_ptr;
            }

            const value_type* operator->() const
            {
                return &reinterpret_cast<node*>(node_ptr)->data;
            }

            bool operator!= (node_iterator node) const
            {
                return node_ptr != node.node_ptr;
            }

            const_reference operator*()
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

        node_iterator insert (node_iterator position, node_iterator first, node_iterator last)
        {
            while(first != last)
                insert(position, *first),
                ++first;
        }



        void unique()
        {
            node_iterator it = begin();
            while(it != end())
            {
                while(*it == it.node_ptr->next->data)
                    erase(it.node_ptr->next);
                it++;
            }
        }


        void clear()
        {
            _clear();
            init();
        }


         void remove (const T& val)
        {
            for(node_iterator it = begin(); it != end(); ++it)
                if (*it == val)
                {
                    erase(it);
                    return;
                }
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

        void swap(List& x)
        {
            std::swap(sentinel, x.sentinel);
        }

        void splice(node_iterator position, List& x, node_iterator first, node_iterator last)
        {
            position.node_ptr->transfer(first, last);
        }

        void reverse()
        {
            if(!empty() && sentinel.next->next != &sentinel)
            {
                sentinel.reverse();
            }
        }

        void remove_if(std::function<bool(const T&)> predicate)
        {
            node_iterator it = begin();
            while(it != end())
                if (predicate(*it))
                    erase(it++);
        }
    };
}
