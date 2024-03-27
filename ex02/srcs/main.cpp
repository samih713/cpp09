#include "PmergeMe.hpp"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <list>
#include <deque>

using std::cerr;
using std::cout;
using std::endl;
using std::list;
using std::pair;
using std::deque;

template<typename T>
void print(T &l);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "Usage: ./PmergeMe [sequence]" << endl;
		return -1;
    }
    try
    {
		std::cout.setf (std::ios_base::adjustfield, std::ios_base::left);
		// start list timer
		double start_list = clock();
        list<int> _list = PmergeMe<list<int>, list<pair<int, int> > >::fill_up_list(argv + 1, argc - 1);
		list<int> temp = _list;
        list<int> sorted_list = PmergeMe<std::list<int>, std::list<std::pair<int, int> > >::FJMI(_list);
		// end list timer
		double duration_list = clock() - start_list;


		// start list timer
		double start_deque = clock();
        deque<int> _deque = PmergeMe<deque<int>, deque<pair<int, int> > >::fill_up_list(argv + 1, argc - 1);
        deque<int> sorted_deque = PmergeMe<deque<int>, deque<pair<int, int> > >::FJMI(_deque);
		// end list timer
		double duration_deque = clock() - start_deque;

		cout << std::setw(15) << "Un-Sorted: ";
		print(temp);
		cout << std::setw(15) << "Sorted: ";
		print(sorted_list);
		cout << "Time to process a range of " << temp.size() << " elements with std::list : " << duration_list << " ms" << endl;
		cout << "Time to process a range of " << temp.size() << " elements with std::deque : " << duration_deque << " ms" << endl;
    }
	catch (std::runtime_error &e)
	{
		cout << e.what() << endl;
	}
	return 0;
}

template<typename T>
void print(T &l)
{
    for (typename T::iterator it = l.begin(); it != l.end(); it++)
        cout << *it << " ";
    cout << endl;
}

#if 0
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



double Random()
{
    return std::rand() % 100;
}
#endif // main tester
