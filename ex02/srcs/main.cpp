#include "PmergeMe.hpp"
#include <algorithm>
#include <iostream>
#include <list>

using std::cerr;
using std::cout;
using std::endl;
using std::list;

void   printlist_d(int_list_t l);
double Random();

int main()
{
    int_list_t a(3000);
    int_list_t b;

    std::generate(a.begin(), a.end(), Random);
    b = PmergeMe::FJMI(a);
	if (std::is_sorted(b.begin(), b.end()))
	{
		cout << "sorted" << endl;
	}
	else
	{
		cerr << "not sorted" << endl;
	}
    return 0;
}

void printlist_d(int_list_t l)
{
    for (int_list_t::iterator it = l.begin(); it != l.end(); it++)
        cout << *it << " ";
    cout << endl;
}

double Random()
{
    return std::rand() % 100;
}
