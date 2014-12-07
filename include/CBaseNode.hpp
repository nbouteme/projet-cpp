#pragma once

namespace nsSdD
{
    /// Doubly-linked node in a circular list.
    class CBaseNode
    {
        /// Defines the internal type of the class
        typedef CBaseNode* pointer;

    public:
        /// Pointer to the previous node
        pointer m_prev = nullptr;
        /// Pointer to the next node
        pointer m_next = nullptr;

        /**
         * \brief Places this node before \a elem
         * \param elem The node to put "this" before.
         */
        void hook(pointer elem)
        {
            m_next = elem;
            m_prev = elem->m_prev;
            elem->m_prev->m_next = this;
            elem->m_prev = this;
        }

        /**
         * \brief Returns a pointer to the next node.
         * This is unused and there only to maintain comptability with
         * eventual tests.
         * \return A pointer to the next node
         */
        pointer GetSuivant()
        {
            return m_next;
        }

        /**
         * \brief Removes a node from its list.
         * Its ressources aren't freed.
         */
        void unhook()
        {
            m_prev->m_next = m_next;
            m_next->m_prev = m_prev;
            m_prev = nullptr;
            m_next = nullptr;
        }

        /**
         * \brief Moves a range [first;last[ of nodes and put it before "this"
         * If last is the node that called this method, the list remains untouched.
         * \param first Pointer to the first element in the range
         * \param last Pointer to the last element in the range
         */
        void transfer(CBaseNode* first, CBaseNode* last)
        {
            if(last != this)
            {
                last->m_prev->m_next = this;
                first->m_prev->m_next = last;
                m_prev->m_next = first;
                pointer tmp_this = m_prev;
                m_prev = last->m_prev;
                last->m_prev = first->m_prev;
                first->m_prev = tmp_this;
            }
        }

        /// Reverse the order of the elements in a list.
        void reverse()
        {
            CBaseNode* tmp = this;
            do
            {
                std::swap(tmp->m_prev, tmp->m_next);
                tmp = tmp->m_prev;
            } while(this != tmp);
        }

        /**
         * \brief Swaps two nodes, that could be in differents lists.
         * \param x A node to swap
         * \param y Another node to swap
         */
        static void swap(CBaseNode& x, CBaseNode& y)
        {
            if (x.m_next != &x)
            {// x non vide
                if(y.m_next != &y)
                    {// et y non vide
                        std::swap(x.m_next, y.m_next);
                        std::swap(x.m_prev, y.m_prev);//echange les lien internes a x et y
                        x.m_next->m_prev = x.m_prev->m_next = &x;//les precedent et suivant etait ceux de y, donc on reassigne
                        y.m_next->m_prev = y.m_prev->m_next = &y;
                    }
                else
                {// et y vide
                    y.m_next = x.m_next;
                    y.m_prev = x.m_prev;//reconstitue les pointeurs internes a x
                    y.m_next->m_prev = y.m_prev->m_next = &y; //reconsitue les pointeur sur x
                    x.m_next = x.m_prev = &x;//x devient vide
                }
            }
            else if (y.m_next != &y)
            {// x vide et y non vide
                x.m_next = y.m_next;
                x.m_prev = y.m_prev;//reconstitue les pointeur internes a y
                x.m_next->m_prev = x.m_prev->m_next = &x;//reconstitue les pointeurs sur y
                y.m_next = y.m_prev = &y;//y devient vide
            }
        }
    };
}
