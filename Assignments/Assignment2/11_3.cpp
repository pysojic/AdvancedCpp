#include <iostream>
#include <tuple>
#include <type_traits>

#include "include/Tuple.h"

int main()
{
    using Tuple = mpcs::Tuple2<int, double, char, int, double>;

    using Types = mpcs::IndexOf<Tuple, double>::type;

    std::cout << mpcs::Getter3<Tuple, double>::value;
}