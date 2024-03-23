#include <ostream>
#include <sstream>
#include <string>

#ifndef DATE_HPP
#define DATE_HPP

using std::string;

enum
{
	JAN = 1,
	FEB,
	MAR,
	APR,
	MAY,
	JUN,
	JUL,
	AUG,
	SEP,
	OCT,
	NOV,
	DEC
};

static const char dateDelim = '-';

class Date
{
public:
	Date (const string &date);
	~Date ();
	Date (const Date &);
	Date &operator= (const Date &);

	Date &operator-- ();
	bool  operator> (const Date &date) const;
	bool  operator> (const string &date) const;
	bool  operator< (const Date &date) const;
	bool  operator< (const string &date) const;
	bool  operator== (const Date &date) const;
	bool  operator== (const string &date) const;

	double get_year () const;
	double get_month () const;
	double get_day () const;

private:
	bool		validate_date ();
	inline bool isLeapYear (int year);
	bool		isLeap;
	int			year;
	int			month;
	int			day;
};

std::ostream &operator<< (std::ostream &os, const Date &date);
std::string	 &operator<< (std::string &s, const Date &date);

#endif // DATE_HPP
