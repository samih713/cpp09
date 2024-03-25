#include "BitcoinExchange.hpp"
#include "Date.hpp"
#include <stdexcept>

using std::runtime_error;

/* ------------------------------------------------------------------------- */
/*                          construction/destruction                         */
/* ------------------------------------------------------------------------- */

/**
 * @brief Constructs a BitcoinExchange object.
 *
 * This constructor initializes a BitcoinExchange object by loading data from the specified price
 * file and input file. It loads the price data into the priceStream member variable and the input
 * data into the inputStream member variable. Additionally, it calls the load_price_map() and
 * load_input_map() functions to populate the price map and input map respectively.
 *
 * @param priceFile The path to the price file.
 * @param inputFile The path to the input file.
 * @throws runtime_error If the price file or input file fails to open.
 */
BitcoinExchange::BitcoinExchange (const char *priceFile, const char *inputFile)
	: priceStream (load_file (priceFile, "date,exchange_rate")),
	  inputStream (load_file (inputFile, "date | value"))
{
	load_price_map ();
	load_input_map ();
}

/**
 * @brief Destructor for the BitcoinExchange class.
 *
 * This destructor is responsible for cleaning up the dynamically allocated
 * memory used by the BitcoinExchange object. It deletes the priceStream and
 * inputStream objects.
 */
BitcoinExchange::~BitcoinExchange ()
{
	delete priceStream;
	delete inputStream;
}

/* ------------------------------------------------------------------------- */
/*                              member functions                             */
/* ------------------------------------------------------------------------- */

#define PRINT_ERR(msg) (cerr << (msg) << endl)
#define PRINT_OUT(it, priceIt)                                            \
	(cout << (it)->second.first << " => " << (it)->second.second << " = " \
		  << (it)->second.second * (priceIt)->second << endl)
/**
 * @brief Process the input data and calculate the total value of each transaction.
 * The function iterates over the inputMap and for each transaction, it checks if there is a
 * corresponding price in the priceMap. If a price is found, it calculates the total value of the
 * transaction by multiplying the quantity with the price. If a price is not found, it searches for
 * the nearest previous date in the priceMap and calculates the total value using that price. If an
 * error occurs, it prints the corresponding error message.
 */
void BitcoinExchange::process ()
{
	input_m::iterator begin = inputMap.begin ();
	input_m::iterator end	= inputMap.end ();
	price_m::iterator priceIt;

	for (input_m::iterator it = begin; it != end; it++)
	{
		if (ISERROR (it->first))
		{
			PRINT_ERR (inputErrorMap[it->first]);
			continue;
		}

		priceIt = priceMap.find (it->second.first);
		if (priceIt == priceMap.end ())
		{
			Date dateObj (it->second.first);
			if ((--priceMap.end ())->first < dateObj)
			{
				priceIt = --priceMap.end ();
			}
			while (priceIt == priceMap.end ())
			{
				priceIt = priceMap.find (--dateObj);
			}
		}
		PRINT_OUT (it, priceIt);
	}
}

/**
 * @brief Loads a file and checks the header line.
 *
 * This function opens a file specified by the fileName parameter and checks if
 * the header line matches the provided headerLine parameter. If the file fails to
 * open or the header line is invalid, a runtime_error exception is thrown.
 *
 * @param fileName The name of the file to be loaded.
 * @param headerLine The expected header line of the file.
 * @return A pointer to an ifstream object representing the opened file.
 * @throws runtime_error If the file fails to open or the header line is invalid.
 */
ifstream *BitcoinExchange::load_file (const char *fileName, const string &headerLine)
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
