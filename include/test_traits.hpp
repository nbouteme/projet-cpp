#pragma once
#include <type_traits>

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

#define HAS_MEMBER(member)                 \
template <class T>                         \
class has_member_##member                  \
{                                          \
    using yes = char[2];                   \
    using  no = int;                       \
                                           \
    struct Fallback { int member; };       \
    struct Derived : T, Fallback { };      \
                                           \
    template <class C>                     \
    static no& test(decltype(C::member)*); \
    template < typename C>                 \
    static yes& test(C*);                  \
                                           \
public:                                    \
    static constexpr bool val =            \
    sizeof(test<Derived>(nullptr)) ==      \
    sizeof(yes);                           \
};                                         \
                                           \
template <class T>                         \
struct has_##member                        \
: public std::integral_constant            \
<bool,has_member_##member<T>::val>         \
{ };                                       \

HAS_MEMBER(insert)
HAS_MEMBER(erase)
HAS_MEMBER(push_back)
HAS_MEMBER(pop_back)
HAS_MEMBER(push_front)
HAS_MEMBER(back)
HAS_MEMBER(front)
HAS_MEMBER(pop_front)
HAS_MEMBER(assign)
HAS_MEMBER(clear)
HAS_MEMBER(remove)
HAS_MEMBER(remove_if)
HAS_MEMBER(unique)
HAS_MEMBER(empty)
HAS_MEMBER(size)
HAS_MEMBER(max_size)
HAS_MEMBER(splice)
HAS_MEMBER(merge)
HAS_MEMBER(reverse)
HAS_MEMBER(sort)
HAS_MEMBER(swap)
HAS_MEMBER(resize)
HAS_MEMBER(test)
