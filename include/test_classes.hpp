#pragma once
/** @file test_classes.hpp */

/**My Preprocessor Macro.*/ 
#define TEST_DEFINE(x) (x*x)

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
