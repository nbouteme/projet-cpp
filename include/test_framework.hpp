#pragma once

/*
 * \file test_framework.hpp
 * \brief Define the unit testing engine
 */

#include <test_traits.hpp>
#include <IziAssert.h>


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


// FIXME: On ne peut pas tester plusieurs traits, donc ca pose probleme si un test depends d'un autre, par exemple le test de size a besoin de push_front pour remplir la liste
// On est censé ignorer les tests interdependant ? Ou dire qu'ils ont echoué ? Est-ce que le fait de ne pas pourvoir passer un test equivaut a un echec ?
// TODO: Trouver une facon d'enregistrer les tests des leur declaration
