#pragma once

// Ce fichier permet de determiner les membre existant d'une classe
// C'est utilisé dans les test comme substitution a la compilation
// conditionelle car plus modulable avec du code externe Une des
// lacune de ce systeme est de ne pas faire de difference entre donnee
// membre et fonction ne peut detecter une surcharge specifique d'une
// fonction specifique, et ne peux analyser que les membres public
// (mais ca c'est pas grave car seul l'interface nous interesse lors
// des tests)

// Aussi, je ne peux pas implementer de trait pour GetSuivant car on
// ne sais pas si il CNode est interne a CList ou pas, le qualifier
// change.  peutetre tester pour T::CNode::GetSuivant et T::GetSuivant
// dans le meme trait ? A tester.

// determine si T possede un membre insert
template<typename T>
struct has_insert
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::insert));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre clear
template<typename T>
struct has_clear
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::clear));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre remove
template<typename T>
struct has_remove
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::remove));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre unique
template<typename T>
struct has_unique
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::unique));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre erase
template<typename T>
struct has_erase
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::erase));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre push_back
template<typename T>
struct has_push_back
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::push_back));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre push_front
template<typename T>
struct has_push_front
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::push_front));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre pop_front
template<typename T>
struct has_pop_front
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::pop_front));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre pop_back
template<typename T>
struct has_pop_back
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::pop_back));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre empty
template<typename T>
struct has_empty
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::empty));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre empty
template<typename T>
struct has_empty
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::empty));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre begin
template<typename T>
struct has_begin
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::begin));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre end
template<typename T>
struct has_end
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::end));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre assign
template<typename T>
struct has_assign
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::assign));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre swap
template<typename T>
struct has_swap
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::swap));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre splice
template<typename T>
struct has_splice
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::splice));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre reverse
template<typename T>
struct has_reverse
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::reverse));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre remove
template<typename T>
struct has_remove
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::remove));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre remove_if
template<typename T>
struct has_remove_if
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::remove_if));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre resize
template<typename T>
struct has_resize
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::resize));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre merge
template<typename T>
struct has_merge
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::merge));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};

// determine si T possede un membre sort
template<typename T>
struct has_sort
{
    typedef char yes;
    typedef char[2] no;

    template<typename C>
    static yes test(decltype(&C::sort));
    template<typename C>
    static no test(...);

    enum { value = sizeof(test<T>(0)) == sizeof(yes)};
};
