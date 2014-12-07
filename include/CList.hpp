#pragma once

#include <cstddef>
#include <limits>
#include <memory>

#include <CNode.hpp>

namespace nsSdD
{
    /**
     * \class CList
     * Circular list with memory being managed with a smart pointer
     */
    template <typename T>
    class CList
    {
        /// Iterator having iterator_traits, allowing to use it in a range-based for loop
        class CNodeIterator;

        /// Internal size type
        typedef size_t size_type;
        /// Internal iterator type
        typedef CNodeIterator iterator;
        
        class CNodeIterator
        {
	public:
            typedef T                                   value_type;
            typedef ptrdiff_t                           difference_type;
            typedef CBaseNode*                          pointer;
            typedef CNodeIterator&                      reference;
            typedef std::bidirectional_iterator_tag     iterator_category;

            /// Creates an iterator from a pointer to a node
            CNodeIterator(CBaseNode* val = nullptr) : m_CNodePtr(val) {}
            /// Pointer to the node being currently iterated
            pointer m_CNodePtr;

            /**
             * \brief Increments the iterator to point to the next node in the list
             * \return A reference to itself, now pointing to the next node.
             */
            reference operator++()
            {
                m_CNodePtr = m_CNodePtr->m_next;
                return *this;
            }

            /**
             * \brief Increments the iterator to point to the next node in the list
             * \return An iterator to the node, pre-incrementation.
             */
            iterator operator++(int)
            {
                CBaseNode* tmp = m_CNodePtr;
                m_CNodePtr = m_CNodePtr->m_next;
                return tmp;
            }

            /**
             * Decrements the iterator to point to the next node in the list
             * \return An iterator to the previous node, pre-decrementation.
             */
            iterator operator--(int)
            {
                CBaseNode* tmp = m_CNodePtr;
                m_CNodePtr = m_CNodePtr->m_prev;
                return tmp;
            }

            /**
             * Decrements the iterator to point to the next node in the list
             * \return A reference to itself, now pointing to the previous node.
             */
            reference operator--()
            {
                m_CNodePtr = m_CNodePtr->m_prev;
                return *this;
            }

            /**
             * Checks if an iterator is pointing on the same node as this.
             * \param CNode The node being compared.
             * \return True if the two iterators points on the same element
             */
            bool operator== (iterator CNode)
            {
                return m_CNodePtr == CNode.m_CNodePtr;
            }

            /**
             * \brief Allows to acess members of the underlying type
             * \return A pointer to the underlying object.
             */
            value_type* operator->()
            {
                return &reinterpret_cast<CNode<T>*>(m_CNodePtr)->m_data;
            }

            /**
             * \brief Checks if an iterator is pointing on the same node as this.
             * \param CNode The node being compared.
             * \return False if the two iterators points on the same element
             */
            bool operator!= (const iterator& CNode)
            {
                return m_CNodePtr != CNode.m_CNodePtr;
            }

            /**
             * \brief Dereference the iterator to access its underlying object
             * \return A reference to the underlying object
             */
            value_type& operator*()
            {
                return reinterpret_cast<CNode<T>*>(m_CNodePtr)->m_data;
            }
        };
    private:
        /// Initialize an empty list
        void init()
        {
            m_sentinel->m_next = m_sentinel.get();
            m_sentinel->m_prev = m_sentinel.get();
        }

        /// Remove every element in a list
        void _clear()
        {
            while(!empty())
                erase(begin());
        }

        /**
         * Moves a range [first;last[ from a list to another, and put it before \a position
         * \param position The element in the list to puts the elements in the range before.
         * \param first Iterator on the first element to move
         * \param last Iterator on the node following the last node to move
         */
        void transfer(iterator position, iterator first, iterator last)
        {
            position.m_CNodePtr->transfer(first.m_CNodePtr, last.m_CNodePtr);
        }

        /// Dummy element that allows to have certain guarantees on the integrity of a list
        std::shared_ptr<CBaseNode> m_sentinel = std::make_shared<CBaseNode>();
    public:
        /// Initializes an empty list
        explicit CList()
        {
            init();
        }

        /**
         * \brief Creates a list of \a n elements with a value of \a val
         * \param n The number of elements to create
         * \param val A value to copy 
         */
        CList(size_type n, const T& val = T()) : CList()
        {
            while(n)
                push_back(val), --n;
        }

        /**
         * \brief Creates a copy of \a x
         * \param x The list to copy
         */
        explicit CList(const CList& x) : CList()
        {
            for(auto &val : x)
                push_back(val);
        }

        /**
         * \brief Creates a list by copying the elements in the range [first;last[
         * \param first An iterator on the first element to copy
         * \param last An iterator on the next node of the last node to copy
         */
        CList(iterator first, iterator last) : CList()
        {
            insert(end(), first, last);
        }

        /// Frees the allocated ressources
        ~CList()
        {
            _clear();
        }

        /**
         * \brief Assigns the content of \a rhs to this
         * Assigns the content of \a rhs to this
         * \param rhs The Right Hand Side of the expression
         */
        CList<T>& operator=(const CList<T> &rhs)
        {
            if(this == &rhs) return *this;
            assign(rhs.begin(), rhs.end());
            return *this;
        }

        /// Remove duplicated consecutive elements
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

        /// Remove every elements in the list
        void clear()
        {
            _clear();
            init();
        }

        /**
         * \brief Remove every elements equal to \a val
         * Remove every elements in the list that are equal to \a val
         * \par Complexity
         * Linear.
         * \par Iterator Validity
         * Every iterators are still valid, except those on removed elements
         * \par Data races
         * Container is modified, removed elements are modified, iterating on removed elements is not safe.
         * \param val Value to compare
         */
        void remove(const T& val)
        {
            for(CNodeIterator it = begin(); it != end(); ++it)
                if(*it == val)
                    it = erase(it);
        }

        /**
         * Remove every elements in the list if the predicates evaluates to true
         * \param predicate Unary predicates evaluating to true for elements to be removed
         */
        void remove_if(std::function<bool(const T&)> predicate)
        {
            CNodeIterator it = begin();
            while(it != end())
                if (predicate(*it))
                    it = erase(it++);
        }

        /**
         * \brief Inserts a copy of every element in the range [\a first;\a last[ before \a position
         * \par Complexity
         * Linear.
         * \par Iterator Validity
         * Every iterators are still valid
         * \par Data races
         * Container is modified, no contained element are modified, acessing and iterating through the others elements is safe, except through
         * ranges including \a position
         * \param position Iterator on the element the range is copied before. 
         * \param first Iterator on the first element to be copied
         * \param last Iterator on the last element of the range
         * \return An iterator to the first added element
         */
        iterator insert (iterator position, iterator first, iterator last)
        {
            CList t(first, last);
            CNodeIterator tmp = t.begin();
            splice(position, t);
            return tmp;
        }

        /**
         * \brief Inserts a copy of \a val before \a position
         * \par Complexity
         * Constant.
         * \par Iterator Validity
         * Every iterators are still valid
         * \par Data races
         * Container is modified, no contained element are modified, acessing and iterating through the others elements is safe, except through
         * ranges including \a position
         * \param position Iterator on the element \a val is copied before. 
         * \param val The value to copy.
         * \return An iterator to the first added element
         */
        iterator insert(iterator position, const T& val)
        {
            CNode<T> *elem = new CNode<T>(val);
            elem->hook(position.m_CNodePtr);
            return elem;
        }

        /**
         * \brief Inserts \a n copy of \a val before \a position
         * \par Complexity
         * Linear.
         * \par Iterator Validity
         * Every iterators are still valid
         * \par Data races
         * Container is modified, no contained element are modified, acessing and iterating through the others elements is safe, except through
         * ranges including \a position
         * \param position Iterator on the element \a val is copied before. 
         * \param n The number of copies to insert before \a position.
         * \param val The value to copy.
         * \return An iterator to the first added element
         */
        iterator insert(iterator position, size_type n, const T& val)
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

        /**
         * Copies an element and put it at the beginning of the list
         * \param val The value to copie 
         */
        void push_front(const T& val)
        {
            insert(begin(), val);
        }

        /**
         * Copies an element and put it at the end of the list
         * \param val The value to copie 
         */
        void push_back(const T& val)
        {
            insert(end(), val);
        }

        /**
         * \brief Removes a node from the list, given an iterator \a position to it
         * \par Complexity
         * Constant.
         * \par Iterator Validity
         * Every iterator in the removed range are invalidated
         * \par Data races
         * Container is modified, removed elements are modified, acessing and iterating through the others elements is safe
         * \param position An iterator pointing the element to remove
         * \return An iterator to the element following the one deleted
         */
        iterator erase(iterator position)
        {
            CNodeIterator tmp(position.m_CNodePtr->m_next);
            position.m_CNodePtr->unhook();
            delete position.m_CNodePtr;
            return tmp;
        }

        /**
         * \brief Removes a range [\a first;\a last[ from the list
         * \par Complexity
         * Linear.
         * \par Iterator Validity
         * Every iterator in the removed range are invalidated
         * \par Data races
         * Container is modified, removed elements are modified, acessing and iterating through the others elements is safe
         * \param first An iterator to the first element to remove
         * \param last An iterator following the last element to remove
         * \return An iterator to the element following the last deleted element
         */
        iterator erase(iterator first, iterator last)
        {
            while(first != last)
                first = erase(first);
            return last;
        }

        /// Removes the first element of a list
        void pop_front()
        {
            erase(begin());
        }

        /// Removes the last element of a list
        void pop_back()
        {
            CNodeIterator tmp = end();
            erase(--tmp);
        }

        /**
         * \brief Checks whether a list is empty
         * \return True if the list is empty
         */
        bool empty() const noexcept
        {
            return m_sentinel.get() == m_sentinel->m_prev;
        }

        /**
         * \brief Computes the size of a list
         * \return The size of the list
         */
        size_type size() const noexcept
        {
            return std::distance(begin(), end());
        }

        /**
         * \brief Returns an iterator to the first element
         * \return An iterator to the first element
         */
        CNodeIterator begin() const noexcept
        {
            return m_sentinel->m_next;
        }

        /**
         * \brief Returns an iterator pointing after the last element.
         * \return An iterator pointing after the last element.
         */
        CNodeIterator end() const noexcept
        {
            return m_sentinel->m_next->m_prev;
        }

        /// Returns the maximum number of elements that the list container can hold.
        size_type max_size() const noexcept
        {
            return std::numeric_limits<size_type>::max();
        }

        /// Returns a reference to the first element of the list
        T& front() noexcept
        {
            return *begin();
        }

        /// Returns a reference to the last element of the list
        T& back () noexcept
        {
            CNodeIterator tmp;
            tmp = end();
            return *(--tmp);
        }

        /**
         * \brief Assigns the content of the list by the elements in the [\a first; \a last[ range
         * If the range is smaller than the current list size, the extra elements are erased.
         * If the range is bigger than the current list size, the extra elements are copied.
         * \par Complexity
         * Linear.
         * \par Iterator Validity
         * Every iterator are invalidated
         * \par Data races
         * Copied elements are accessed, container is modified, contained elements are modified
         * \param first An iterator to the first element to assign
         * \param last An iterator following the last element to assign
         */
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

        /**
         * \brief Swaps the content of two lists.
         * \par Complexity
         * Constant.
         * \par Iterator Validity
         * All iterator remain valid, but instead refers to elements in the other list
         * \par Data races
         * Both container are accessed, none of the contained elements are.
         * \param x A list to swap
         */
        void swap(CList& x)
        {
            CBaseNode::swap(*m_sentinel, *x.m_sentinel);
        }

        /**
         * \brief Move the content of a list before an element in another
         * Moves the content of x before the element pointed by position
         * \par Complexity
         * Constant.
         * \par Iterator Validity
         * All iterator remain valid, the iterators on the transfered element are now iterating in the other list
         * \par Data races
         * Both container are accessed, accessing and modifying elements is safe, iterating through is not safe.
         * \param position Iterator on the element to move before
         * \param x List to move before \a position
         */
        void splice(iterator position, CList& x)
        {
            if(&x != this) // [23.3.5.5] 3
                position.m_CNodePtr->transfer(x.begin().m_CNodePtr, x.end().m_CNodePtr);
        }

        /**
         * \brief Move an element from a list to another
         * Moves the element at \a i from the list \a x and put it before \a position
         * \par Complexity
         * Constant.
         * \par Iterator Validity
         * All iterator remain valid, the iterators on the transfered element are now iterating in the other list
         * \par Data races
         * Both container are accessed, accessing and modifying elements is safe, iterating through is not safe.
         * \param position Iterator on the element to move before
         * \param x List to move an element from
         * \param i Iterator on the element to move
         */
        void splice(iterator position, CList& x, iterator i)
        {
            (void)x;
            CNodeIterator j = i;
            ++j;
            if(position == i || position == j) return;
            position.m_CNodePtr->transfer(i.m_CNodePtr, j.m_CNodePtr);
        }

        /**
         * \brief Move a range of elements from a list to another
         * Moves the elements in the range [\a first; \a last[ from the list \a x and put them before \a position
         * \par Complexity
         * Constant.
         * \par Iterator Validity
         * All iterator remain valid, the iterators on \a x are now iterating in the other list
         * \par Data races
         * Both container are accessed, accessing and modifying elements is safe, iterating through is not safe.
         * \param position Iterator on the element to move before
         * \param x List to move an element from
         * \param first Iterator on the first element of the range
         * \param last Iterator on the last element of the range
         */
        void splice(iterator position, CList& x, iterator first, iterator last)
        {
            (void)x;
            position.m_CNodePtr->transfer(first, last);
        }

        /**
         * \brief Reverse the order of elements in a list
         * \par Complexity
         * Linear.
         * \par Iterator Validity
         * All iterator remain valid
         * \par Data races
         * Both container are accessed, accessing and modifying elements is safe, iterating through is not safe.
         */
        void reverse()
        {
            if(!empty() && m_sentinel->m_next->m_next != m_sentinel.get())
                m_sentinel->reverse();
        }

        /**
         * \brief Resize the container to n elements.
         * If n > size(), the extra element are default constructed or copies of \a val
         * else the list is truncated
         * \par Complexity
         * Linear.
         * \par Iterator Validity
         * All iterator remain valid, except the ones on the removed elements
         * \par Data races
         * Both container are accessed, removed elements are accessed, iterating throught the others is safe.
         * Iterating through the list concurrently is not safe
         * \param n The new size of the list
         * \param val Element to copy when creating elements in the container
         */
        void resize(size_type n, const T& val = T())
        {
            CNodeIterator first = begin();
            CNodeIterator last = end();
            while(first != last && --n) ++first;
            if(first != last)//on reduit
                erase(first, last);
            else//ou on rajoute ce qui manque
                insert(last, n - std::distance(first, last), val);
        }

        /**
         * \brief Merges two sorted lists into one
         * If the lists aren't sorted this causes undefined behavior
         * x is emptied after this operation
         * \par Complexity
         * Linear.
         * \par Iterator Validity
         * All iterator remain valid
         * \par Data races
         * Both container are accessed, contained elements are accessed but never modified.
         * Iterating through the list concurrently is not safe
         * \param x The list to merge into
         */
        void merge(CList& x)
        {
            merge(x, [](const T &a, const T& b){ return a < b; });
        }

        /**
         * \brief Merges two sorted lists into one
         * If the lists aren't sorted this causes undefined behavior
         * x is emptied after this operation
         * \par Complexity
         * Linear.
         * \par Iterator Validity
         * All iterator remain valid
         * \par Data races
         * Both container are accessed, contained elements are accessed but never modified.
         * Iterating through the list concurrently is not safe
         * \param x The list to merge into
         * \param comp Binary predicate that evaluates to true if its
         * first argument is considered strictly inferior to its
         * second
         */
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

        /**
         * \brief Swaps the content of two lists.
         * This sort is stable, it means consecutive equal elements keep their order
         * \par Complexity
         * Approximately N log N.
         * \par Iterator Validity
         * All iterator remain valid
         * \par Data races
         * Both container are accessed, contained elements are accessed but never modified.
         * Iterating through the list concurrently is not safe
         */
        void sort()
        {
            // merge s'attend a avoir une CListe deja triee en parametre,
            // donc on peut l'utiliser pour notre mergesort O(N log N)

            if (m_sentinel->m_next != m_sentinel.get() &&
                m_sentinel->m_next->m_next != m_sentinel.get()) // une CListe vide ou avec 1 element est deja triee
            {
                CList reg;//cette CListe repartie les element dans les partitions
                CList tmp[sizeof(void*) << 3];
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

    /**
     * \brief Swaps the content of two lists.
     * \par Complexity
     * Constant.
     * \par Iterator Validity
     * All iterator remain valid, but instead refers to elements in the other list
     * \par Data races
     * Both container are accessed, none of the contained elements are.
     * \param x A list to swap
     * \param y A list to swap
     */
    template <class T>
    void swap(CList<T>& x, CList<T>& y)
    {
        x.swap(y);
    }
}
