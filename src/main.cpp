#include <CList.hpp>
#include <iostream>

using namespace std;

/**
 *\mainpage CList
 * Rewrite of the STL's list template.  The goal of this rewrite is to
 * implement automatic memory managment with smart pointers while
 * being as close as the C++'s standard draft as possible.  By "as the
 * C++'s standard draft as possible", we mean for example that
 * algorithms complexities are respected, as well as data-race and
 * iterator validity
 */

struct A
{
    int a;
};

int main()
{
	nsSdD::CList<A> l;
    A a {1};
    l.push_front(a);
    l.begin()->a = 0;
    return 0;
}
