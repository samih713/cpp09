#include "RPN.hpp"

RPN::RPN (const string &exp) : exp (exp), _fnum (0), _snum (0)
{
}

RPN::~RPN ()
{
}

RPN::RPN (const RPN &other) : exp (other.exp), _fnum (other._fnum), _snum (other._snum)
{
}
