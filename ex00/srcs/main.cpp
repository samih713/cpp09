#include "BitcoinExchange.hpp"
#include <iostream>

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		cerr << "Usage provide an input file!" << endl;
    return -1;
	}
	string inputFile = argv[1];
  BitcoinExchange binance; 
  binance.print_map();
}
