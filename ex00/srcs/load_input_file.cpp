#include "BitcoinExchange.hpp"
#include "Date.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>

using std::ifstream;
using std::runtime_error;
using std::istringstream;
using std::make_pair;

static void validate_header_line(const string &line)
{
	static const string headerLine ("date | value");
	if (line != headerLine)
		throw runtime_error ("Invalid header line");
}

static void set_error_value (string &date, double &value, const string &error_msg)
{
	date = error_msg;
	value = INVALID_PRICE;
}

void BitcoinExchange::load_input_file (const char *inputFile)
{
	string line;
	string date;
	double value;
	size_t delimiterPos;
	const string delimiter = " | ";
	size_t lineNumber = 0;

	// open the file
	static ifstream		inputDB(inputFile, std::ios_base::in);
	if (!inputDB.good ())
		throw runtime_error ("Failed to open value database");

	// header line
	std::getline (inputDB, line);
	validate_header_line (line);

	while (std::getline (inputDB, line)) // get the line
	{
		value = 0;
		delimiterPos = line.find(delimiter);
		if (delimiterPos == string::npos)
			set_error_value(date, value, "Error: bad input => " + line);
		else // validate day
		{
			date = line.substr(0, delimiterPos);
			if (date < priceMap.begin()->first)
				set_error_value(date, value, "Error: invalid date => " + line);
			else {
				try {
					Date dateObj(date);
					if (!dateObj.validate_date ())
						set_error_value(date, value, "Error: bad input => " + date);
				}
				catch (...) {
					set_error_value(date, value, "Error: bad input => " + date);
				}
			}

		}

		// validate the value
		if (value != INVALID_PRICE) {
			istringstream valueStream (line.substr(delimiterPos + delimiter.length()));
			valueStream >> value;
			if (!valueStream.eof () || valueStream.fail ())
				set_error_value(date, value, "Error: bad input => " + date);
			else if (value > 1000)
				set_error_value(date, value, "Error: too large a number.");
			else if (value < 0)
				set_error_value(date, value, "Error: not a positive number.");
		}
		// if all's good add it to the map
		inputMap.insert (make_pair(lineNumber, make_pair (date, value)));
		lineNumber++;
	}
}
