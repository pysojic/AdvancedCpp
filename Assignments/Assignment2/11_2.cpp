#include <iostream>
#include <tuple>
#include <type_traits>

constexpr size_t length(const std::tuple<>&) 
{
    return 0;
}

template <typename T, typename... Ts>
constexpr size_t length(const std::tuple<T, Ts...>&) 
{
    return 1 + length(std::tuple<Ts...>{});
}

template <typename List, std::size_t index>
struct TypeAt;

template <typename Head, typename... Tail>
struct TypeAt<std::tuple<Head, Tail...>, 0>
{
    using type = Head;
};

template <typename Head, typename... Tail, size_t i>
struct TypeAt<std::tuple<Head, Tail...>, i>
{
    using type = TypeAt<std::tuple<Tail...>, i - 1>::type;
};

int main()
{
    using Tuple = std::tuple<int, char, double>;
    Tuple tup = {1,2,3};

    std::cout << length(tup) << std::endl; // OK

    std::cout << typeid(TypeAt<Tuple, 1>::type).name() << std::endl;

    /*
        We can see that we can indeed have a constexpr function that returns the length of a tuple at compile time.
        Personally, I still prefer the template way, as it clearly indicates to the caller that the length is returned
        at compile time, while I might need to go check that the function declaration of length() is constexpr if I want to ensure 
        that it is evaluated at compile time (could make it consteval). The advantage of the constexpr function, however, is that
        it can work both at runtime and compile time, and is somewhat easier to code.
    */

    /*
        It is not possible to have a constexpr function of TypeAt since functions cannot return types.
        A constexpr function simply cannot return a type because types and values live in different "domains" of the language. 
        Types are part of the compile-time type system and are handled via templates, 
        whereas constexpr functions operate on values—even if those values are known at compile time.
    */
}