

#pragma once // Remplace les conditions pour éviter l'auto inclusion

class CList
{
    template<typename T>
    typedef T value_type;
    typedef T allocator_type;
    typedef T reference;
    typedef T const_reference;
    typedef T pointer_safety;
    typedef T const_pointer;

    public:
        CList();
       ~CList();
    protected:
    private:
};


