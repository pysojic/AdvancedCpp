#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>
#include <execution>

#include "StopWatch.hpp"

int main()
{
    std::vector<double> vec;
    vec.reserve(1'000'000);

    std::random_device rd;
    std::mt19937_64 mt(rd());
    std::normal_distribution norm(0.0, 1.0);

    
    std::generate_n(std::back_inserter(vec), vec.capacity(), [&]() { return norm(mt); });
    std::vector<double> vec2(vec);
    std::vector<double> vec3(vec);
    
    {
        ScopedTimer timer1("std::execution::seq: ");
        std::sort(std::execution::seq, vec.begin(), vec.end());
    }

    {
        ScopedTimer timer1("std::execution::par: ");
        std::sort(std::execution::par, vec.begin(), vec.end());
    }

    {
        ScopedTimer timer1("std::execution::par_unseq: ");
        std::sort(std::execution::par_unseq, vec.begin(), vec.end());
    }

    /*
        The par and par_unseq execution policies are about 2 times faster that the seq policy.mt
        There is no tangible difference between the par and par_unseq policies.
    */
}