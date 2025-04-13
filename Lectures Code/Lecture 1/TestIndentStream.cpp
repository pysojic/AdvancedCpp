#include <iostream>
#include "IndentStream.h"

using namespace std;
using namespace mpcs;

int main()
{

	IndentStream ins(cout);
	ins << " /*\n" 
		<< indent << "This function calculates the Fibonacci sequence,\n"
		          << "which is defined by Wikipedia as follows:\n\n"
	    << indent;
	ins << "In mathematics, the Fibonacci numbers,\n"
		<< "commonly denoted Fn form a sequence,\n"
		<< "called the Fibonacci sequence, such that each\n"
		<< "number is the sum of the two preceding ones,\n"
		<< "starting from 0 and 1.\n";
	ins << unindent << unindent << " */\n\n";
	ins << "int" << endl;
	ins << "fib(int n) {" << indent << endl;
	ins << "if (n == 0) " << indent << endl;
	ins << "return 0;" << unindent << endl;
	ins << "if (n == 1) " << indent << endl;
	ins << "return 1;" << unindent << endl;
	ins << "return fib(n-2) + fib(n-1);" << unindent << endl;
	ins << "}" << endl;
	return 0;
}
