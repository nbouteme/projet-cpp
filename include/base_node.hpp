#pragma once

namespace nsSdD
{
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

        pointer GetSuivant()
        {
            return next;
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
}
