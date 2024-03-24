#include "BitcoinExchange.hpp"
#include "Date.hpp"
#include <stdexcept>

using std::runtime_error;

BitcoinExchange::BitcoinExchange (const char *priceDBFile,
								  const char *inputFile)
	: priceDB (load_file (priceDBFile, "date,exchange_rate")),
	  inputDB (load_file (inputFile, "date | value"))
{
	load_price_map ();
	load_input_file ();
}

BitcoinExchange::~BitcoinExchange ()
{
	delete priceDB;
	delete inputDB;
}

void BitcoinExchange::process ()
{
	input_m::iterator begin = inputMap.begin ();
	input_m::iterator end	= inputMap.end ();

	string date;

	for (input_m::iterator it = begin; it != end; it++)
	{
		// find the price for the date
		price_m::iterator priceIt = priceMap.find (it->second.first);
		if (it->second.second == INVALID_PRICE)
			cerr << it->second.first
				 << endl; // date here would contain the error message
		else if (priceIt == priceMap.end ())
		{
			Date dateObj (it->second.first);
			while (priceIt == priceMap.end ())
			{
				date << --dateObj;
				priceIt = priceMap.find (date);
			}
			cout << it->second.first << " => " << it->second.second << " = "
				 << it->second.second * priceIt->second << endl;
		}
		else
			cout << it->second.first << " => " << it->second.second << " = "
				 << it->second.second * priceIt->second << endl;
	}
}

ifstream *BitcoinExchange::load_file (const char   *fileName,
									  const string &headerLine)
{
	string _headerLine;

	ifstream *dataBase = new ifstream;
	dataBase->open (fileName, std::ios_base::in);

	if (!dataBase->good ())
	{
		throw runtime_error ("Failed to open " + string (fileName) + " .");
	}

	std::getline (*dataBase, _headerLine);

	if (_headerLine != headerLine)
	{
		throw runtime_error (string (fileName) + " : Invalid header line");
	}

	return dataBase;
}

#if defined(DEBUG)
void BitcoinExchange::print_priceMap ()
{
	price_m::iterator begin = priceMap.begin ();
	price_m::iterator end	= priceMap.end ();
	for (price_m::iterator it = begin; it != end; it++)
		cout << "Date [" << it->first << "] price [" << it->second << "]\n";
}
#endif // DEBUG
