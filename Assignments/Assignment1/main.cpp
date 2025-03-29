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
        std::regex rgx(R"(\d+\.\d+)");
        auto begin = std::sregex_iterator(str.begin(), str.end(), rgx);
        auto end = std::sregex_iterator();

        std::cout << "Found " << std::distance(begin, end) << " numbers with a decimal point:\n";
        for (std::sregex_iterator i = begin; i != end; ++i)
        {
            std::smatch match = *i;
            std::cout << match.str() << "\n";
        }
    }

    // Using ctre
    {
        ScopedTimer st{"crte duration: "};
        for (auto m : ctre::search_all<"\\d+\\.\\d+">(str)) 
        {
            std::cout << m.to_view() << "\n";
        }
    }
    
    return 0;

}