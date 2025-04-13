#include <tuple>
#include <iostream>
#include <type_traits>

template<class First, class Second> 
struct Append;

template<typename... Ts, typename... Us>
struct Append<std::tuple<Ts...>, std::tuple<Us...> >
{
    using type = std::tuple<Ts..., Us...>;
};

template<typename T, typename A, typename B> 
struct Replace;

template<typename... Ts, typename A, typename B>
struct Replace<std::tuple<A, Ts...>, A, B> 
{
    using type = std::tuple<B, Ts...>;
};

// This meta function and the following are identical, just different styles
// Here we inherit the type member from Append
template<typename H, typename... Ts, typename A, typename B>
struct Replace<std::tuple<H, Ts...>, A, B>
: public Append<std::tuple<H>, typename Replace<std::tuple<Ts...>, A, B>::type> 
{
};

// Here we declare Replace::type directly
template<typename H, typename... Ts, typename A, typename B>
struct Replace<std::tuple<H, Ts...>, A, B>
{
    using type = Append<std::tuple<H>, typename Replace<std::tuple<Ts...>, A, B>::type>::type>;
};

template<typename T, typename A, typename B>
struct ReplaceAll;

template <typename A, typename B>
struct ReplaceAll<std::tuple<>, A, B>
{
    using type = std::tuple<>;
};

template<typename... Ts, typename A, typename B>
struct ReplaceAll<std::tuple<A, Ts...>, A, B>
// : public Append<std::tuple<B>, typename ReplaceAll<std::tuple<Ts...>, A, B>::type> // Equivalent
{
    using type = Append<std::tuple<B>, typename ReplaceAll<std::tuple<Ts...>, A, B>::type>::type;
};

template<typename H, typename... Ts, typename A, typename B>
struct ReplaceAll<std::tuple<H, Ts...>, A, B>
// " Append<std::tuple<H>, typename ReplaceAll<std::tuple<Ts...>, A, B>::type> // Equivalent
{
    using type = Append<std::tuple<H>, typename ReplaceAll<std::tuple<Ts...>, A, B>::type>::type;
};

int main()
{
    using Test = std::tuple<int, double, int, char, double , int>;

    static_assert(std::is_same_v<ReplaceAll<Test, int, double>::type, std::tuple<double, double, double, char, double, double>>, 
        "Types are not equal");

    using Test2 = std::tuple<char, double, int, int>;

    static_assert(std::is_same_v<ReplaceAll<Test2, double, uint16_t>::type, std::tuple<char, uint16_t, int, int>>, 
        "Types are not equal"); 
}