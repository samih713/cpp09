#include "Date.hpp"
#include <sstream>

using std::istringstream;
using std::runtime_error;

/**
 * @brief Constructs a Date object with the specified date.
 * @param date The date in the format "YYYY-MM-DD".
*/
Date::Date (const string &date) : isLeap (false), year (0), month (0), day (0)
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



/* ------------------------------------------------------------------------- */
/*                             operator overload                             */
/* ------------------------------------------------------------------------- */

Date &Date::operator-- ()
{
	if (day == 1)
	{
		if (month == JAN)
		{
			year--;
			month = DEC;
			day	  = 31;
		}
		else
		{
			month--;
			switch (month)
			{
			case FEB: day = isLeap ? 29 : 28; break;
			case APR:
			case JUN:
			case SEP:
			case NOV: day = 30; break;
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

bool Date::operator> (const Date &rhs) const
{
	if (year > rhs.get_year ()) return true;
	else return false;

	if (month > rhs.get_month ()) return true;
	else return false;

	if (day > rhs.get_day ()) return true;
	return false;
}

bool Date::operator>= (const Date &rhs) const
{
	return (*this > rhs || *this == rhs);
}

bool Date::operator> (const string &rhs) const
{
	Date dateObj (rhs);
	return (*this > dateObj);
}

bool Date::operator>= (const string &rhs) const
{
	return (*this > rhs || *this == rhs);
}

bool Date::operator< (const Date &rhs) const
{
	if (year < rhs.get_year ()) return true;
	else return false;

	if (month < rhs.get_month ()) return true;
	else return false;

	if (day < rhs.get_day ()) return true;
	return false;
}

bool Date::operator<= (const Date &rhs) const
{
  return (*this < rhs || *this == rhs);
}

bool Date::operator< (const string &rhs) const
{
	Date dateObj (rhs);
	return (*this < dateObj);
}

bool Date::operator<= (const string &rhs) const
{
  return (*this < rhs || *this == rhs);
}

bool Date::operator== (const Date &rhs) const
{
	if (year != rhs.year) return false;
	if (month != rhs.month) return false;
	if (day != rhs.day) return false;
	return true;
}

bool Date::operator== (const string &rhs) const
{
	Date dateObj (rhs);
	return (*this == dateObj);
}

bool Date::operator!= (const Date &rhs) const
{
	return !(*this == rhs);
}

bool Date::operator!= (const string &rhs) const
{
	return !(*this == rhs);
}

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

/* ------------------------------------------------------------------------- */
/*                              member functions                             */
/* ------------------------------------------------------------------------- */

/**
 * @brief Validates the date.
 * @return True if the date is valid, false otherwise.
*/
bool Date::validate_date ()
{
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

/**
 * @brief Checks if a year is a leap year.
 * @param year The year to check.
 * @return True if the year is a leap year, false otherwise.
*/
inline bool Date::isLeapYear (int year)
{
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

inline double Date::get_year () const
{
	return year;
}

inline double Date::get_month () const
{
	return month;
}

inline double Date::get_day () const
{
	return day;
}
