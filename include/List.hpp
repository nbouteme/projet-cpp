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
    class CList
    {
        typedef size_t size_type;
        typedef CNodeIterator iterator;
        
        struct CNodeIterator
        {
            typedef T                                   value_type;
            typedef ptrdiff_t                           difference_type;
            typedef CBaseNode*                          pointer;
            typedef CNodeIterator&                      reference;
            typedef std::bidirectional_iterator_tag     iterator_category;
    

            CNodeIterator(CBaseNode* val = nullptr) : m_CNodePtr(val) {}
            pointer m_CNodePtr;

            CNodeIterator operator++()
            {
                m_CNodePtr = m_CNodePtr->m_next;
                return *this;
            }

            CNodeIterator operator++(int)
            {
                CBaseNode* tmp = m_CNodePtr;
                m_CNodePtr = m_CNodePtr->m_next;
                return tmp;
            }

            CNodeIterator operator--(int)
            {
                CBaseNode* tmp = m_CNodePtr;
                m_CNodePtr = m_CNodePtr->m_prev;
                return tmp;
            }

            CNodeIterator operator--()
            {
                m_CNodePtr = m_CNodePtr->m_prev;
                return *this;
            }

            bool operator== (iterator CNode)
            {
                return m_CNodePtr == CNode.m_CNodePtr;
            }

            pointer operator->()
            {
                return reinterpret_cast<CNode<T>*>(m_CNodePtr);
            }

            bool operator!= (const iterator& CNode)
            {
                return m_CNodePtr != CNode.m_CNodePtr;
            }

            value_type& operator*()
            {
                return reinterpret_cast<CNode<T>*>(m_CNodePtr)->m_data;
            }
        };

        void init()
        {
            m_sentinel->m_next = m_sentinel.get();
            m_sentinel->m_prev = m_sentinel.get();
        }

        void _clear()
        {
            while(!empty())
                erase(begin());
        }

        void transfer(iterator position, iterator first, iterator last)
        {
            position.m_CNodePtr->transfer(first.m_CNodePtr, last.m_CNodePtr);
        }

        // Attention mesdames et messieurs c'est de la haute technique!
        std::shared_ptr<CBaseNode> m_sentinel = std::make_shared<CBaseNode>();
        //C'est literallement identique que
        //CBaseCNode m_sentinel;
        // si ce n'est que c'est plus lent a instancier, et plus long
        // a ecrire et necessite de rajouter des .get() de partout les
        // weak pointer sont literallement inutilisable dans notre
        // contexte on a une classe CBaseCNode qui ne contient pas de
        // donnee, et une classe CNode<T> qui contient des donnee la
        // classe base CNode<T> est utilisee directement seulement par
        // la m_sentinelle alors c'est elle qui devrait etre
        // proprietaire et responsable de la liberation de la memoire,
        // et donc ses membres m_next et m_prev devrait etre des shared
        // ptr mais du coup, on perd la relation entre CBaseCNode et
        // CNode<T> car CNode<T> ne doit alors avoir que des membre qui
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
        CList()
        {
            init();
        }

        CList(size_type n, const T& val = T()) : CList()
        {
            while(n)
                push_back(val), --n;
        }

        CList(const CList& x) : CList()
        {
            for(auto &val : x)
                push_back(val);
        }

        CList(iterator first, iterator last) : CList()
        {
            insert(end(), first, last);
        }

        ~CList()
        {
            _clear();
        }

        CList<T>& operator=(const CList<T> &rhs)
        {
            if(this == &rhs) return *this;
            assign(rhs.begin(), rhs.end());
            return *this;
        }

        void unique()
        {
            if(empty()) return;
            CNodeIterator first = begin();
            CNodeIterator last  = end();
            CNodeIterator m_next  = first;
            while(++m_next != last)
            {
                if(*first == *m_next)
                    erase(m_next);
                else
                    first = m_next;
                m_next = first;
            }
        }

        void clear()
        {
            _clear();
            init();
        }

        // [23.3.5.4]
        // 12. Suprime tout les element de la CListe si *it = val
        // 13. Ne leve pas d'exception sauf si la comparaison est surchargée tel que elle puisse en lever une
        void remove (const T& val)
        {
            for(CNodeIterator it = begin(); it != end(); ++it)
                if(*it == val)
                    it = erase(it);
        }

        void remove_if(std::function<bool(const T&)> predicate)
        {
            CNodeIterator it = begin();
            while(it != end())
                if (predicate(*it))
                    it = erase(it++);
        }

        // [23.3.5.4]
        // 1. L'insertion dans la CListe n'affecte pas la validité des iterateur existant
        // 2. L'insertion de plusieurs element est linéaire.
        CNodeIterator insert (iterator position, iterator first, iterator last)
        {
            CList t(first, last);
            CNodeIterator tmp = t.begin();
            splice(position, t);
            return tmp;
        }

        // [23.3.5.4]
        // 1. L'insertion dans la CListe n'affecte pas la validité des iterateur existant
        // 2. L'insertion d'un seul élément est constante.
        CNodeIterator insert(iterator position, const T& val)
        {
            CNode<T> *elem = new CNode<T>(val);
            elem->hook(position.m_CNodePtr);
            return elem;
        }

        CNodeIterator insert(iterator position, size_type n, const T& val)
        {
            if(n == 0) return position;
            CList tmp(n, val);
            CNodeIterator ret = tmp.begin();
            splice(position, tmp);
            // le standard dis que meme en modifian la CListe, les
            // iterateur reste valides, mais pointent maintenant vers
            // un element de cette CListe
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
        CNodeIterator erase(iterator position)
        {
            CNodeIterator tmp(position.m_CNodePtr->m_next);
            position.m_CNodePtr->unhook();
            delete position.m_CNodePtr;
            return tmp;
        }

        // [23.3.5.4]
        // 1. La supresseion d'un element n'affecte que les iterateurs sur cet element
        // 2. La supression de plusieurs elements est linéaire.
        CNodeIterator erase(iterator first, iterator last)
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
            CNodeIterator tmp = end();
            erase(--tmp);
        }

        bool empty()
        {
            return m_sentinel.get() == m_sentinel->m_prev;
        }

        // La complexité est constante, pour eviter d'avoir un autre membre et de devoir mettre a jour ce rendre qui rendrait splice lineaire.
        size_type size()
        {
            return std::distance(begin(), end());
        }

        CNodeIterator begin() const
        {
            return m_sentinel->m_next;
        }

        CNodeIterator end() const
        {
            return m_sentinel->m_next->m_prev;
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
            CNodeIterator tmp;
            tmp = end();
            return *(--tmp);
        }

        void assign (iterator first, iterator last)
        {
            CNodeIterator frst = begin();
            CNodeIterator lst = end();

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
        void swap(CList& x)
        {
            CBaseNode::swap(*m_sentinel, *x.m_sentinel);
        }

        // [23.3.5.5]
        // 2. splice detruit une CListe en deplacant ses elements vers une autre
        // 4. x devient vide
        // 5. compléxité: constante
        void splice(iterator position, CList& x)
        {
            if(&x != this) // [23.3.5.5] 3
            position.m_CNodePtr->transfer(x.begin().m_CNodePtr, x.end().m_CNodePtr);
        }

        // [23.3.5.5]
        // 6. deplace i avant position si x possede le meme allocateur que this
        // et n'affecte pas la CListe si position == i ou ++i
        // 7. i doit etre valide
        // 8. complexité constante
        void splice(iterator position, CList& x, iterator i)
        {
            (void)x;
            CNodeIterator j = i;
            ++j;
            if(position == i || position == j) return;
            position.m_CNodePtr->transfer(i.m_CNodePtr, j.m_CNodePtr);
        }

        // [23.3.5.5]
        // 9.deplace les elements de x dans l'interval [first;last[ avant position
        // 10.comportement indefini si position est entre first et last
        // 11.Complexité constante si &x == this, et au moins lineaire dans le cas contraire.
        // mais notre implementation est constante dans les 2 cas
        void splice(iterator position, CList& x, iterator first, iterator last)
        {
            (void)x;
            position.m_CNodePtr->transfer(first, last);
        }

        // [23.3.5.5]
        // 23. Inverse l'ordre de la CListe
        // Complexité lineaire
        void reverse()
        {
            if(!empty() && m_sentinel->m_next->m_next != m_sentinel.get())
                m_sentinel->reverse();
        }

        // [23.3.5.5]
        // 4. T doit être copiable
        void resize(size_type n, const T& val = T())
        {
            CNodeIterator first = begin();
            CNodeIterator last = end();
            while(first != last && --n) ++first;
            if(first != last)//on reduit
                erase(first, last);
            else//ou on rajoute ce qui manque
                insert(last, n - std::distance(first, last));
        }

        // [23.3.5.5]
        // 19. *this et x doivent etre trié, autrement le comportement est indéfini 
        // 20. ne fait rien si &x == this, sinon, fusionne les 2 CListes en detruisant x
        // les iterateur sont toujours valide, sauf que ils pointent sur des membre de *this au lieu de x
        // 21. x devient vide
        // 22. complexité lineraire
        void merge(CList& x)
        {
            merge(x, [](const T &a, const T& b){ return a < b; });
        }

        void merge(CList& x, std::function<bool(const T &a, const T& b)> comp)
        {
            if(this == &x) return; //on ne merge pas avec elle meme !

            CNodeIterator first  =   begin();
            CNodeIterator first2 = x.begin();

            CNodeIterator last   =   end();
            CNodeIterator last2  = x.end();

            while (first != last && first2 != last2)//jusqua la fin d'une des CListes
                if (comp(*first2, *first)) // si l'element de la 2eme CList est inf
                {
                    CNodeIterator m_next = first2;//on sauvegarde le suivant
                    transfer(first, first2, ++m_next);//et on transfere l'element
                    first2 = m_next; // avance dans la seconde CListe
                }
                else
                    ++first; // avance dans la premiere CListe

            if (first2 != last2)// on est arrivé a la fin de la 1ere CListe
                transfer(last, first2, last2);//tout le reste va a la fin
        }

        // [23.3.5.5]
        // 25. Necessite la comparaison <
        // 26. Trie la CListe sans affecter la validité des iterateur existant
        // 27. Stable (l'ordre d'element egaux ne change pas)
        // 28. Complexité N log N
        void sort()
        {
            // merge s'attend a avoir une CListe deja triee en parametre,
            // donc on peut l'utiliser pour notre mergesort O(N log N)

            if (m_sentinel->m_next != m_sentinel.get() &&
                m_sentinel->m_next->m_next != m_sentinel.get()) // une CListe vide ou avec 1 element est deja triee
            {
                CList reg;//cette CListe repartie les element dans les partitions
                CList tmp[sizeof(void*) << 3];
                // CListes de partitionements, le nombre de CListe
                // utilisées est depend du nombre d'element a trier,
                // le nombre de CListe depends de la quantite de donnee adressable dans la ram de la machine,
                // l'algo foire si on a un ensemble de donnee a trier
                // de plus de quelque dizaines d'exibytes (enfin moins
                // car par exemple sous linux la taille max d'un
                // pointeur en user-space est de 48bits)
                // sizeof(void*) << 3 veut juste dire "assez de CListe
                // pour ne pas deborder", puisque pour deborder faut
                // avoir plus d'element a trier que de memoire
                // addressable
                CList *last = &tmp[0];//pointeur sur la derniere CListe de partition utilisé
                CList *counter;// pointeur sur la CListe de partition

                do
                {
                    reg.splice(reg.begin(), *this, begin());//on met le debut de notre CListe dans une CList temporaire

                    for(counter = &tmp[0];//a partir de la premiere CListe de partition
                        counter != last && !counter->empty();//pour chaque CListe de part non vide utilisée
                        ++counter)
                    {
                        counter->merge(reg);//reg devient vide, et ses elements sont placé correctement dans la CListe courante
                        reg.swap(*counter); //et on recupere cette CListe pour le traitement
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
    void swap(CList<T>& x, CList<T>& y)
    {
        x.swap(y);
    }
}
