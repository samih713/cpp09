#include <string>
#include <ostream>
#include <sstream>

#ifndef DATE_HPP
#define DATE_HPP

using std::string;

class Date
{
public:
/* ------------------------ Construction/Destruction ----------------------- */
	Date(const string &date, char dateDelim = '-');
	~Date();
	Date(const Date &);
	Date &operator=(const Date &);
/* ---------------------------- Member functions --------------------------- */
	bool validate_date ();
	Date &operator--();
	bool operator>(const Date &date) const;
	bool operator<(const Date &date) const;
/* -------------------------------- getters -------------------------------- */
	double get_year() const;
	double get_month() const;
	double get_day() const;
	double get_delim() const;
private:
	inline bool isLeapYear (int year);
	bool isLeap;
	int	 year;
	int	 month;
	int	 day;
	char _dateDelim;
};

std::ostream &operator<<(std::ostream &os, const Date &date);
std::string &operator<<(std::string &s, const Date &date);

#endif // DATE_HPP

