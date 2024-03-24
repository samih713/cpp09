#include <fstream>
#include <iostream>
#include <map>
#include <string>

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

typedef std::map<string, double>						  price_m;
typedef std::multimap<size_t, std::pair<string, double> > input_m;

#define INVALID_PRICE -1

/**
 * @class BitcoinExchange
 * @brief Represents a Bitcoin exchange.
 *
 * The BitcoinExchange class is responsible for loading price data and input data,
 * and processing the data to perform various operations related to Bitcoin exchange.
 */
class BitcoinExchange
{

public:
	BitcoinExchange (const char *priceDBFile,
					 const char *inputFile); // constructor
	~BitcoinExchange ();					 // destructor
	void process ();

private:
	void	  load_price_map ();
	void	  load_input_file ();
	ifstream *load_file (const char *fileName, const string &headerLine);

	ifstream *priceDB;
	price_m	  priceMap;

	ifstream *inputDB;
	input_m	  inputMap;

	BitcoinExchange (const BitcoinExchange &o);
	BitcoinExchange &operator= (const BitcoinExchange &);

#ifdef DEBUG

public:
	void print_priceMap ();
#endif // DEBUG
};

#endif // BITCOINEXCHANGE_HhP
