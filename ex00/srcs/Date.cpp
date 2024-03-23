#include "Date.hpp"
#include <exception>
#include <sstream>

using std::istringstream;
using std::runtime_error;

/* ------------------------ Construction/Destruction ----------------------- */

/* @brief Date constructor
 *
 * @param date as a string
 *
 * @throw runtime_error if invalid date format
 */
Date::Date (const string &date) : isLeap(false), year(0), month(0), day(0)
{
	istringstream dateStream (date);

	char del1;
	char del2;

	dateStream >> std::noskipws;
	dateStream >> year >> del1 >> month >> del2 >> day;

	if (dateStream.fail () || dateStream.bad ())
		throw runtime_error ("(stream) Invalid date format");

	if (del1 != dateDelim || del2 != dateDelim)
		throw runtime_error ("(delim) Invalid date format");

	isLeap = isLeapYear (year);

	if (!this->validate_date ())
		throw runtime_error ("(validation) Invalid date format");
}

Date::~Date ()
{
}

Date::Date (const Date &other)
	: year (other.year), month (other.month), day (other.day)
{
}

Date &Date::operator= (const Date &other)
{
	if (this != &other)
	{
		year  = other.year;
		month = other.month;
		day	  = other.day;
	}
	return *this;
}

/* ---------------------------- Member functions --------------------------- */

/* @brief Validate the date
 *
 * @return true if the date is valid, false otherwise
 */
bool Date::validate_date ()
{
	// validate month
	if (month < JAN || month > DEC) return false;

	// validate days
	switch (month)
	{
	case FEB:
	{
		if (isLeap && day > 29) return false;
		if (!isLeap && day > 28) return false;
		break;
	}
	case APR:
	case JUN:
	case SEP:
	case NOV:
		if (day > 30) return false;
		break;
	default: // rest
		if (day > 31) return false;
	}
	return true;
}

/* @brief Check if the year is a leap year
 *
 * @param year the year to check
 *
 * @return true if the year is a leap year, false otherwise
 */
inline bool Date::isLeapYear (int year)
{
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

double Date::get_year () const
{
	return year;
}

double Date::get_month () const
{
	return month;
}

double Date::get_day () const
{
	return day;
}

Date &Date::operator-- ()
{
	if (day == 1)
	{
		if (month == 1)
		{
			year--;
			month = 12;
			day	  = 31;
		}
		else
		{
			month--;
			switch (month)
			{
			case 2: day = isLeap ? 29 : 28; break;
			case 4:
			case 6:
			case 9:
			case 11: day = 30; break;
			default: day = 31;
			}
		}
	}
	else
	{
		day--;
	}
	return *this;
}

// comparisons
bool Date::operator> (const Date &date) const
{
	if (year > date.get_year ()) return true;
	else return false;

	if (month > date.get_month ()) return true;
	else return false;

	if (day > date.get_day ()) return true;
	return false;
}

bool Date::operator> (const string &date) const
{
	Date dateObj (date);
	return (*this > dateObj);
}

bool Date::operator< (const Date &date) const
{
	if (year < date.get_year ()) return true;
	else return false;

	if (month < date.get_month ()) return true;
	else return false;

	if (day < date.get_day ()) return true;
	return false;
}

bool Date::operator< (const string &date) const
{
	Date dateObj (date);
	return (*this < dateObj);
}

bool Date::operator== (const Date &date) const
{
	if (year != date.year) return false;
	if (month != date.month) return false;
	if (day != date.day) return false;
	return true;
}

bool Date::operator== (const string &date) const
{
	Date dateObj (date);
	return (*this == dateObj);
}

// stream operations
std::ostream &operator<< (std::ostream &os, const Date &date)
{
	os << date.get_year () << dateDelim << date.get_month () << dateDelim
	   << date.get_day ();
	return os;
}

std::string &operator<< (std::string &s, const Date &date)
{
	std::ostringstream os;
	os << date;
	s = os.str ();
	return s;
}
