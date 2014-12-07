#pragma once

/*
 * \file test_classes.hpp
 * \brief Defines classes to test instantiation and assignment with.
 */

/// Class that can't be copied
class NonCopyable
{
public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

/// Class that can't be instancied
class NonInstanciable
{
public:
    NonInstanciable() = delete;
};
