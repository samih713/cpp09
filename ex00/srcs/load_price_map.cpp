#include "BitcoinExchange.hpp"
#include "Date.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>

using std::istringstream;
using std::runtime_error;



void BitcoinExchange::load_price_map ()
{

	string line;
	string date;
	double price;
	size_t comma;

	std::pair<price_m::iterator, bool> ret;

	while (std::getline (*priceDB, line)) // get the line
	{
		comma = line.find_first_of (" , ", 0);
		if (comma == string::npos)
			throw runtime_error ("Invalid date/price format");
		else
		{
			Date dateObj (line.substr (0, comma));
			date << dateObj;
		}
		// validate the price
		istringstream priceStream (line.substr (comma + 1));
		priceStream >> price;
		if (!priceStream.eof () || priceStream.fail () || price < 0)
			throw runtime_error ("Date [" + date + "] Invalid price format");
		// if all's good add it to the map
		ret = priceMap.insert (std::make_pair (date, price));
		if (ret.second == false)
			throw runtime_error ("Date [" + date + "] already exists");
	}
}
