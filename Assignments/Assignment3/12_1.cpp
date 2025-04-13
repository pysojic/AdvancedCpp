#include <iostream>
#include <type_traits>

template <typename T>
struct remove_all_pointers
{
    using type = T;
};

template <typename T>
struct remove_all_pointers<T*>
    : public remove_all_pointers<T>
{
};

template <typename T>
using remove_all_pointers_t = typename remove_all_pointers<T>::type;

int main()
{
    std::cout << std::is_same_v<remove_all_pointers_t<int*****>, int> << std::endl;
    std::cout << std::is_same_v<remove_all_pointers_t<int*****>, int*> << std::endl;
}