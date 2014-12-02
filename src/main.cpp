#include <List.hpp>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	nsSdD::List<int> l;
    
    l.push_back(8);
	l.push_back(7);
	l.push_back(6);
	l.push_back(5);
	l.push_back(4);
	l.push_back(3);
    l.sort();
    
    for(auto i : l)
        printf("%d\n", i);
    return 0;
}
