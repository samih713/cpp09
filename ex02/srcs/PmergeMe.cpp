#include "PmergeMe.hpp"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>

using std::list;
using std::pair;

typedef list<pair<double, double> > _list;

PmergeMe::PmergeMe ()
{
}

PmergeMe::~PmergeMe ()
{
}

PmergeMe::PmergeMe (const PmergeMe &other)
{
	(void)other;
}

PmergeMe &PmergeMe::operator= (const PmergeMe &other)
{
	(void)other;
	return *this;
}



void merge_sort_seconds (_list &pairs)
{
  list<double> sorted(0);
	// recursion end
	if (pairs.size () == 1)
	{
		return ;
	}
  // find half the list
  int mid = pairs.size() / 2;
	_list::iterator half = pairs.begin ();
  std::advance(half, mid);

	_list			left (pairs.begin (), half);
	_list			right (half, pairs.end());

	merge_sort_seconds (left);
	merge_sort_seconds (right);

  pairs.clear();
  std::merge(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(pairs));
}

void PmergeMe::FJMI (list<int> &l)
{
	// determine if size is even or odd
	pair<bool, double> straggler = std::make_pair (false, 0);
	if (l.size () % 2 != 0)
	{
		// if odd, save the last element
		straggler.second = l.back ();
		straggler.first	 = true;
		l.pop_back ();
		assert (l.size () % 2 == 0 && "list size should be even");
	}

	// split the numbers into pairs
	list<pair<double, double> > pairs;
	while (!l.empty ())
	{
		// remove 1 element from the front of the list
		double a = l.front ();
		l.pop_front ();
		// remove 2nd element
		double b = l.front ();
		l.pop_front ();
		// a should be less than b, if not swap
		if (a > b) std::swap (a, b);
		pairs.push_back (std::make_pair (a, b));
	}

	// recursively merge
  merge_sort_seconds(pairs);
	// if straggler was added, push it to the pairs
	if (straggler.first)
	{
		l.push_back (straggler.second);
	}
}
