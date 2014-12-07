#include <CList.hpp>
#include <list>
#include <sstream>

#define TTTEST nsSdD::CList<int>
#include <test_traits.hpp>
#include <test_framework.hpp>
#include <test_classes.hpp>

// Toute les parties entre blocs d'accolades ou ligne finissant par
// /**/ sont susceptible d'emplecher la compilation si une certaine
// surcharge ou certains traits n'ont pas ete implementée si un
// probleme de compilation survient sur une partie non marqué comme
// sucepptible de ne pas compiler on considere que la classe a echouer
// le test

TEST(insert)
{
    // l'implementation de insert implique d'avoir fait des iterateurs
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    list<int> n;

    l.insert(l.begin(), 1);
    l.insert(l.begin(), 2);
    l.insert(l.begin(), 3);
    l.insert(l.end(), 1);
    l.insert(l.end(), 2);
    l.insert(l.end(), 3);

    n.insert(n.begin(), 1);
    n.insert(n.begin(), 2);
    n.insert(n.begin(), 3);
    n.insert(n.end(), 1);
    n.insert(n.end(), 2);
    n.insert(n.end(), 3);

    for(auto i : n) comp << i;

    // on en profite pour tester si la boucle for c++11 marche,
    // decommenter le code si dessous
    // for(auto i : l) out << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    IZI_ASSERT(out.str() == comp.str());
    return true;
}
END_TEST(insert)


TEST(sort)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    list<int> n;
    srand(0);
    for(int i = 0; i < 1000; ++i)
        l.push_back(rand());
    srand(0);
    for(int i = 0; i < 1000; ++i)
        n.push_back(rand());
    l.sort();
    n.sort();
    for(auto i : n) comp << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    IZI_ASSERT(out.str() == comp.str());
    return true;
}
END_TEST(sort)

TEST(erase)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    list<int> n;
    srand(0);
    for(int i = 0; i < 100; ++i)
        l.push_back(rand());
    srand(0);
    for(int i = 0; i < 100; ++i)
        n.push_back(rand());

    n.erase(n.begin());
    l.erase(l.begin());
    n.erase(n.begin());
    l.erase(l.begin());
    n.erase(n.begin());
    l.erase(l.begin());

    for(auto i : n) comp << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    IZI_ASSERT(out.str() == comp.str());
    return true;
}
END_TEST(erase)

TEST(unique)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    list<int> n;
    srand(0);
    for(int i = 0; i < 100000; ++i)
        l.push_back(rand());
    srand(0);
    for(int i = 0; i < 100000; ++i)
        n.push_back(rand());
    l.unique();
    n.unique();
    for(auto i : n) comp << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    IZI_ASSERT(out.str() == comp.str());
    return true;
}
END_TEST(unique)

TEST(merge)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    list<int> n;
    CList<int> x;
    list<int> y;

    srand(0);
    for(int i = 0; i < 10; ++i)
        l.push_back(rand());
    srand(0);
    for(int i = 0; i < 10; ++i)
        n.push_back(rand());
    srand(0);
    for(int i = 0; i < 10; ++i)
        x.push_back(rand());
    srand(0);
    for(int i = 0; i < 10; ++i)
        y.push_back(rand());

    l.sort();
    n.sort();
    l.merge(x);
    n.merge(y);

    IZI_ASSERT(x.empty());

    for(auto i : n) comp << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    IZI_ASSERT(out.str() == comp.str());
    return true;
}
END_TEST(merge)

/*
TEST(test)
{
    IZI_ASSERT(!"Vous n'etes pas censes voir ca");
}
END_TEST(test)
*/

TEST(pop_back)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    list<int> n;
    srand(0);
    for(int i = 0; i < 100; ++i)
        l.push_back(rand());
    srand(0);
    for(int i = 0; i < 100; ++i)
        n.push_back(rand());

    l.pop_back();
    l.pop_back();
    l.pop_back();
    n.pop_back();
    n.pop_back();
    n.pop_back();

    for(auto i : n) comp << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    IZI_ASSERT(out.str() == comp.str());
    return true;
}
END_TEST(pop_back)

TEST(pop_front)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    list<int> n;
    srand(0);
    for(int i = 0; i < 100; ++i)
        l.push_front(rand());
    srand(0);
    for(int i = 0; i < 100; ++i)
        n.push_front(rand());

    l.pop_front();
    l.pop_front();
    l.pop_front();
    n.pop_front();
    n.pop_front();
    n.pop_front();

    for(auto i : n) comp << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    IZI_ASSERT(out.str() == comp.str());
    return true;
}
END_TEST(pop_front)

TEST(push_back)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    list<int> n;
    srand(0);
    for(int i = 0; i < 100; ++i)
        l.push_back(rand());
    srand(0);
    for(int i = 0; i < 100; ++i)
        n.push_back(rand());

    l.push_back(1);
    l.push_back(12);
    l.push_back(0);
    n.push_back(1);
    n.push_back(12);
    n.push_back(0);

    for(auto i : n) comp << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    IZI_ASSERT(out.str() == comp.str());
    return true;
}
END_TEST(push_back)

TEST(push_front)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    list<int> n;
    srand(0);
    for(int i = 0; i < 100; ++i)
        l.push_front(rand());
    srand(0);
    for(int i = 0; i < 100; ++i)
        n.push_front(rand());

    l.push_front(1);
    l.push_front(12);
    l.push_front(0);
    n.push_front(1);
    n.push_front(12);
    n.push_front(0);

    for(auto i : n) comp << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    // Si ce test echoue...
    IZI_ASSERT(out.str() == comp.str());
    return true;
}
END_TEST(push_front)

TEST(front)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    list<int> n;
    srand(0);
    for(int i = 0; i < 100; ++i)
        l.push_front(rand());
    srand(0);
    for(int i = 0; i < 100; ++i)
        n.push_front(rand());
    IZI_ASSERT(l.front() == n.front());

    for(auto i : n) comp << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    IZI_ASSERT(out.str() == comp.str());
    return true;
}
END_TEST(front)

TEST(back)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    list<int> n;
    srand(0);
    for(int i = 0; i < 100; ++i)
        l.push_back(rand());
    srand(0);
    for(int i = 0; i < 100; ++i)
        n.push_back(rand());
    IZI_ASSERT(l.back() == n.back());

    for(auto i : n) comp << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    IZI_ASSERT(out.str() == comp.str());
    return true;
}
END_TEST(back)

TEST(clear)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    srand(0);
    for(int i = 0; i < 100; ++i)
        l.push_front(rand());
    l.clear();

    IZI_ASSERT(l.size() == 0);
    return true;
}
END_TEST(clear)

TEST(remove)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    list<int> n;
    srand(0);
    for(int i = 0; i < 100000; ++i)
        l.push_front(rand());
    srand(0);
    for(int i = 0; i < 100000; ++i)
        n.push_front(rand());
    l.remove(42);
    n.remove(42);
    for(auto i : n) comp << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    IZI_ASSERT(out.str() == comp.str());
    return true;
}
END_TEST(remove)

TEST(remove_if)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    list<int> n;
    srand(0);
    for(int i = 0; i < 100000; ++i)
        l.push_front(rand());
    srand(0);
    for(int i = 0; i < 100000; ++i)
        n.push_front(rand());
    l.remove_if([](const int&i){return i > 42;});
    n.remove_if([](const int&i){return i > 42;});
    for(auto i : n) comp << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    IZI_ASSERT(out.str() == comp.str());
    return true;
}
END_TEST(remove_if)

TEST(reverse)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    list<int> n;
    srand(0);
    for(int i = 0; i < 100; ++i)
        l.push_front(rand());
    srand(0);
    for(int i = 0; i < 100; ++i)
        n.push_front(rand());
    l.reverse();
    n.reverse();
    for(auto i : n) comp << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    IZI_ASSERT(out.str() == comp.str());
    return true;
}
END_TEST(reverse)

TEST(size)
{
    using namespace nsSdD;
    using namespace std;

    T l;
    list<int> n;
    srand(0);
    for(int i = 0; i < 100; ++i)
        l.push_front(rand());
    srand(0);
    for(int i = 0; i < 100; ++i)
        n.push_front(rand());
    IZI_ASSERT(l.size() == n.size());
    return true;
}
END_TEST(size)

TEST(assign)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    T l;
    T n;
    srand(0);
    for(int i = 0; i < 1000; ++i)
        l.push_back(0);
    srand(0);
    for(int i = 0; i < 1000; ++i)
        n.push_back(rand());
    l.assign(n.begin(), n.end());
    for(auto i : n) comp << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    IZI_ASSERT(out.str() == comp.str());
    return true;
}
END_TEST(assign)


int main()
{
    // TODO: Changer le type pour tester avec diverse classes, std::list par exemple
    using int_list = nsSdD::CList<int>;

    // Test d'instanciation
    {
        nsSdD::CList<NonCopyable>();
        nsSdD::CList<NonInstanciable>();
        int_list();
    }

    run_all_tests();
    return 0;
}
