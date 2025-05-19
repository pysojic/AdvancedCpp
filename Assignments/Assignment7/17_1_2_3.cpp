#include <iostream>
#include <concepts>
#include <type_traits>

/*
Exercice 17_1 Answer:

Feature-test macros need to be available during the preprocessing phase, 
before the compiler has parsed any C++ constructs, 
so they must be defined as preprocessor macros rather than as language-level constants; 
a constexpr variable simply isn’t visible to the preprocessor and therefore cannot be used in #if or #ifdef directives. 
By using #define, both standard headers and build tools can inject or override those macros, 
enabling conditional compilation of headers or code based on which features the compiler and standard library actually support. 
This approach also maintains consistency with C’s long-established feature macros like __STDC_VERSION__, ensures toolchain support for feature testing at preprocessing time, 
and allows library headers to guard their own contents before any C++ parsing or name lookup occurs.
*/


// Concept version
template<template<class> class Pred, class Tuple>
struct Filter;

template<template<class> class Pred>
struct Filter<Pred, std::tuple<>> {
    using type = std::tuple<>;
};

template<template<class> class Pred, class Head, class... Tail>
    requires Pred<Head>::value
struct Filter<Pred, std::tuple<Head, Tail...>> {
    using type = decltype(
        std::tuple_cat(
            std::tuple<Head>{},
            std::declval<typename Filter<Pred, std::tuple<Tail...>>::type>()
        )
    );
};

template<template<class> class Pred, class Head, class... Tail>
    requires (!Pred<Head>::value)
struct Filter<Pred, std::tuple<Head, Tail...>> {
    using type = typename Filter<Pred, std::tuple<Tail...>>::type;
};

template<class Tuple, template<class> class Pred>
using Filter_t = typename Filter<Pred, Tuple>::type;


// void_t version
template<template<class> class Pred, class Tuple, class = void>
struct Filter2;

template<template<class> class Pred>
struct Filter2<Pred, std::tuple<>> {
    using type = std::tuple<>;
};

template<template<class> class Pred, class Head, class... Tail>
struct Filter2<
    Pred,
    std::tuple<Head, Tail...>,
    std::enable_if_t<Pred<Head>::value>
> {
    using type = decltype(
        std::tuple_cat(
            std::tuple<Head>{},
            std::declval<typename Filter2<Pred, std::tuple<Tail...>>::type>()
        )
    );
};

template<template<class> class Pred, class Head, class... Tail>
struct Filter2<
    Pred,
    std::tuple<Head, Tail...>,
    std::enable_if_t<!Pred<Head>::value>
> {
    using type = typename Filter2<Pred, std::tuple<Tail...>>::type;
};

template<class Tuple, template<class> class Pred>
using Filter2_t = typename Filter<Pred, Tuple>::type;

int main()
{
    static_assert(std::is_same_v<
        Filter_t<std::tuple<long, float>, std::is_integral>,
        std::tuple<long>
    >);

    static_assert(std::is_same_v<
        Filter2_t<std::tuple<long, float>, std::is_integral>,
        std::tuple<long>
    >);
}

// Exercice 17_3 Answer:

/* 
1. requires clause on the template header

template<typename T>
requires std::copy_constructible<T>
T duplicate(T const &t) 
{
    return t;
}

We could use this when we want our constraint to be immediately visible alongside the template parameters, 
and when we may combine several requirements:

template<typename T>
requires std::copy_constructible<T> && std::default_initializable<T>
T make_and_copy(T const &t) { … }

Because it sits right after the <…>, 
it’s easy to scan which concepts apply to all parameters, especially in more complex templates.
*/

/*
2. Trailing requires clause on the declaration

template<typename T>
T duplicate(T const &t)
requires std::copy_constructible<T>
{
    return t;
}

This style keeps the signature first and the constraint second, 
much like a throws-clause in Java or the noexcept specifier in C++. It reads top-down:

-> “Here’s my function.”
-> “Oh, and by the way, T must be copy-constructible.”

We could use it when we want the return type and parameter list to be our readers’ first focus.
*/

/*
3. Constrained template header (abbreviated parameter)

template<std::copy_constructible T>
T duplicate(T const &t) 
{
    return t;
}

This is compact and makes each parameter self-documenting: every time we see T, 
we know it’s copy_constructible. 
It’s ideal when every template parameter carries a single concept and we don’t need complex boolean combinations. 
It also scales nicely when we have multiple parameters each with its own concept:

template<std::integral I, std::floating_point F>
auto mix(I i, F f) { … }
*/

/*
4. Function-template abbreviated syntax (“terse”)

auto duplicate(std::copy_constructible auto const &t) 
{
    return t;
}

This is the most concise: it fuses template declaration and parameter in one go.
Great for small, utility-like functions where the only template “plumbing” is the concept itself. 
Because there’s no explicit template<…> line, it reads almost like overload resolution:

auto add(std::integral auto a, std::integral auto b) 
{
    return a + b;
}

We could use it when brevity matters and the concept is the only template requirement.
*/
