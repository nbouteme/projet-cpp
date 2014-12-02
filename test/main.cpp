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

// Fuck everything.
// On est censé ecrire comment nos tests si on n'a aucune garantie
// qu'il compile avec les autre puisque il choisissent quoi
// implementer


class UnitTests
{
    typedef std::function<bool()> Test;
    std::map<std::string, Test> Tests;
public:
    UnitTests()
    {
        Tests["compilation"] = []()
        {
            // un probleme ici empeche la compilation, pour tout les autres test
            List<int> l;
            List<NonCopyable>();
            List<NonInstantiable>();
            List<std::string>();
            List<int*>();

            //test boucle for c++11
            for(int i : l) printf("%d\n", i);
            
            // pas trop le choix ici vu que en cas d'echec, la compilation echoue
            return true;
        };

        Tests["GetSuivant"] = []()
        {
            List<int> l;
            // l.GetSuivant /nop, pas un membre
            // Le comportement de getsuivant n'ayant pas ete defini... pas grand chose a tester
            return true;
        };
        
        Tests["insert"] = []()
        {
            std::stringstream str;
            std::stringstream str1;
            List<int> l;
            std::list<int> m;
            l.insert(l.end(), 1);
            l.insert(l.end(), 2);
            l.insert(l.begin(), 1);
            l.insert(l.begin(), 2);
            
            m.insert(m.end(), 1);
            m.insert(m.end(), 2);
            m.insert(m.begin(), 1);
            m.insert(m.begin(), 2);
            // le test passe si la fonction insert respecte le standard
            IZI_ASSERT(*l.begin() == *m.begin());
            for(int i : l) str << i;
            for(int i : m) str1 << i;
            IZI_ASSERT(str.str() == str1.str());
            return true;
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


//tester les fuites memeoire avec valgrind si dispo
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
