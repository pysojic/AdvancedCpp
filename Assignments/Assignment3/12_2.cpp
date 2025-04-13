#include <iostream>
#include <type_traits>

template<typename T>
struct is_reference
{
    static constexpr bool value = false;
};

template<typename T>
struct is_reference<T&>
{
    static constexpr bool value = true;
};

template<typename T>
struct is_reference<T&&>
{
    static constexpr bool value = true;
};

template <typename T>
constexpr bool is_reference_v = is_reference<T>::value;

template<typename T>
struct remove_reference
{
    using type = T;
};

template<typename T>
struct remove_reference<T&>
{
    using type = T;
};

template<typename T>
struct remove_reference<T&&>
{
    using type = T;
};

template<typename T>
using remove_reference_t = remove_reference<T>::type;

int main()
{
    std::cout << "Check non-reference type: " << is_reference_v<int> << std::endl;
    std::cout << "Check lvalue reference type: " << is_reference_v<int&> << std::endl;
    std::cout << "Check rvalue reference type: " << is_reference_v<int&&> << std::endl;

    std::cout << "\nCheck removing lvalue reference type: " << std::is_reference_v<remove_reference_t<int&>> << std::endl;
    std::cout << "Check removing rvalue reference type: " << std::is_reference_v<remove_reference_t<int&&>> << std::endl;
}