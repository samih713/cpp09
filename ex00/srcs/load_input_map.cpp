#include "BitcoinExchange.hpp"
#include "Date.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>

using std::ifstream;
using std::istringstream;
using std::make_pair;
using std::runtime_error;

/**
 * @brief Loads input data from a file into the BitcoinExchange object.
 *
 * This function reads each line from the input file and parses it to extract the date and value.
 * It validates the input data and inserts it into the inputMap member variable.
 * If any errors occur during the parsing or validation process, error messages are inserted into
 * the errorMap member variable.
 *
 * @param None.
 * @return None.
 */
void BitcoinExchange::load_input_map ()
{
	string		 line;
	string		 date;
	double		 value;
	loc			 delimiterPos;
	const string delimiter	= " | ";
	size_t		 lineNumber = 1;
	Date		 dateObj;

	while (std::getline (*inputStream, line)) // get the line
	{
		if (line.empty ()) continue; // skip empty lines
		delimiterPos = line.find (delimiter);
		if (delimiterPos == string::npos) insert_error (lineNumber, "Error: bad input => " + line);
		else // validate day
		{
			try
			{
				dateObj = Date (line.substr (0, delimiterPos));
				if (priceMap.begin ()->first > dateObj)
					insert_error (lineNumber, "Error: invalid date => " + line);
			}
			catch (const runtime_error &e)
			{
				insert_error (lineNumber, "Error: bad input => " + line.substr (0, delimiterPos));
			}
		}

		value = validate_value (lineNumber, line.substr (delimiterPos + delimiter.length ()));

		inputMap.insert (make_pair (lineNumber, make_pair (dateObj, value)));

		lineNumber++;
	}
}

/**
 * Inserts an error message into the inputErrorMap at the specified line number.
 *
 * @param lineNumber The line number where the error occurred.
 * @param error_msg The error message to be inserted.
 */
inline void BitcoinExchange::insert_error (size_t lineNumber, const string &error_msg)
{
	std::ostringstream errorStream (error_msg);
	errorStream << "[" << lineNumber << "] " << error_msg;
	inputErrorMap.insert (make_pair (lineNumber, errorStream.str ()));
}

/**
 * Validates and converts a string value to a double,
 * if string is invalid or out of range, an error message
 * is inserted into the inputErrorMap.
 *
 * @param lineNumber The line number of the input file.
 * @param value_str The string value to be validated and converted.
 * @return The converted double value if it is valid, otherwise -1.
 */
inline double BitcoinExchange::validate_value (size_t lineNumber, const string &value_str)
{
	double		  value;
	istringstream valueStream (value_str);
	valueStream >> value;
	if (ISERROR (lineNumber)) return -1;
	if (!valueStream.eof () || valueStream.fail ())
		insert_error (lineNumber, "Error: bad input => " + value_str);
	else if (value > 1000) insert_error (lineNumber, "Error: too large a number.");
	else if (value < 0) insert_error (lineNumber, "Error: not a positive number.");
	return value;
}
