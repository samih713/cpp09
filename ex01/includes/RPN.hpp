#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

#ifndef RPN_HPP
#define RPN_HPP

using std::istringstream;
using std::runtime_error;
using std::string;

typedef std::stack<double> number_stack;

#define TO_INT(c) ((c) - '0')

enum OPERATIONS
{
	MULT = '*',
	DIV	 = '/',
	ADD	 = '+',
	SUB	 = '-'
};

/**
 * @class RPN
 * @brief Represents a Reverse Polish Notation calculator.
 *
 * The RPN class provides functionality to evaluate mathematical expressions
 * in Reverse Polish Notation (RPN) format. It supports basic arithmetic
 * operations such as addition, subtraction, multiplication, and division.
 */
class RPN
{

public:
	RPN (const string &exp);
	~RPN ();
	RPN (const RPN &other);
	double evaluate ();

private:
	void		 do_operation (char opr);
	static bool	 is_operand (char entry);
	static bool	 is_number (char entry);
	double		 get_result ();
	void		 pop_two ();
	number_stack numStk;
	string		 exp;
	double		 _fnum;
	double		 _snum;

	RPN &operator= (const RPN &); // deleted
};

#endif // RPN_HPP
