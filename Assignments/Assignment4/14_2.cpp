#include <iterator>
#include <algorithm>
#include <functional>
#include <list>
#include <iostream>

namespace mpcs
{
template<class BidirIt, class Compare = std::less<>>
void sort(BidirIt first, BidirIt last, Compare cmp = Compare()) 
{
    if (first == last) 
        return;
    BidirIt next = first;
    if (++next == last) 
        return;

    auto slow = first, fast = first;
    while (true) 
    {
        ++fast; 
        if (fast == last) break;
        ++fast; 
        if (fast == last) break;
        ++slow;
    }
    BidirIt mid = std::next(slow);

    mpcs::sort(first, mid, cmp);
    mpcs::sort(mid, last,  cmp);

    std::inplace_merge(first, mid, last, cmp);
}
}

int main()
{
    std::list<int> L = {5,1,4,2,3};
    mpcs::sort(L.begin(), L.end());   
    
    for (auto elem : L)
        std::cout << elem << ',';
}