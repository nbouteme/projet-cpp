#pragma once

// definie le test d'une fonction specifique

#include <map>
#include <test_traits.hpp>
#include <IziAssert.h>

#define TEST(name)                                        \
template <typename T>                                     \
typename std::enable_if<has_##name<T>::value, bool>::type \
test_##name(const T&)

