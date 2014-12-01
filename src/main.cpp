#include <List.hpp>

using namespace std;

int main(int argc, char *argv[])
{
	nsSdD::List<int> l;
	l.push_back(3);
	l.push_back(4);
	l.push_front(2);
	l.push_front(1);
	l.pop_front();
	l.pop_back();





	printf("%lu\n", l.size());
	l.clear();
	printf("%lu\n", l.size());
	if (l.empty())
		printf("%lu\n", l.size());
	if (!l.empty())
		printf("%lu\n", l.size());
    return 0;
}
