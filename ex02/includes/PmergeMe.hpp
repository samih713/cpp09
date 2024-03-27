#include <algorithm>
#include <iterator>
#include <list>
#include <sstream>
#include <utility>

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

/* ---------------------------- helper typedefs ---------------------------- */
// clang-format off
typedef std::pair<bool, int> straggler_t;
/* ------------------------------ helper macro ----------------------------- */
#define IS_ODD(x) ((x.size()) % 2 != 0)

/* ------------------------------------------------------------------------- */
/*                              class definition                             */
/* ------------------------------------------------------------------------- */
template<typename I, typename P>
class PmergeMe
{

public:

	static I FJMI (I &numbers);
	static I fill_up_list(char **argv, int size);
private:
	static straggler_t find_straggler(I &numbers);
	static P merge_sort_seconds(P &pairs);
	static I extract_largest(P &sorted_pairs);
	static void insert_smallest(P &sorted_pairs, I &sorted);

	PmergeMe ();
	~PmergeMe ();
	PmergeMe (const PmergeMe &other);
	PmergeMe   &operator= (const PmergeMe &other);
};

/* ------------------------------------------------------------------------- */
/*                               implementation                              */
/* ------------------------------------------------------------------------- */
template<typename I, typename P>
I PmergeMe<I, P>::fill_up_list(char **argv, int size)
{
	I numbers;
	int entry(-1);
	for (int i = 0; i < size; i++)
	{
		if (std::string(argv[i]) == "-0")
		{
			throw std::runtime_error("Error: invalid input");
		}

		std::istringstream iss((std::string(argv[i])));
		iss >> entry;
		if (iss.fail() || !iss.eof() || entry < 0)
		{
			throw std::runtime_error("Error: invalid input");
		}
		else
		{
			numbers.push_back(entry);
		}
	}
	return numbers;
}

template<typename I, typename P>
I PmergeMe<I, P>::FJMI(I &numbers)
{
    straggler_t straggler = find_straggler(numbers);

    P pairs;
    P sorted_pairs;

    I sorted(0);

    // fill up pairs
    while (!numbers.empty())
    {
        int a = numbers.front();
        numbers.pop_front();
        int b = numbers.front();
        numbers.pop_front();
        if (a > b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }
    // recursively merge sort the pairs
    sorted_pairs = merge_sort_seconds(pairs);
    // extract the largest elements
    sorted = extract_largest(sorted_pairs);
    // insert the smallest elements
    insert_smallest(sorted_pairs, sorted);
    // if straggler was added, push it to the pairs
    if (straggler.first)
    {
        typename I::iterator insert_position =
            std::lower_bound(sorted.begin(), sorted.end(), straggler.second);
        sorted.insert(insert_position, straggler.second);
    }
    return sorted;
}

template<typename I, typename P>
void PmergeMe<I, P>::insert_smallest(P &sorted_pairs, I &sorted)
{
    for (typename P::iterator it = sorted_pairs.begin(); it != sorted_pairs.end(); it++)
    {
        typename I::iterator ins =
            std::lower_bound(sorted.begin(), sorted.end(), it->first);
        sorted.insert(ins, it->first);
    }
}

template<typename I, typename P>
I PmergeMe<I, P>::extract_largest(P &sorted_pairs)
{
    I sorted(0);
    for (typename P::iterator it = sorted_pairs.begin(); it != sorted_pairs.end(); it++)
    {
        sorted.push_back(it->second);
    }
    return sorted;
}

template<typename I,typename P>
straggler_t PmergeMe<I, P>::find_straggler(I &numbers)
{
    straggler_t straggler = std::make_pair(false, 0);

    if (IS_ODD(numbers))
    {
        straggler.second = numbers.back();
        straggler.first = true;
        numbers.pop_back();
    }
    return straggler;
}

bool comp(const std::pair<int, int> &a, const std::pair<int, int> &b)
{
    return a.second < b.second;
}

template<typename I, typename P>
P PmergeMe<I, P>::merge_sort_seconds(P &pairs)
{
    P sorted(0);

    if (pairs.size() == 1)
    {
        return pairs;
    }

    typename P::iterator half = pairs.begin();
    size_t      mid = pairs.size() / 2;
    std::advance(half, mid);

    P left(pairs.begin(), half);
    P right(half, pairs.end());

    left = merge_sort_seconds(left);

    right = merge_sort_seconds(right);

    std::merge(left.begin(), left.end(), right.begin(), right.end(),
               std::back_inserter(sorted), comp);

    return sorted;
}

#endif // PMERGEME_HPP
