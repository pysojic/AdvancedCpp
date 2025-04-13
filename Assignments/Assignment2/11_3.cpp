#include <iostream>
#include <tuple>
#include <type_traits>

#include "include/Tuple.h"

int main()
{
    using Tuple = mpcs::Tuple2<int, double, char, int, double>;

    Tuple tup{1, 2.0, 'a', 3, 4.9};

   // std::cout << mpcs::get<double>(tup); // Assertion fail, double appears multiple times
   // std::cout << mpcs::get<float>(tup); // Assertion fail, float is not in the tuple
   std::cout << mpcs::get<char>(tup); // OK
}