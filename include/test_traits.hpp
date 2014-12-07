#pragma once
#include <type_traits>
/*
 * \file test_traits.hpp
 * \brief Defines traits that identify a list container
 */

/**
 * \def HAS_MEMBER(member)
 * Generates a trait class that determines if a type has one or more method
 * called \a member
 */

#define HAS_MEMBER(member)                 \
template <class T>                         \
struct has_member_##member                 \
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
