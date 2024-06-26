#include "BitcoinExchange.hpp"
#include <iostream>

static const char *priceDBFile = "data.csv";

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Usage provide an input file!" << endl;
        return -1;
    }
    try
    {
        const char     *inputFile = argv[1];
        BitcoinExchange binance(priceDBFile, inputFile);
        binance.process();
    }
    catch (std::runtime_error &e)
    {
        cerr << e.what() << endl;
    }

#ifdef DEBUG
    // binance.print_priceMap();
#endif // DEBUG
    return 0;
}
