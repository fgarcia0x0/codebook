#pragma once

#include <algorithm>
#include <functional>
#include <iterator>
#include <utility>

namespace codebook::algorithms::sorting
{

	namespace internal
	{
		template <std::random_access_iterator RandomIter, 
			  std::predicate<std::iter_value_t<RandomIter>,
			  				 std::iter_value_t<RandomIter>>
			  				 Comparator = std::less<>>
		void merge(RandomIter first,
				   RandomIter middle,
				   RandomIter last,
				   Comparator&& cmp = {})
		{
			if (first == middle || middle == last)
				return;
			
			using RandomIterValueType = std::iter_value_t<RandomIter>;

			std::size_t n1 = static_cast<std::size_t>(std::distance(first, middle));
			std::size_t n2 = static_cast<std::size_t>(std::distance(middle, last));

			std::vector<RandomIterValueType> left_vec;
			left_vec.reserve(n1);

			std::vector<RandomIterValueType> right_vec;
			right_vec.reserve(n2);

			std::copy(first, middle, std::back_inserter(left_vec));
			std::copy(middle, last, std::back_inserter(right_vec));

			/*
			std::merge(left_vec.begin(), left_vec.end(), 
					   right_vec.begin(), right_vec.end(), 
					   first, std::move(cmp));
			*/

			auto left_iter = left_vec.begin();
			auto right_iter = right_vec.begin();
			auto result = first;

			while ((left_iter != left_vec.end()) && (right_iter != right_vec.end()))
				*result++ = cmp(*left_iter, *right_iter) ? *left_iter++ : *right_iter++;

			// copy rest of left_vec + rest of right_vec
			std::copy(right_iter, right_vec.end(), 
					  std::copy(left_iter, left_vec.end(), result));
		}
	}

	template <std::random_access_iterator RandomIter, 
			  std::predicate<std::iter_value_t<RandomIter>,
			  				 std::iter_value_t<RandomIter>>
			  				 Comparator = std::less<>>
	constexpr void merge_sort(RandomIter begin,
							  RandomIter end,
							  Comparator&& cmp = {})
	{
		using DiffType = std::iter_difference_t<RandomIter>;
		DiffType diff = std::distance(begin, end);

		if (diff > DiffType{ 1 })
		{
			RandomIter mid = begin + diff / 2;
			merge_sort(begin, mid);
			merge_sort(mid, end);
		    internal::merge(begin, mid, end, std::move(cmp));
		}
	}
}
