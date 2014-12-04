#pragma once

#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>
#include <cassert>

namespace nsSdD
{
    template <typename T>
    class List
    {
        struct node_iterator;
        typedef size_t size_type;

        struct base_node
        {
            typedef base_node* pointer;

            pointer prev = nullptr;
            pointer next = nullptr;
            void hook(pointer elem)
            {
                next = elem;
                prev = elem->prev;
                elem->prev->next = this;
                elem->prev = this;
            }

            void unhook()
            {
                 prev->next = next;
                 next->prev = prev;
                 prev = nullptr;
                 next = nullptr;
            }

            void transfer(base_node* first, base_node* last)
            {
                if(last != this)
                {
                    last->prev->next = this;
                    first->prev->next = last;
                    prev->next = first;
                    pointer tmp_this = prev;
                    prev = last->prev;
                    last->prev = first->prev;
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

            static void swap(base_node& x, base_node& y)
            {
                if (x.next != &x)
                {// x non vide
                    if(y.next != &y)
                    {// et y non vide
                        std::swap(x.next, y.next);
                        std::swap(x.prev, y.prev);//echange les lien internes a x et y
                        x.next->prev = x.prev->next = &x;//les precedent et suivant etait ceux de y, donc on reassigne
                        y.next->prev = y.prev->next = &y;
                    }
                    else
                    {// et y vide
                        y.next = x.next;
                        y.prev = x.prev;//reconstitue les pointeurs internes a x
                        y.next->prev = y.prev->next = &y; //reconsitue les pointeur sur x
                        x.next = x.prev = &x;//x devient vide
                    }
                }
                else if (y.next != &y)
                {// x vide et y non vide
                    x.next = y.next;
                    x.prev = y.prev;//reconstitue les pointeur internes a y
                    x.next->prev = x.prev->next = &x;//reconstitue les pointeurs sur y
                    y.next = y.prev = &y;//y devient vide
                }
            }
        };

        struct node : public base_node
        {
            T data;
            node (const T& val) : data(val) {}
        };

        struct node_iterator
        {
            typedef T                                   value_type;
            typedef ptrdiff_t                           difference_type;
            typedef base_node*                          pointer;
            typedef node_iterator&                      reference;
            typedef std::bidirectional_iterator_tag     iterator_category;
            typedef const base_node*                    const_pointer;
            typedef const node_iterator&                const_reference;

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

            pointer operator->()
            {
                return reinterpret_cast<node*>(node_ptr);
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
            while(!empty())
                erase(begin());
        }

        void transfer(node_iterator position, node_iterator first, node_iterator last)
        {
            position.node_ptr->transfer(first.node_ptr, last.node_ptr);
        }

        base_node sentinel;

    public:
        List()
        {
            init();
        }

        List(size_type n, const T& val = T()) : List()
        {
            insert(end(), n, val);
        }

        List(const List& x)
        {
            for(auto &val : x)
                push_back(val);
        }

        List(node_iterator first, node_iterator last)
        {
            insert(end(), first, last);
        }

        ~List()
        {
            _clear();
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
                if(*it == val)
                {
                    erase(it);
                    return;
                }
        }

        node_iterator insert (node_iterator position, node_iterator first, node_iterator last)
        {
            while(first != last)
                insert(position, *first),
                ++first;
        }

        node_iterator insert(node_iterator position, const T& val)
        {
            node *elem = new node(val);
            elem->hook(position.node_ptr);
            return elem;
        }

        node_iterator insert(node_iterator position, size_type n, const T& val)
        {
            if(n == 0) return position;
            List tmp(n, val);
            node_iterator ret = tmp.begin();
            splice(position, tmp);
            // le standard dis que meme en modifian la liste, les
            // iterateur reste valides, mais pointent maintenant vers
            // un element de cette liste
            return ret;
        }

        node_iterator erase(node_iterator position)
        {
            node_iterator tmp(position.node_ptr->next);
            position.node_ptr->unhook();
            delete position.node_ptr;
            return tmp;
        }

        node_iterator erase(node_iterator first, node_iterator last)
        {
            while(first != last)
                erase(first), ++first;
            return last;
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

        void swap(List& x)
        {
            base_node::swap(sentinel, x.sentinel);
        }

        void splice(node_iterator position, List& x)
        {
            position.node_ptr->transfer(x.begin(), x.end());
        }

        // D'apres le standard, x est censé être utilisé pour verifier si le
        // type d'allocator est le meme
        void splice(node_iterator position, List& x, node_iterator i)
        {
            (void)x;
            node_iterator j = i;
            ++j;
            if(position == i || position == j) return;
            position.node_ptr->transfer(i.node_ptr, j.node_ptr);
        }

        void splice(node_iterator position, List& x, node_iterator first, node_iterator last)
        {
            position.node_ptr->transfer(first, last);
        }

        void reverse()
        {
            if(!empty() && sentinel.next->next != &sentinel)
                sentinel.reverse();
        }

        void remove_if(std::function<bool(const T&)> predicate)
        {
            node_iterator it = begin();
            while(it != end())
                if (predicate(*it))
                    erase(it++);
        }

        void merge(List& x)
        {
            merge(x, [](const T &a, const T& b){ return a < b; });
        }

        void resize(size_type n, const T& val = T())
        {
            node_iterator first = begin();
            node_iterator last = end();
            while(first != last && --n) ++first;
            if(first != last)//on reduit
                erase(first, last);
            else//ou on rajoute ce qui manque
                insert(last, n - std::distance(first, last));
        }

        void merge(List& x, std::function<bool(const T &a, const T& b)> comp)
        {
            if(this == &x) return; //on ne merge pas avec elle meme !

            node_iterator first  =   begin();
            node_iterator first2 = x.begin();

            node_iterator last   =   end();
            node_iterator last2  = x.end();

            while (first != last && first2 != last2)//jusqua la fin d'une des listes
                if (comp(*first2, *first)) // si l'element de la 2eme List est inf
                {
                    node_iterator next = first2;//on sauvegarde le suivant
                    transfer(first, first2, ++next);//et on transfere l'element
                    first2 = next; // avance dans la seconde liste
                }
                else
                    ++first; // avance dans la premiere liste

            if (first2 != last2)// on est arrivé a la fin de la 1ere liste
                transfer(last, first2, last2);//tout le reste va a la fin
        }

        void sort()
        {
            // merge s'attend a avoir une liste deja triee en parametre,
            // donc on peut l'utiliser pour notre mergesort O(N log N)

            if (sentinel.next       != &sentinel &&
                sentinel.next->next != &sentinel) // une liste vide ou avec 1 element est deja triee
            {
                List reg;//cette liste repartie les element dans les partitions
                List tmp[sizeof(void*) << 3];
                // listes de partitionements, le nombre de liste
                // utilisées est depend du nombre d'element a trier,
                // le nombre de liste depends de la quantite de donnee adressable dans la ram de la machine,
                // l'algo foire si on a un ensemble de donnee a trier
                // de plus de quelque dizaines d'exibytes (enfin moins
                // car par exemple sous linux la taille max d'un
                // pointeur en user-space est de 48bits)
                // sizeof(void*) << 3 veut juste dire "assez de liste
                // pour ne pas deborder", puisque pour deborder faut
                // avoir plus d'element a trier que de memoire
                // addressable
                List *last = &tmp[0];//pointeur sur la derniere liste de partition utilisé
                List *counter;// pointeur sur la liste de partition

                do
                {
                    reg.splice(reg.begin(), *this, begin());//on met le debut de notre liste dans une list temporaire

                    for(counter = &tmp[0];//a partir de la premiere liste de partition
                        counter != last && !counter->empty();//pour chaque liste de part non vide utilisée
                        ++counter)
                    {
                        counter->merge(reg);//reg devient vide, et ses elements sont placé correctement dans la liste courante
                        reg.swap(*counter); //et on recupere cette liste pour le traitement
                    }
                    reg.swap(*counter);//la partition est faite
                    last += counter == last;//on incremente la partition
                }
                while (!empty());

                for(counter = &tmp[1]; counter != last; ++counter)
                    counter->merge(*(counter - 1));//on combine toutes nos partitions

                swap(*(last - 1));//last pointe sur apres la derniere qui contien le resultat final
            }
        }
    };
}
