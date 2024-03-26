// #include "PmergeMe.hpp"
#include <algorithm>
#include <iostream>
#include <list>

using std::list;

using std::cout;
using std::endl;

typedef list<double> _list;

_list merge_sort_seconds (_list &pairs)
{
	// recursion end
	if (pairs.size () == 1)
	{
		return pairs;
	}
	// find half the list
	int				mid	 = pairs.size () / 2;
	_list::iterator half = pairs.begin ();
	std::advance (half, mid);

	_list left (pairs.begin (), half);
	_list right (half, pairs.end ());

	merge_sort_seconds (left);
	merge_sort_seconds (right);

	pairs.clear ();
	std::merge (
		left.begin (), left.end (), right.begin (), right.end (), std::back_inserter (pairs));
	return pairs;
}

void   print_list (_list l);
double Random ()
{
	return std::rand () % 100;
}

int main ()
{
	_list a (50);
	std::generate (a.begin (), a.end (), Random);

	print_list (a);

	merge_sort_seconds (a);

	print_list (a);
}

void print_list (_list l)
{
	for (_list::iterator it = l.begin (); it != l.end (); it++)
		cout << *it << " ";
	cout << endl;
}
