// To run each assignment part, change the CMakeLists.txt file with the associated cpp file

#include <iostream>
#include <regex>
#include <string>

#include "ctre.hpp"
#include "StopWatch.hpp"

int main()
{
// HW 10-1
    std::string str{"1.23, 4, 5.6, 7.89"};
    // Using std::regex
    {
        ScopedTimer st{"std::regex duration: "};
        std::regex rgx(R"((\d+)\.(\d+))");
        auto begin = std::sregex_iterator(str.begin(), str.end(), rgx);
        auto end = std::sregex_iterator();

        std::cout << "Found " << std::distance(begin, end) << " numbers with a decimal point:\n";
        for (std::sregex_iterator i = begin; i != end; ++i)
        {
            std::smatch match = *i;
            std::string before = match[1].str();
            std::string after  = match[2].str();
            std::cout << before << " is before the decimal and " << after << " is after the decimal" << std::endl;
        }
    }

    std::cout << std::endl;

    // Using ctre
    {
        ScopedTimer st{"crte duration: "};
        for (auto& m : ctre::search_all<"(\\d+)\\.(\\d+)">(str)) 
        {
            const auto& [full, before, after] = m;
            std::cout << before << " is before the decimal and " << after << " is after the decimal" << std::endl;
        }
    }
    
    return 0;

}
