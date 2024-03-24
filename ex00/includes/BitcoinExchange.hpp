#include "Date.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::istringstream;
using std::runtime_error;

typedef size_t loc;
typedef std::map<Date, double>							  price_m;
typedef std::multimap<size_t, std::pair<Date, double> > input_m;
typedef std::map<size_t, string>						  input_error_m;

#define ISERROR(lineNumber) (inputErrorMap.find(lineNumber) != inputErrorMap.end())

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
	BitcoinExchange (const char *priceFile, const char *inputFile);
	~BitcoinExchange ();
	void process ();

private:
	void		load_price_map ();
	void		load_input_map ();
	inline void insert_error (size_t lineNumber, const string &error_msg);
	inline double validate_value(size_t lineNumber, const string &value_str);
	ifstream   *load_file (const char *fileName, const string &headerLine);

	ifstream *priceStream;
	price_m	  priceMap;

	ifstream	 *inputStream;
	input_m		  inputMap;
	input_error_m inputErrorMap;

	BitcoinExchange (const BitcoinExchange &o);
	BitcoinExchange &operator= (const BitcoinExchange &);

#ifdef DEBUG

public:
	void print_priceMap ();
#endif // DEBUG
};

#endif // BITCOINEXCHANGE_HhP
