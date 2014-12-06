#pragma once

// definie le test d'une fonction specifique
#include <test_traits.hpp>
#include <IziAssert.h>

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
