#pragma once

namespace nsSdD
{
    template <typename T>
    class List
    {
        struct node
        {
    	    typedef node* pointer;
    
        	pointer prev = nullptr;
        	pointer next = nullptr;
        	T data;
        
        	void hook (pointer elem)
        	{
        		pointer tmp = elem->prev;
        		next = elem;
        		prev = elem->prev;
        		elem->prev = this;
        		if(tmp)
        		tmp->next = this;
        	}
        };
    };
}
