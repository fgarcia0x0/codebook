#pragma once

#include <algorithm>
#include <functional>
#include <iterator>
#include <utility>

namespace codebook::algorithms::sorting
{
	template <std::random_access_iterator RandomIter, 
			  std::predicate<std::iter_value_t<RandomIter>,
			  				 std::iter_value_t<RandomIter>>
			  				 Comparator = std::less<>>
	constexpr void selection_sort(RandomIter begin,
								  RandomIter end,
								  Comparator&& cmp = {})
	{
		for (RandomIter i = begin; i < end - 1; ++i)
		{
			RandomIter min = std::min_element(i, end, std::forward<Comparator>(cmp));
			if (min != i)
				std::iter_swap(min, i);
		}
	}
}
