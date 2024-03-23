#include "BitcoinExchange.hpp"
#include "Date.hpp"

BitcoinExchange::BitcoinExchange (const char *priceDBFile)
{
	// load the price map
	load_price_map (priceDBFile);
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

void	BitcoinExchange::process()
{
	imap::iterator begin = inputMap.begin();
	imap::iterator end = inputMap.end();

	string date;

	for (imap::iterator it = begin; it != end; it++)
	{
		// find the price for the date
		pmap::iterator priceIt = priceMap.find(it->second.first);
		if (it->second.second == INVALID_PRICE)
			cerr << it->second.first << endl; // date here would contain the error message
		else if (priceIt == priceMap.end()) {
			Date dateObj(it->second.first);
			while (priceIt == priceMap.end()) {
				date << --dateObj;
				priceIt = priceMap.find(date);
			}
			cout << it->second.first << " => " << it->second.second << " = " << it->second.second * priceIt->second << endl;
		}
		else
			cout << it->second.first << " => " << it->second.second << " = " << it->second.second * priceIt->second << endl;
	}
}
#if defined(DEBUG)
void BitcoinExchange::print_priceMap ()
{
  pmap::iterator begin = priceMap.begin();
  pmap::iterator end = priceMap.end();
  for (pmap::iterator it = begin; it != end; it++)
    cout << "Date [" << it->first << "] price [" << it->second << "]\n";
}
#endif // DEBUG

