#pragma once // Remplace les conditions pour éviter l'auto inclusion
#include <cstddef> // ptrdiff_t
template<typename T> class node_iterator;
class node_iterator
{
    public:
        ptrdiff_t difference_type;
        //iterator_category?
        template<typename T>
        T value_type;
        T* pointer;// I Dunno
        T& reference;// I Dunno
        template<typename T>
        T Data; //The Data of the node


        node_iterator();
        ~node_iterator();
    protected:
    private:
};


