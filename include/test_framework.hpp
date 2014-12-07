#pragma once
#include <test_traits.hpp>
#include <IziAssert.h>

/*
 * \file test_framework.hpp
 * \brief Define the unit testing engine
 */

/*
 * \def TEST(name)
 * Generate a generic test signature called if the T type has the \a
 * member declared, the test is callable with test_\a name.
 * If the T type doesn't have a \a name member, a dummy test is called instead
 */

#define TEST(name)                                                 \
template <typename T>                                              \
typename std::enable_if<has_##name<T>::value == false, bool>::type \
test_##name(void)                                                  \
{                                                                  \
    IZI_ASSERT(!"Methode " #name " non implémentée");              \
    return false;                                                  \
}                                                                  \
template <typename T>                                              \
typename std::enable_if<has_##name<T>::value, bool>::type          \
test_##name(void)


// TODO: Trouver une facon d'enregistrer les tests des leur declaration
