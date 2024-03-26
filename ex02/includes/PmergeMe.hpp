#include <list>

#ifndef PMERGEME_HPP
#define PMERGEME_HPP
/* ---------------------------- helper typedefs ---------------------------- */
// clang-format off
using std::list;
using std::pair;
typedef list<pair<int, int> > pair_list_t;
typedef list<int> int_list_t;
typedef pair<bool, int> straggler_t;
/* ------------------------------ helper macro ----------------------------- */
#define IS_ODD(x) ((x.size()) % 2 != 0)

class PmergeMe
{

public:
	PmergeMe (int_list_t &input_list);
	~PmergeMe ();
	PmergeMe (const PmergeMe &other);
	PmergeMe   &operator= (const PmergeMe &other);
	static int_list_t FJMI (std::list<int> &list);

private:
	static straggler_t find_straggler(int_list_t &input_list);
	static pair_list_t merge_sort_seconds(pair_list_t &pairs);
	static int_list_t extract_largest(pair_list_t &sorted_pair);
	static void insert_smallest(pair_list_t &sorted_pair, int_list_t &largest);
};

#endif // PMERGEME_HPP
