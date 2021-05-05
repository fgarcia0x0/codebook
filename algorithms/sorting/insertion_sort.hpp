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
	constexpr void insertion_sort(RandomIter begin,
								  RandomIter end,
								  Comparator&& cmp = {})
	{
		RandomIter prev{ };

		for (RandomIter i = std::next(begin); i < end; ++i)
		{
			for (RandomIter curr = i; curr > begin; --curr)
			{
				prev = std::prev(curr);

				if (cmp(*prev, *curr))
					break;

				std::iter_swap(prev, curr);
			}
		}
	}
}


