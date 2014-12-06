#include <CList.hpp>
#include <iostream>

using namespace std;

int main()
{
	nsSdD::CList<int> l;
	nsSdD::CList<int> n;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);
    n.push_back(4);
    n.push_back(5);
    n.push_back(6);
    l = n;
    for(auto i : l)
        printf("%d\n", i);
    return 0;
}
