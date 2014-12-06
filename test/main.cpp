#include <List.hpp>
#include <list>
#include <sstream>
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
    CList<int> l;
    CList<int> n;

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

TEST(sort)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    CList<int> l;
    CList<int> n;
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

TEST(erase)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    CList<int> l;
    CList<int> n;
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

TEST(unique)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    CList<int> l;
    CList<int> n;
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

TEST(merge)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    CList<int> l;
    CList<int> n;
    CList<int> x;
    CList<int> y;

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

TEST(test)
{
    IZI_ASSERT(!"Vous n'etes pas censes voir ca");
}

TEST(pop_back)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    CList<int> l;
    CList<int> n;
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

TEST(pop_front)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    CList<int> l;
    CList<int> n;
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

TEST(push_back)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    CList<int> l;
    CList<int> n;
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

TEST(push_front)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    CList<int> l;
    CList<int> n;
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

TEST(front)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    CList<int> l;
    CList<int> n;
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

TEST(back)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    CList<int> l;
    CList<int> n;
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

TEST(clear)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    CList<int> l;
    srand(0);
    for(int i = 0; i < 100; ++i)
        l.push_front(rand());
    l.clear();

    IZI_ASSERT(l.size() == 0);
    return true;
}

TEST(remove)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    CList<int> l;
    CList<int> n;
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

TEST(remove_if)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    CList<int> l;
    CList<int> n;
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

TEST(reverse)
{
    using namespace nsSdD;
    using namespace std;
    stringstream out, comp;
    CList<int> l;
    CList<int> n;
    srand(0);
    for(int i = 0; i < 100000; ++i)
        l.push_front(rand());
    srand(0);
    for(int i = 0; i < 100000; ++i)
        n.push_front(rand());
    l.reverse();
    n.reverse();
    for(auto i : n) comp << i;
    for(auto f = l.begin(); f != l.end(); ++f) out << *f;
    IZI_ASSERT(out.str() == comp.str());
    return true;
}

TEST(size)
{
    using namespace nsSdD;
    using namespace std;

    CList<int> l;
    CList<int> n;
    srand(0);
    for(int i = 0; i < 100; ++i)
        l.push_front(rand());
    srand(0);
    for(int i = 0; i < 100; ++i)
        n.push_front(rand());
    IZI_ASSERT(l.size() == n.size());
    return true;
}

int main()
{
    // Test d'instanciation
    {
        using namespace nsSdD;
        using namespace std;

        CList<NonCopyable>();
        CList<NonInstanciable>();
        CList<int>();
        CList<NonCopyable>();
        CList<NonInstanciable>();
        CList<int>();
    }

    test_insert    (nsSdD::CList<int>());
    test_push_back (nsSdD::CList<int>());
    test_pop_back  (nsSdD::CList<int>());
    test_pop_front (nsSdD::CList<int>());
    test_push_front(nsSdD::CList<int>());
    test_front     (nsSdD::CList<int>());
    test_back      (nsSdD::CList<int>());
    test_merge     (nsSdD::CList<int>());
    test_sort      (nsSdD::CList<int>());
    test_erase     (nsSdD::CList<int>());
    test_remove    (nsSdD::CList<int>());
    test_unique    (nsSdD::CList<int>());
    test_clear     (nsSdD::CList<int>());
    test_remove    (nsSdD::CList<int>());
    test_remove_if (nsSdD::CList<int>());
    test_reverse   (nsSdD::CList<int>());

    //permet de montrer que la detection fonctionne:
    //test_test (nsSdD::CList<int>());
    return 0;
}
