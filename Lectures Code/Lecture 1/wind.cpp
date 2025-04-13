#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>
#include <string>

using namespace std;
ofstream output("output.csv");

int
knotsToSaffirSimpson(int knots)
{
    if(knots < 64) {
        return 0;
    }
    if(knots < 83) {
        return 1;
    }
    if(knots < 96) {
        return 2;
    }
    if(knots < 114) {
        return 3;
    }
    if(knots < 136) {
        return 4;
    }
    return 5;
}

class YearEntry {
public:
    YearEntry() : ssDays(0) {}
    void addKnots(string str) {
        ssDays += knotsToSaffirSimpson(stoi(str))/4.0;
    }
    double ssDays;
};

void 
print_year(pair<int const, YearEntry> year_entry_pair) 
{
    output << year_entry_pair.first << ", " << year_entry_pair.second.ssDays << endl;
}

int main()
{
    int first_year = numeric_limits<int>::max();
    int last_year = 0;
    map<int, YearEntry > ssMap;
    string line;
    YearEntry *currentYearEntry = nullptr;
    ifstream tracks(".\\hurdat_atlantic_1851-2011.txt");
    smatch what;
    regex headerRegex(R"((?:\d{2}/){2}(\d{4}))"); // See how much nicer raw strings are for regexes
	regex dayRegex(".{11}[*SEWLD].{7}\\s+(\\d+).{13}\\s+(\\d+).{13}\\s+(\\d+).{13}\\s+(\\d+).*");

    while(getline(tracks, line)) {
        if(regex_search(line, what, headerRegex)) {
			//cout << line;  // just so we can see progress...
            int currentYear{};
            istringstream yearstream(what[1].str());
            yearstream >> currentYear;
            first_year = min(first_year, currentYear);
            last_year = max(last_year, currentYear);
            currentYearEntry = &ssMap[currentYear];
            continue;
        } else if ( regex_search( line, what, dayRegex ) ) {        
			currentYearEntry->addKnots(what[1]);
			currentYearEntry->addKnots(what[2]);
			currentYearEntry->addKnots(what[3]);
			currentYearEntry->addKnots(what[4]);
		}
    }
	output << "Year, Saffir-Simpson Days" << endl;
	for(int i = first_year; i <= last_year; i++) {
		print_year({ i, ssMap[i] });
    }
}
