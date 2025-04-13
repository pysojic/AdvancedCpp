#ifndef OPTIMIZED_COPY_H
#define OPTIMIZED_COPY_H
#include<type_traits>
#include<iterator>
using std::iterator_traits;
using std::integral_constant;
using std::true_type;
using std::enable_if_t;
using std::remove_const_t;
using std::is_trivially_copy_assignable_v;
using std::same_as;
using std::is_same_v;
using std::contiguous_iterator;
using std::contiguous_iterator_tag;

namespace mpcs {

	template<typename I1, typename I2>
	I2 optimized_copy(I1 first, I1 last, I2 out)
	{

		while (first != last)
		{
			*out = *first;
			++out;
			++first;
		}
		return out;
	}


	template<typename T>
	using iter_value_t = typename iterator_traits<T>::value_type;

	template<contiguous_iterator T, contiguous_iterator U>
	requires is_trivially_copy_assignable_v<iter_value_t<U>>
	         && same_as<remove_const_t<iter_value_t<T>>, iter_value_t<U>>
		U optimized_copy(T first, T last, U out)
	{
		memcpy(&*out, &*first, (last - first) * sizeof(iter_value_t<T>));
		return out + (last - first);
	}


}

#endif // !OPTIMIZED_COPY_H
