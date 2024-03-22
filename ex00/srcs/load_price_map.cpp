#include "BitcoinExchange.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>

const string BitcoinExchange::priceDB_file = "./data.csv";

using std::ifstream;
using std::istringstream;
using std::runtime_error;

static bool validate_date (const string &input);

void BitcoinExchange::load_price_map ()
{
	static const string headerLine ("date,exchange_rate");
	static ifstream		priceDB (priceDB_file.c_str (), std::ios_base::in);

	if (!priceDB.good ())
		throw runtime_error ("Failed to open price database");

	string line;
	string date;
	double price;
	size_t comma;

	std::pair<dpm::iterator, bool> ret;

	while (std::getline (priceDB, line)) // get the line
	{
		if (line == headerLine) continue;

		comma = line.find_first_of (',', 0);
		if (comma == string::npos)
			throw runtime_error ("Invalid date/price format");
		else // validate day
		{
			date = line.substr (0, comma);
			if (!validate_date (date)) throw runtime_error ("Invalid date");
		}

		// validate the price
		istringstream priceStream (line.substr (comma + 1));
		priceStream >> price;
		if (!priceStream.eof () || priceStream.fail () || price < 0)
			throw runtime_error ("[" + date + "] Invalid price format");

		// if all's good add it to the map
		ret = priceMap.insert (std::make_pair (date, price));
		if (ret.second == false) throw runtime_error ("Date already exists");
	}
}

inline static bool isLeapYear (int year)
{
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

static bool validate_date (const string &date)
{
	istringstream dateStream (date);

	int	 year;
	int	 month;
	int	 day;
	char del1;
	char del2;

	bool isLeap = false;

	dateStream >> std::noskipws;
	dateStream >> year >> del1 >> month >> del2 >> day;

	if (dateStream.fail () || dateStream.bad ()) return false;
	if (del1 != '-' || del2 != '-') return false;

	isLeap = isLeapYear (year);
	// validate month
	if (month < 1 || month > 12) return false;
	// validate days
	switch (month)
	{
	case 2:
	{ // feb
		if (isLeap && day > 29) return false;
		if (!isLeap && day > 28) return false;
		break;
	}
	case 4:
	case 6:
	case 9:
	case 11: //  april, june, september, november
		if (day > 30) return false;
		break;
	default: // rest
		if (day > 31) return false;
	}
	return true;
}
