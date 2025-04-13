#include<regex>
#include<iomanip>
#include<iostream>
using namespace std;

int main()
{
  string text("Here are some numbers: 1.23, 4, 5.6, 7.89");
  regex decimal(R"((\d+)\.(\d+))");
  smatch results;
  while (regex_search(text, results, decimal)) {
    cout << results[1] << " is before the decimal, and " << results[2] << " is after the decimal" << endl;
    text = results.suffix();
  }
  return 0;
}