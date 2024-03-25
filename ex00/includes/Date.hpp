#include <ostream>
#include <string>

#ifndef DATE_HPP
#define DATE_HPP

using std::ostream;
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
	Date (const Date &other);
	Date &operator= (const Date &other);

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
	string		  to_string () const;

private:
	bool		validate_date () const;
	static inline bool isLeapYear (int year);

	bool isLeap;
	int	 year;
	int	 month;
	int	 day;
};

/* ---------------------------- stream overload ---------------------------- */
ostream &operator<< (ostream &output_s, const Date &date);
string	&operator<< (string &string_s, const Date &date);

#endif // DATE_HPP
