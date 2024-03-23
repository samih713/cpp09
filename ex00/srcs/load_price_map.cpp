#include "Date.hpp"
#include "BitcoinExchange.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>

using std::ifstream;
using std::istringstream;
using std::runtime_error;

void BitcoinExchange::load_price_map (const char *priceDBFile)
{
	const string headerLine ("date,exchange_rate");
	static ifstream		priceDB (priceDBFile, std::ios_base::in);

	if (!priceDB.good ())
		throw runtime_error ("Failed to open price database");

	string line;
	string date;
	double price;
	size_t comma;

	std::pair<pmap::iterator, bool> ret;

	while (std::getline (priceDB, line)) // get the line
	{
		if (line == headerLine) continue;

		comma = line.find_first_of (" , ", 0);
		if (comma == string::npos)
			throw runtime_error ("Invalid date/price format");
		else // validate day
		{
			Date dateObj(line.substr (0, comma));
			if (!dateObj.validate_date ())
				throw runtime_error ("Invalid date");
			date << dateObj;
		}
		// validate the price
		istringstream priceStream (line.substr (comma + 1));
		priceStream >> price;
		if (!priceStream.eof () || priceStream.fail () || price < 0)
			throw runtime_error ("Date [" + date + "] Invalid price format");
		// if all's good add it to the map
		ret = priceMap.insert (std::make_pair (date, price));
		if (ret.second == false) throw runtime_error ("Date [" + date + "] already exists");
	}
}

