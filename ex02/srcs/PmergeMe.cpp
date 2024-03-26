#include "PmergeMe.hpp"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>

PmergeMe::PmergeMe(int_list_t &input_list)
{
	(void)input_list;
}

PmergeMe::~PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    (void)other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    (void)other;
    return *this;
}
