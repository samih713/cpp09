#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>
#include <cassert>

using std::cout;
using std::endl;

/* ------------------------------------------------------------------------- */
/*                                  testing                                  */
/* ------------------------------------------------------------------------- */
void print_pair_list(pair_list_t &pairs)
{
	for (pair_list_t::iterator it = pairs.begin(); it != pairs.end(); it++)
	{
		cout << "[" << it->first << ", " << it->second << "]" << endl;
	}
}

void print_int_list(int_list_t &list)
{
	for (int_list_t::iterator it = list.begin(); it != list.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
}
/* ------------------------------------------------------------------------- */
/*                                  testing                                  */
/* ------------------------------------------------------------------------- */

/*
* @brief finds the last element [straggler] in an odd list
* @return stragger_t where bool is true if straggler is found
*/
int_list_t PmergeMe::FJMI(int_list_t &input_list)
{
    straggler_t straggler = find_straggler(input_list);

    pair_list_t pairs;
    pair_list_t sorted;
	int_list_t largest(0);

    while (!input_list.empty())
    {
        // remove 1 element from the front of the list
        double a = input_list.front();
        input_list.pop_front();
        // remove 2nd element
        double b = input_list.front();
        input_list.pop_front();
        // a should be less than b, if not swap
        if (a > b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }

    // recursively merge
    sorted = merge_sort_seconds(pairs);

	// extract the largest elements
	largest = extract_largest(sorted);


	insert_smallest(sorted, largest);

    // if straggler was added, push it to the pairs
    if (straggler.first)
    {
		int_list_t::iterator ins = std::lower_bound(largest.begin(), largest.end(), straggler.second);
		largest.insert(ins, straggler.second);
    }

	return largest;
}

void PmergeMe::insert_smallest(pair_list_t &sorted_pair, int_list_t &largest)
{
	for (pair_list_t::iterator it = sorted_pair.begin(); it != sorted_pair.end(); it++)
	{
		int_list_t::iterator ins = std::lower_bound(largest.begin(), largest.end(), it->first);
		largest.insert(ins, it->first);
	}
}

int_list_t PmergeMe::extract_largest(pair_list_t &sorted_pair)
{
	int_list_t largest(0);
	for (pair_list_t::iterator it = sorted_pair.begin(); it != sorted_pair.end(); it++)
	{
		// push the second element of the pair
		largest.push_back(it->second);
	}
	return largest;
}



/*
 * @brief finds the last element [straggler] in an odd list
 * @param input_list an un-sorted list of integers
 * @return stragger_t where bool is true if straggler is found
 */
straggler_t PmergeMe::find_straggler(int_list_t &input_list)
{
    straggler_t straggler = std::make_pair(false, 0);

    if (IS_ODD(input_list))
    {
        straggler.second = input_list.back();
        straggler.first = true;
        input_list.pop_back();
        assert(!IS_ODD(input_list) && "list size should be even");
    }

    return straggler;
}

bool comp(const pair<int, int> &a, const pair<int, int> &b)
{
	return a.second < b.second;
}


/*
 * @brief merge sort based on the second
 * element of the pairs
 * @param pairs a list of pairs
*/
pair_list_t PmergeMe::merge_sort_seconds(pair_list_t &pairs)
{
    pair_list_t sorted(0);


    if (pairs.size() == 1)
    {
        return pairs;
    }

    pair_list_t::iterator half = pairs.begin();
    size_t                mid = pairs.size() / 2;
    std::advance(half, mid);

    pair_list_t left(pairs.begin(), half);
    pair_list_t right(half, pairs.end());

    left = merge_sort_seconds(left);

    right = merge_sort_seconds(right);

    std::merge(left.begin(), left.end(), right.begin(), right.end(),
               std::back_inserter(sorted), comp);

	return sorted;
}
