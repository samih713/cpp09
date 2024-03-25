#include "PmergeMe.hpp"
#include <algorithm>
#include <list>
#include <cassert>

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
}

void sort_second(std::list<std::pair<double, double>> &pairs)
{
	
}

static FJMI(std::list &list)
{
	// determine if size is even or odd
	double straggler(0);
	// if odd, save the last element
	if (list.size() % 2 != 0)
	{
		straggler = list.back();
		list.pop_back();
		assert(list.size() % 2 == 0 && "list size should be even");
	}
	// split the numbers into pairs
	std::list<std::pair<double, double>> pairs;
	while (!list.empty())
	{
		// remove 1 element from the front of the list
		double a = list.front();
		list.pop_front();
		// remove 2nd element
		double b = list.front();
		list.pop_front();
		// a should be less than b, if not swap
		if (a > b)
			std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}
	// sort list recursively by its 2nd element
	sort_second(pairs);
}
