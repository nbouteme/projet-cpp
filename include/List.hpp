#pragma once

#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>
#include <cassert>
#include <node.hpp>

namespace nsSdD
{
    // L'implémentation utilise un minimum vital de smart_pointer (aka
    // pas de weak_ptr), car deja ca a rien a foutre dans une
    // structure de donnee complexe, ensuite la gestion de la memoire
    // etait parfaite a la base, mais maintenant avec les
    // smart_pointer on a encore plus de problemes a resoudre. Les
    // weak ptr font une pagaille pas croyable dans le code. Mais bon
    // sa c'est un eu faute d'avoir choisi d'implementer une liste
    // circulaire. Au final, la liste est plus grosse et plus lente
    // que ce quel a besoin d'etre
    template <typename T>
    class List
    {
        struct node_iterator;
        typedef size_t size_type;

        struct node_iterator
        {
            typedef T                                   value_type;
            typedef ptrdiff_t                           difference_type;
            typedef base_node*                          pointer;
            typedef node_iterator&                      reference;
            typedef std::bidirectional_iterator_tag     iterator_category;

            node_iterator(base_node* val = nullptr) : node_ptr(val) {}
            pointer node_ptr;

            node_iterator operator++()
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

            node_iterator operator--()
            {
                node_ptr = node_ptr->prev;
                return *this;
            }

            bool operator== (node_iterator node)
            {
                return node_ptr == node.node_ptr;
            }

            pointer operator->()
            {
                return reinterpret_cast<node<T>*>(node_ptr);
            }

            bool operator!= (const node_iterator& node)
            {
                return node_ptr != node.node_ptr;
            }

            value_type& operator*()
            {
                return reinterpret_cast<node<T>*>(node_ptr)->data;
            }
        };

        void init()
        {
            sentinel->next = sentinel.get();
            sentinel->prev = sentinel.get();
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

        // Attention mesdames et messieurs c'est de la haute technique!
        std::shared_ptr<base_node> sentinel = std::make_shared<base_node>();
        //C'est literallement identique que
        //base_node sentinel;
        // si ce n'est que c'est plus lent a instancier, et plus long
        // a ecrire et necessite de rajouter des .get() de partout les
        // weak pointer sont literallement inutilisable dans notre
        // contexte on a une classe base_node qui ne contient pas de
        // donnee, et une classe node<T> qui contient des donnee la
        // classe base node<T> est utilisee directement seulement par
        // la sentinelle alors c'est elle qui devrait etre
        // proprietaire et responsable de la liberation de la memoire,
        // et donc ses membres next et prev devrait etre des shared
        // ptr mais du coup, on perd la relation entre base_node et
        // node<T> car node<T> ne doit alors avoir que des membre qui
        // sont weak les const& et le polymorphisme avec les
        // shared_ptr sont mutuellement exclusif aussi
        // class A{};
        // class B : A{};
        // void f(const shared_ptr<A>&){}
        // int main(int argc, char *argv[])
        // {
        //     shared_ptr<B> b = make_shared<B>();
        //     f(b);
        //     return 0;
        // }
        // ne compile pas
    public:
        List()
        {
            init();
        }

        List(size_type n, const T& val = T()) : List()
        {
            while(n)
                push_back(val), --n;
        }

        List(const List& x) : List()
        {
            for(auto &val : x)
                push_back(val);
        }

        List(node_iterator first, node_iterator last) : List()
        {
            insert(end(), first, last);
        }

        ~List()
        {
            _clear();
        }

        List<T>& operator=(const List<T> &rhs)
        {
            if(this == &rhs) return *this;
            assign(rhs.begin(), rhs.end());
            return *this;
        }

        void unique()
        {
            if(empty()) return;
            node_iterator first = begin();
            node_iterator last  = end();
            node_iterator next  = first;
            while(++next != last)
            {
                if(*first == *next)
                    erase(next);
                else
                    first = next;
                next = first;
            }
        }

        void clear()
        {
            _clear();
            init();
        }

        // [23.3.5.4]
        // 12. Suprime tout les element de la liste si *it = val
        // 13. Ne leve pas d'exception sauf si la comparaison est surchargée tel que elle puisse en lever une
        void remove (const T& val)
        {
            for(node_iterator it = begin(); it != end(); ++it)
                if(*it == val)
                    it = erase(it);
        }

        void remove_if(std::function<bool(const T&)> predicate)
        {
            node_iterator it = begin();
            while(it != end())
                if (predicate(*it))
                    it = erase(it++);
        }

        // [23.3.5.4]
        // 1. L'insertion dans la liste n'affecte pas la validité des iterateur existant
        // 2. L'insertion de plusieurs element est linéaire.
        node_iterator insert (node_iterator position, node_iterator first, node_iterator last)
        {
            List t(first, last);
            node_iterator tmp = t.begin();
            splice(position, t);
            return tmp;
        }

        // [23.3.5.4]
        // 1. L'insertion dans la liste n'affecte pas la validité des iterateur existant
        // 2. L'insertion d'un seul élément est constante.
        node_iterator insert(node_iterator position, const T& val)
        {
            node<T> *elem = new node<T>(val);
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

        void push_front(const T& val)
        {
            insert(begin(), val);
        }

        void push_back(const T& val)
        {
            insert(end(), val);
        }

        // [23.3.5.4]
        // 1. La supresseion d'un element n'affecte que les iterateurs sur cet element
        // 2. La supression d'un seul élément est constante.
        node_iterator erase(node_iterator position)
        {
            node_iterator tmp(position.node_ptr->next);
            position.node_ptr->unhook();
            delete position.node_ptr;
            return tmp;
        }

        // [23.3.5.4]
        // 1. La supresseion d'un element n'affecte que les iterateurs sur cet element
        // 2. La supression de plusieurs elements est linéaire.
        node_iterator erase(node_iterator first, node_iterator last)
        {
            while(first != last)
                first = erase(first);
            return last;
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
            return sentinel.get() == sentinel->prev;
        }

        // La complexité est constante, pour eviter d'avoir un autre membre et de devoir mettre a jour ce rendre qui rendrait splice lineaire.
        size_type size()
        {
            return std::distance(begin(), end());
        }

        node_iterator begin() const
        {
            return sentinel->next;
        }

        node_iterator end() const
        {
            return sentinel->next->prev;
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
                *frst = *first,
                ++first,
                ++frst;
            if(first == last)
                erase(frst, lst);
            else
                insert(lst, first, last);
        }

        // Swap a complexité constante
        void swap(List& x)
        {
            base_node::swap(*sentinel, *x.sentinel);
        }

        // [23.3.5.5]
        // 2. splice detruit une liste en deplacant ses elements vers une autre
        // 4. x devient vide
        // 5. compléxité: constante
        void splice(node_iterator position, List& x)
        {
            if(&x != this) // [23.3.5.5] 3
            position.node_ptr->transfer(x.begin().node_ptr, x.end().node_ptr);
        }

        // [23.3.5.5]
        // 6. deplace i avant position si x possede le meme allocateur que this
        // et n'affecte pas la liste si position == i ou ++i
        // 7. i doit etre valide
        // 8. complexité constante
        void splice(node_iterator position, List& x, node_iterator i)
        {
            (void)x;
            node_iterator j = i;
            ++j;
            if(position == i || position == j) return;
            position.node_ptr->transfer(i.node_ptr, j.node_ptr);
        }

        // [23.3.5.5]
        // 9.deplace les elements de x dans l'interval [first;last[ avant position
        // 10.comportement indefini si position est entre first et last
        // 11.Complexité constante si &x == this, et au moins lineaire dans le cas contraire.
        // mais notre implementation est constante dans les 2 cas
        void splice(node_iterator position, List& x, node_iterator first, node_iterator last)
        {
            (void)x;
            position.node_ptr->transfer(first, last);
        }

        // [23.3.5.5]
        // 23. Inverse l'ordre de la liste
        // Complexité lineaire
        void reverse()
        {
            if(!empty() && sentinel->next->next != sentinel.get())
                sentinel->reverse();
        }

        // [23.3.5.5]
        // 4. T doit être copiable
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

        // [23.3.5.5]
        // 19. *this et x doivent etre trié, autrement le comportement est indéfini 
        // 20. ne fait rien si &x == this, sinon, fusionne les 2 listes en detruisant x
        // les iterateur sont toujours valide, sauf que ils pointent sur des membre de *this au lieu de x
        // 21. x devient vide
        // 22. complexité lineraire
        void merge(List& x)
        {
            merge(x, [](const T &a, const T& b){ return a < b; });
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

        // [23.3.5.5]
        // 25. Necessite la comparaison <
        // 26. Trie la liste sans affecter la validité des iterateur existant
        // 27. Stable (l'ordre d'element egaux ne change pas)
        // 28. Complexité N log N
        void sort()
        {
            // merge s'attend a avoir une liste deja triee en parametre,
            // donc on peut l'utiliser pour notre mergesort O(N log N)

            if (sentinel->next       != sentinel.get() &&
                sentinel->next->next != sentinel.get()) // une liste vide ou avec 1 element est deja triee
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

    // specialisation de complexité constante de swap au lieu d'etre lineaire
    template <class T>
    void swap(List<T>& x, List<T>& y)
    {
        x.swap(y);
    }
}
