#include "BitcoinExchange.hpp"
#include <iostream>

static const char *priceDBFile = "/Users/sabdelra/Desktop/current_projects/cpp/cpp09/ex00/data.csv";

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		cerr << "Usage provide an input file!" << endl;
		return -1;
	}
	const char *inputFile = argv[1];
	BitcoinExchange binance(priceDBFile); // i am sure that object is in a valid state
	binance.load_input_file(inputFile);
	binance.process();

#ifdef DEBUG
  binance.print_priceMap();
#endif // DEBUG
  return 0;
}



