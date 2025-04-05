#include "variadic_examples.h"
#include <iostream>
#include<typeinfo>
using namespace std;
using namespace mpcs;
struct A {
	static void foo() { cout << "In A" << endl; }
};
struct B {
	static void foo() { cout << "In B" << endl; }
};
typedef tuple<A, B> AB;
typedef tuple<char, unsigned char, signed char> CharTypes;

int main()
{
	cout << Length<CharTypes>::value << endl; // Prints 3 because 3 types in CharTypes
	TypeAt<AB, 1>::type::foo(); // Prints "In B" because B is the 1st type of tuple<A, B> (A is the 0th type)
	cout << IndexOf<CharTypes, unsigned char>::value << endl; // Prints 1 because unsigned char is the 1st type of the CharTypes tuple

	typedef Append<AB, tuple<int>>::type ABint; // ABint is tuple<A, B, int>
	cout << IndexOf<ABint, int>::value << endl; // Prints 2 because int is the 2nd type in tuple<A, B, int>

	typedef Replace<tuple<int, double>, int, double>::type ABdouble; // ABdouble is tuple<A, B, double>
	cout << IndexOf<ABdouble, double>::value << endl; // Prints 2 because double is the 2nd type in tuple<A, B, double>

	static_assert(is_same_v<Replace<CharTypes, double, void>::type, CharTypes>, "Unexpected type change");
	return 0;
}