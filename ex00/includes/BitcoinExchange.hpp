#include <fstream>
#include <iostream>
#include <map>
#include <string>

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

using std::cerr;
using std::cout;
using std::endl;
using std::string;

typedef std::map<string, double> pmap;
typedef std::multimap<size_t, std::pair<string, double> > imap;

#define INVALID_PRICE -1

class BitcoinExchange
{

public:
	BitcoinExchange (const char *priceDBFile); // constructor
	~BitcoinExchange (); // destructor
	BitcoinExchange (const BitcoinExchange &); // copy constructor
	BitcoinExchange &operator= (const BitcoinExchange &); // copy assignment
	void				load_input_file (const char *inputFile);
	void 				process();
#ifdef DEBUG
	void print_priceMap ();
#endif // DEBUG

private:
	void				load_price_map (const char *priceDBFile);
	pmap				priceMap;
	imap				inputMap;
};

#endif // BITCOINEXCHANGE_HhP
