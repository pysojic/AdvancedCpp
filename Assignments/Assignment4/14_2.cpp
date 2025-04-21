#include <iterator>
#include <algorithm>
#include <functional>
#include <list>
#include <iostream>
#include <type_traits>

template<class BidirIt, class Compare = std::less<>>
void merge_sort(BidirIt first, BidirIt last, Compare cmp = Compare()) 
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

    merge_sort(first, mid, cmp);
    merge_sort(mid, last,  cmp);

    std::inplace_merge(first, mid, last, cmp);
}

int main()
{
    std::list<int> L = {5,1,4,2,3};
    merge_sort(L.begin(), L.end());   
    
    for (auto elem : L)
        std::cout << elem << ',';
}