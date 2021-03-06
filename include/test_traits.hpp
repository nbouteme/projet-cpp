#pragma once
#include <type_traits>
/*
 * \file test_traits.hpp
 * \brief Defines traits that identify a list container
 */

/**
 * \def HAS_MEMBER(member)
 * Generates a trait class that determines if a type has one or more method overload
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
    template <typename C>                  \
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
{ };                                       
