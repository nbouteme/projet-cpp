#pragma once

class NonCopyable
{
public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

class NonInstanciable
{
public:
    NonInstanciable(){}
};
