#include <List.hpp>
#include <iostream>
#include <sstream>
#include <functional>
#include <string>
#include <map>
#include <list>
#include <IziAssert.h>

using namespace nsSdD;

class NonCopyable
{
public:
    NonCopyable(){};
};

class NonInstantiable
{
public:
    NonInstantiable() = delete;
};

// TODO: Changer une troisieme fois la maniere de tester.

// TODO: tester les fuites memoire avec valgrind si dispo
int main(int argc, char *argv[])
{
    UnitTests ut;
    if(argc == 1)
        return ut.runAll();
    int k = 0;
    for(int i = 1; i < argc; ++i)
        if(!ut.run(argv[i])) ++k;
    return k;
}
