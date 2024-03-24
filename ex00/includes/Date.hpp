#include <ostream>
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

/**
 * @class Date
 * @brief Represents a date.
 *
 * The Date class provides functionality to work with dates, including
 * comparison operators and access to individual components of a date.
 */
class Date
{
public:
	Date ();
	Date (const string &date);
	~Date ();
	Date (const Date &);
	Date &operator= (const Date &);

	/* --------------------------- operator overload -------------------------- */
	Date		 &operator-- ();
	bool		  operator> (const Date &rhs) const;
	bool		  operator>= (const Date &rhs) const;
	bool		  operator> (const string &rhs) const;
	bool		  operator>= (const string &rhs) const;
	bool		  operator< (const Date &rhs) const;
	bool		  operator<= (const Date &rhs) const;
	bool		  operator< (const string &rhs) const;
	bool		  operator<= (const string &rhs) const;
	bool		  operator== (const Date &rhs) const;
	bool		  operator== (const string &rhs) const;
	bool		  operator!= (const Date &rhs) const;
	bool		  operator!= (const string &rhs) const;
	/* -------------------------------- getters ------------------------------- */
	inline double get_year () const;
	inline double get_month () const;
	inline double get_day () const;
	string to_string ();

private:
	bool		validate_date ();
	inline bool isLeapYear (int year);

	bool isLeap;
	int	 year;
	int	 month;
	int	 day;
};

/* ---------------------------- stream overload ---------------------------- */
std::ostream &operator<< (std::ostream &os, const Date &date);
std::string	 &operator<< (std::string &s, const Date &date);

#endif // DATE_HPP
