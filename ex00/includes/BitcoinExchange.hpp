#include <fstream>
#include <iostream>
#include <map>
#include <string>

#define DEBUG

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

using std::cerr;
using std::cout;
using std::endl;
using std::map;
using std::string;

typedef map<string, double> dpm;

class BitcoinExchange
{

public:
	BitcoinExchange ();
	~BitcoinExchange ();
	BitcoinExchange (const BitcoinExchange &);
	BitcoinExchange &operator= (const BitcoinExchange &);
#if defined(DEBUG)
  void print_map();
#endif // DEBUG

private:
	void				load_price_map ();
	static const string priceDB_file;
	dpm					priceMap;
};

#endif // BITCOINEXCHANGE_HhP
