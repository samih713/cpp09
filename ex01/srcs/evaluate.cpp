#include "RPN.hpp"

/**
 * Evaluates the Reverse Polish Notation (RPN) expression stored in the `exp`
 * member variable.
 *
 * @return The result of the evaluation.
 * @throws std::runtime_error if the input is invalid or the expression is
 * incomplete.
 */
double RPN::evaluate ()
{
	double		  result (0);
	istringstream iss (exp);
	char		  entry (0);

	while (iss >> entry)
	{
		if (is_number (entry))
		{
			numStk.push (TO_INT (entry));
		}
		else if (is_operand (entry))
		{
			do_operation (entry);
		}
		else
		{
			throw runtime_error ("Invalid input");
		}
	}
	result = get_result ();
	if (!numStk.empty () || !iss.eof ())
	{
		throw runtime_error ("Invalid expression");
	}
	return result;
}

/**
 * @brief Retrieves the result of the Reverse Polish Notation (RPN)
 * calculation.
 *
 * This function returns the top element from the numStk stack, which
 * represents the result of the RPN calculation. The top element is then
 * removed from the stack.
 *
 * @return The result of the RPN calculation.
 */
double RPN::get_result ()
{
	double result (numStk.top ());
	numStk.pop ();
	return result;
}

/**
 * @brief Pops the top two elements from the numStk stack and assigns them to
 * _fnum and _snum respectively.
 *
 * This function is used in Reverse Polish Notation (RPN) evaluation to
 * retrieve the top two numbers from the stack. The top element is assigned to
 * _fnum and the second top element is assigned to _snum. After assigning the
 * values, the top two elements are removed from the stack.
 */
void RPN::pop_two ()
{
	_fnum = numStk.top ();
	numStk.pop ();
	_snum = numStk.top ();
	numStk.pop ();
}

/**
 * Performs the specified operation on the top two numbers in the numStk stack.
 *
 * @param opr The operation to be performed.
 * @throws std::runtime_error if there are less than 2 numbers in the numStk
 * stack.
 */
void RPN::do_operation (char opr)
{
	if (numStk.size () < 2)
	{
		throw runtime_error ("Invalid expression");
	}

	switch (opr)
	{
	case ADD:
	{
		pop_two ();
		numStk.push (_snum + _fnum);
		break;
	}
	case SUB:
	{
		pop_two ();
		numStk.push (_snum - _fnum);
		break;
	}
	case MULT:
	{
		pop_two ();
		numStk.push (_snum * _fnum);
		break;
	}
	case DIV:
	{
		pop_two ();
		numStk.push (_snum / _fnum);
		break;
	}
	default: break;
	}
}

bool RPN::is_number (char entry)
{
	return (std::isdigit (entry));
}

bool RPN::is_operand (char entry)
{
	return (entry == '*' || entry == '/' || entry == '+' || entry == '-');
}
