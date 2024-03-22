#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange ()
{
	load_price_map ();
}

BitcoinExchange::~BitcoinExchange ()
{
}

BitcoinExchange::BitcoinExchange (const BitcoinExchange &other)
{
	(void)other;
}

BitcoinExchange &BitcoinExchange::operator= (const BitcoinExchange &other)
{
	(void)other;

	return *this;
}

#define DEBUG
#if defined(DEBUG)
void BitcoinExchange::print_map ()
{
  dpm::iterator begin = priceMap.begin();
  dpm::iterator end = priceMap.end();
  for (dpm::iterator it = begin; it != end; it++)
    cout << "date [" << it->first << "] price [" << it->second << "]\n";
}
#endif // DEBUG
