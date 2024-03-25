#include "RPN.hpp"
#include <iostream>
#include <stdexcept>

using std::cerr;
using std::cout;
using std::endl;

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		cerr << "Usage: ./RPN \"expression\"\n";
	}
	try
	{
		RPN calculator (argv[1]);
		cout << calculator.evaluate () << endl;
	}
	catch (std::runtime_error &e)
	{
		cerr << e.what () << endl;
	}
}
