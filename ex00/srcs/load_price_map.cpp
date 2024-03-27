#include "BitcoinExchange.hpp"
#include "Date.hpp"
#include <sstream>
#include <stdexcept>

typedef std::pair<price_m::iterator, bool> price_m_ret;

/**
 * @brief Loads the price map with date and corresponding price from a stream.
 *
 * This function reads lines from the provided stream and extracts the date and price
 * information. It validates the format of the date and price, and inserts them into the
 * price map. If the date already exists in the map, an exception is thrown.
 *
 * @throws std::runtime_error if the date/price format is invalid or if the date already
 * exists in the map.
 */
void BitcoinExchange::load_price_map()
{
    string      line;
    Date        dateObj;
    double      price;
    loc         separator;
    price_m_ret insert_ret;

    while (std::getline(*priceStream, line))
    {
        if (line.empty())
            continue; // skip empty lines
        separator = line.find(",");
		cout << "separator: " << separator << endl;
        if (separator == string::npos || line.length() < 3)
            throw runtime_error("Invalid date/price format");
        else
            dateObj = Date(line.substr(0, separator));

        // validate the price
        istringstream priceStream(line.substr(separator + 1));
        priceStream >> price;
        if (!priceStream.eof() || priceStream.fail() || price < 0)
            throw runtime_error("Date [" + dateObj.to_string() +
                                "] Invalid price format");

        // if all's good add it to the map
        insert_ret = priceMap.insert(std::make_pair(dateObj, price));
        if (insert_ret.second == false)
            throw runtime_error("Date [" + dateObj.to_string() + "] already exists");
    }
}
