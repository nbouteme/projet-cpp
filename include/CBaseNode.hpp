#pragma once

namespace nsSdD
{
    struct CBaseNode
    {
        typedef CBaseNode* pointer;

        pointer m_prev = nullptr;
        pointer m_next = nullptr;

        void hook(pointer elem)
        {
            m_next = elem;
            m_prev = elem->m_prev;
            elem->m_prev->m_next = this;
            elem->m_prev = this;
        }

        pointer GetSuivant()
        {
            return m_next;
        }

        
        void unhook()
        {
            m_prev->m_next = m_next;
            m_next->m_prev = m_prev;
            m_prev = nullptr;
            m_next = nullptr;
        }

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

        void reverse()
        {
            CBaseNode* tmp = this;
            do
            {
                std::swap(tmp->m_prev, tmp->m_next);
                tmp = tmp->m_prev;
            } while(this != tmp);
        }

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
