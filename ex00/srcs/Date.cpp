#include "Date.hpp"
#include <sstream>
#include <exception>

using std::runtime_error;
using std::istringstream;

/* ------------------------ Construction/Destruction ----------------------- */
Date::Date(const string &date, char dateDelim) : _dateDelim(dateDelim)
{
	istringstream dateStream (date);

	char del1;
	char del2;

	dateStream >> std::noskipws;
	dateStream >> year >> del1 >> month >> del2 >> day;

	// check for stream errors
	if (dateStream.fail () || dateStream.bad ())
		throw runtime_error("Invalid date format");
	// check for date delimeters
	if (del1 != _dateDelim || del2 != _dateDelim)
		throw runtime_error("Invalid date format");

	isLeap = isLeapYear (year);
}

Date::~Date()
{
}

Date::Date(const Date &other) : year(other.year), month(other.month), day(other.day), _dateDelim(other._dateDelim)
{

}

Date &Date::operator=(const Date &other)
{
	if (this != &other)
	{
		year = other.year;
		month = other.month;
		day = other.day;
		_dateDelim = other._dateDelim;
	}
	return *this;
}

/* ---------------------------- Member functions --------------------------- */
enum {
	JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
};

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

double Date::get_year() const
{
	return year;
}

double Date::get_month() const
{
	return month;
}

double Date::get_day() const
{
	return day;
}

double Date::get_delim() const
{
	return _dateDelim;
}

Date &Date::operator--() {
	if (day == 1) {
		if (month == 1) {
			year--;
			month = 12;
			day = 31;
		} else {
			month--;
			switch (month) {
			case 2:
				day = isLeap ? 29 : 28;
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				day = 30;
				break;
			default:
				day = 31;
			}
		}
	} else {
		day--;
	}
	return *this;
}

bool Date::operator>(const Date &date) const{
	if (year > date.get_year())
		return true;
	if (year < date.get_year())
		return false;
	if (month > date.get_month())
		return true;
	if (month < date.get_month())
		return false;
	if (day > date.get_day())
		return true;
	return false;
}

bool Date::operator<(const Date &date) const{
	if (year < date.get_year())
		return true;
	if (year > date.get_year())
		return false;
	if (month < date.get_month())
		return true;
	if (month > date.get_month())
		return false;
	if (day < date.get_day())
		return true;
	return false;
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
	os << date.get_year() << date.get_delim() << date.get_month() << date.get_delim() << date.get_day();
	return os;
}

std::string &operator<<(std::string &s, const Date &date) {
	std::ostringstream os;
	os << date;
	s = os.str();
	return s;
}
