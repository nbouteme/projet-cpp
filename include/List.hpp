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
        
        };
    };
}
