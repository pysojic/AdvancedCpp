#ifndef TUPLE_H
#define TUPLE_H

#include <utility>
#include <type_traits>
#include <tuple>
namespace mpcs {
	template<typename ...Ts> 
	struct Tuple2;

	template<> 
	struct Tuple2<> 
	{};

	template<typename T, typename ...Ts>
	struct Tuple2<T, Ts...> : public Tuple2<Ts...>
	{
		Tuple2(T const &t, Ts const &... ts) 
			: Tuple2<Ts...>(ts...), val(t) {}
		T val;
	};
	
	template<int i, typename ...Ts>
	struct GetterByIdx;

	template<typename T, typename ...Ts>
	struct GetterByIdx<0, T, Ts...> 
	{
		static auto const &get(Tuple2<T, Ts...> const &tup) 
		{
			return tup.val;
		}

		static auto &get(Tuple2<T, Ts...> &tup) 
		{
			return tup.val;
		}
	};

	template<int i, typename T, typename ...Ts>
	struct GetterByIdx<i, T, Ts...> 
	{
		static auto &get(Tuple2<T, Ts...> const &tup) 
		{
			Tuple2<Ts...> const &restOfVals = tup;
			return GetterByIdx<i - 1, Ts...>::get(restOfVals);
		}
	};

	template<int i, typename ...Ts>
	auto& get(Tuple2<Ts...> &tup) 
	{
		return GetterByIdx<i, Ts...>::get(tup);
	}

	//--------------- Homework ---------------

	template<class List, class Target> 
	struct IndexOf;

	template<class Target>
	struct IndexOf<Tuple2<>, Target>
	{
		static int64_t constexpr value = -1; // Return -1 if not found
		using type = Tuple2<>;
	};

	template<class ...Tail, typename Target>
	struct IndexOf<Tuple2<Target, Tail...>, Target>
	{
		static int64_t constexpr value = 0;
		using type = Tuple2<Tail...>;
	};

	template<class Head, typename... Tail, class Target>
	struct IndexOf<Tuple2<Head, Tail...>, Target>
	{
		private: // Using a Compile-time temporary
		static int64_t constexpr temp = IndexOf<Tuple2<Tail...>, Target>::value;
		public:
		static int64_t constexpr value = temp == -1 ? -1 : 1 + temp;
		using type = IndexOf<Tuple2<Tail...>, Target>::type;
	};

	/*
	Idea: Make a function that splice the tuple at the found type (so we want the rest of the types after the first occurence
	of the target type). From there, re-check the rest of the types using the IndexOf function:
	- if the returned index is -1, all good, there is no ambiguity
	- if the returned index is not -1, then we have more than one occurence of the target which is ambiguous, which should fail
	*/

	template<typename List, typename Target>
	struct GetterByType;

	template<typename... Ts, typename Target>
	struct GetterByType<Tuple2<Ts...>, Target>
	{
		// First store the result of the IndexOf function to avoid multiple calls
		using Info = IndexOf<Tuple2<Ts...>, Target>;

		static int64_t constexpr value = Info::value; // Extract the index of the Target type if found
		using Remaining = Info::type; // Extract the types remaining (after the target)

		// If value is -1, this means the target was not found
		static_assert(value != -1, "Does not contain the type");
		// If value is NOT -1 with the remaining types, 
		// this means the target was found multiple times, hence this is an ambiguous call
		static_assert(IndexOf<Remaining, Target>::value == -1, "Ambiguous call");
	};

	template<typename... Ts, typename Target>
	struct GetterByType<Tuple2<Target, Ts...>, Target>
	{
		
	};

	template<typename Target, typename ...Ts>
	auto& get(Tuple2<Ts...>& tup)
	{
		using Info = GetterByType<Tuple2<Ts...>, Target>; // Compute index and ensure uniqueness
		return GetterByIdx<Info::value, Ts...>::get(tup);
	}
}

#endif