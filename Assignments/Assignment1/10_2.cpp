#include <iostream>
#include <regex>
#include <fstream>
#include <map>

#include "ctre.hpp"

int windCategory(int speed) 
{ 
    if (speed >= 136) 
        return 5; 
    else if (speed >= 114) 
        return 4; 
    else if (speed >= 96) 
        return 3; 
    else if (speed >= 83) 
        return 2;
    else if (speed >= 64) 
        return 1; 
    else 
        return 0; 
}

void saffir_simpson_stl(std::ifstream& filestream)
{
    // regex for header line: capture the date (and hence the year) and the M= value (number of days)
    std::regex headerRegex(R"(\d+\s+(\d{2})\/(\d{2})\/(\d{4}).*M=\s*(\d+))");
    // regex for extracting all digit groups from a daily data line
    std::regex digitRegex(R"(\d+)");

    std::string line;
    std::map<int, double> annualTotals;  // year -> sum of (category/4) for each reading

    while (std::getline(filestream, line)) 
    {
        // skip empty lines
        if(line.empty()) 
            continue;

        std::smatch headerMatch;
        if(std::regex_search(line, headerMatch, headerRegex)) 
        {
            int year = std::stoi(headerMatch[3].str());
            int numDays = std::stoi(headerMatch[4].str());
            // process the next numDays lines (each contains 4 quarter-day readings)
            for (int i = 0; i < numDays; i++) 
            {
                if (!std::getline(filestream, line)) 
                    break;
                // extract all digit tokens from the daily line
                std::sregex_iterator iter(line.begin(), line.end(), digitRegex);
                std::sregex_iterator end;
                std::vector<int> tokens;
                for (; iter != end; ++iter) 
                {
                    tokens.push_back(std::stoi(iter->str()));
                }
                
                double dayTotal = 0.0;
                for (int j = 0; j < 4; j++) 
                {
                    int wind = tokens[5 + j*4];
                    int category = windCategory(wind);
                    dayTotal += (category / 4.0);
                }
                annualTotals[year] += dayTotal;
            }
        }
        // If the line is not a header, then skip
    }

    std::cout << "Year\tSaffir-Simpson Days" << std::endl;
    for (const auto& entry : annualTotals) 
    {
        std::cout << entry.first << "\t" << entry.second << std::endl;
    }
}

void saffir_simpson_ctre(std::ifstream& filestream)
{
    std::map<int, double> annualTotals;

    std::string line;
    while (std::getline(filestream, line)) 
    {
        if (line.empty()) 
            continue;

        if (auto [a,b,c,d,e] = ctre::match<R"(\d+\s+(\d{2})\/(\d{2})\/(\d{4}).*M=\s*(\d+))">(line); a) 
        {
            int year = std::stoi(a.to_string());
            int numDays = std::stoi(d.to_string());

            // Process the next numDays lines (each containing 4 quarter-day readings)
            for (int i = 0; i < numDays; i++) 
            {
                if (!std::getline(filestream, line)) break;

                // Use CTRE to extract all digit tokens from the line.
                std::vector<int> tokens;
                for (auto token : ctre::search_all<"(\\d+)">(line)) 
                {
                    tokens.push_back(std::stoi(token.to_string()));
                }
                
                // Wind speeds are assumed to be at indices 5, 9, 13, and 17.
                double dayTotal = 0.0;
                for (int j = 0; j < 4; j++) 
                {
                    int wind = tokens[5 + j * 4];
                    int category = windCategory(wind);
                    dayTotal += (category / 4.0);
                }
                annualTotals[year] += dayTotal;
            }
        }
    }

    std::cout << "Year\tSaffir-Simpson Days" << std::endl;
    for (const auto& entry : annualTotals) 
    {
    std::cout << entry.first << "\t" << entry.second << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << "hurdat_atlantic_1851-2011.txt" << std::endl; 
        return EXIT_FAILURE; 
    }

    std::ifstream infile(argv[1]);
    if (!infile) 
    {
        std::cerr << "Error opening file " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    // saffir_simpson_stl(infile);

    saffir_simpson_ctre(infile);

    return 0;
}