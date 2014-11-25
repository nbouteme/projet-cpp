#include <List.hpp>
#include <iostream>
#include <functional>
#include <string>
#include <map>

using namespace nsSdD;


class UnitTests
{
    typedef std::function<bool()> Test;
    std::map<std::string, Test> Tests;
public:
    UnitTests()
    {
        Tests["instantiation"] = []()
        {
            List<int>();
            List<std::string>();
            List<int*>();
            return true;
        };

        Tests["touchette"] = []()
        {
            return false;
        };
    }

    int runAll()
    {
        int i = 0;
        for(auto test : Tests)
        {
            printf("[Running test %s]...", test.first.c_str());
            if(test.second())
                printf("\b\b\b\tOk.\n");
            else
                printf("\b\b\b\t\033[07;38mFAILED!\n"), ++i;
        }
        return i;
    }

    bool run(std::string test)
    {
        return Tests[test]();
    }
};

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
