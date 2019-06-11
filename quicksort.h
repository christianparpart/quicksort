// This file is part of the "quicksort" project, http://github.com/christianparpart/quicksort>
//   (c) 2019 Christian Parpart <christian@parpart.family>
//
// Licensed under the MIT License (the "License"); you may not use this
// file except in compliance with the License. You may obtain a copy of
// the License at: http://opensource.org/licenses/MIT

#pragma once
#include <utility>
#include <iterator>
#include <cstddef>

namespace quicksort {

struct AlgorithmStats {
	size_t recursionDepth = 0;
	size_t swapCount = 0;
	size_t iterationCount = 0;
};

inline std::ostream& operator<<(std::ostream& out, AlgorithmStats const& stats)
{
	out << "{recursionDepth: " << stats.recursionDepth
		<< ", swaps: " << stats.swapCount
		<< ", iterations, " << stats.iterationCount
		<< "}";
	return out;
}

template <typename Container>
auto partition(Container& p, std::size_t low, std::size_t high, AlgorithmStats& stats) -> std::size_t
{
	auto i = low - 1;
	auto const pivot = p[high];
	auto const incAndSwap = [&](size_t j) {
		++i;
		std::swap(p[i], p[j]);
		stats.swapCount++;
	};

	for (auto j = low; j < high; ++j, stats.iterationCount++)
		if (p[j] <= pivot)
			incAndSwap(j);

	incAndSwap(high);

	return i;
}

template <typename Container>
void quicksort(Container& p, std::size_t low, std::size_t high, AlgorithmStats& stats)
{
	stats.recursionDepth++;

	if (low < high)
	{
		auto const pi = partition(p, low, high, stats);
		if (pi > 0)
			quicksort(p, low, pi - 1, stats);
		quicksort(p, pi + 1, high, stats);
	}
}

template <typename Container>
auto sort(Container& p) -> AlgorithmStats
{
	AlgorithmStats stats;
	if (std::size(p))
		quicksort(p, 0, std::size(p) - 1, stats);
	return stats;
}

} // namespace quicksort
