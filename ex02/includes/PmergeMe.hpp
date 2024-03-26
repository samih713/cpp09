#include <list>

#ifndef PMERGEME_HPP
#define PMERGEME_HPP
// split the numbers into pairs
// swap pairs if they are in the wrong order
// add larger numbers from the pairs to list call it b's
// sort larger numbers using merge sort
// swap the full pairs
// [10, 1, 3, 7, 4, 8]
// [1,10] [3,7] [4,8]
// [3,7] [4,8] [1,10]
// [7, 8, 10]
// 3 + [7, 8, 10]
// [3, 7, 8, 10]

class PmergeMe
{

public:
	PmergeMe ();
	~PmergeMe ();
	PmergeMe (const PmergeMe &other);
	PmergeMe   &operator= (const PmergeMe &other);
	static void FJMI (std::list<int> &list);
};

#endif // PMERGEME_HPP
