#include <initializer_list>
#include <CList.hpp>
#include <list>
#include <utility>
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

int main()
{
    nsSdD::CList<int> a(nsSdD::CList<int>(10, 10));
    return 0;
}
