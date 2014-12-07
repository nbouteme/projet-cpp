#pragma once

/*
 * \file test_framework.hpp
 * \brief Define the unit testing engine
 */

#include <test_traits.hpp>
#include <map>
#include <string>
#include <IziAssert.h>

#ifndef TTTEST
#error "You must define TTTEST with the Type you want To TEST !"
#endif

struct _base_test
{
    virtual bool test() = 0;
};

std::map<std::string, _base_test*> __tests;

void _register_test(const char *name, _base_test *self)
{
    __tests[name] = self;
}

void run_test(std::string name)
{
    __tests[name]->test();
}

void run_all_tests()
{
    for(auto t : __tests)
        t.second->test();
}

/*
 * \def TEST(name)
 * Generate a generic test signature called if the T type has the \a
 * member declared, the test is callable with test_\a name.
 * If the T type doesn't have a \a name member, a dummy test is called instead
 */
#define TEST(name)                                                 \
template <typename T>                                              \
 struct s_obj_##name : public _base_test                           \
{                                                                  \
 s_obj_##name() { _register_test(#name, this); }                   \
    virtual bool test() { return test_##name<T>(); }               \
                                                                   \
template <typename C>                                              \
typename std::enable_if<has_##name<C>::value == false, bool>::type \
test_##name(void)                                                  \
{                                                                  \
    IZI_ASSERT(!"Methode " #name " non implémentée");              \
    return false;                                                  \
}                                                                  \
template <typename C>                                              \
typename std::enable_if<has_##name<C>::value, bool>::type          \
test_##name(void) {
#define CONCAT2(x, y) x ## y 
#define CONCAT(x, y) CONCAT2(x, y)
#define END_TEST(name) }}; s_obj_ ## name < TTTEST > CONCAT(_tmp, __LINE__);

// FIXME: On ne peut pas tester plusieurs traits, donc ca pose probleme si un test depends d'un autre, par exemple le test de size a besoin de push_front pour remplir la liste
// On est censé ignorer les tests interdependant ? Ou dire qu'ils ont echoué ? Est-ce que le fait de ne pas pourvoir passer un test equivaut a un echec ?
// TODO: Trouver une facon d'enregistrer les tests des leur declaration
