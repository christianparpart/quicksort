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
#include <cassert>

namespace quicksort {

struct AlgorithmStats {
	std::size_t callCount = 0;
	std::size_t swapCount = 0;
	std::size_t iterationCount = 0;
	std::size_t recursionDepth = 0;
	std::size_t currentRecursionDepth = 0;
};

inline std::ostream& operator<<(std::ostream& out, AlgorithmStats const& stats)
{
	out << "{swaps: " << stats.swapCount
		<< ", iterations, " << stats.iterationCount
		<< ", recursion: " << stats.recursionDepth
		<< ", calls: " << stats.callCount
		<< "}";
	return out;
}

// various pivot selector implementations
size_t pivotNaive(std::size_t low, std::size_t high) { return high; }
size_t pivotMiddle(std::size_t low, std::size_t high) { return (low + high) / 2; }

template <typename Container, typename Pivot>
auto partition(Container& p, std::size_t low, std::size_t high, Pivot selectPivot, AlgorithmStats& stats) -> std::size_t
{
	auto i = low - 1;
	auto const pivot = selectPivot(low, high); //p[high];
	auto const incAndSwap = [&](std::size_t j) {
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

template <typename Container, typename Pivot>
void quicksort(Container& p, std::size_t low, std::size_t high, Pivot pivot, AlgorithmStats& stats)
{
	stats.callCount++;
	stats.currentRecursionDepth++;
	if (stats.recursionDepth < stats.currentRecursionDepth)
		stats.recursionDepth = stats.currentRecursionDepth;

	if (low < high)
	{
		auto const pi = partition(p, low, high, pivot, stats);
		if (pi > 0)
			quicksort(p, low, pi - 1, pivot, stats);
		quicksort(p, pi + 1, high, pivot, stats);
	}

	stats.currentRecursionDepth--;
}

template <typename Container>
auto sort(Container& p) -> AlgorithmStats
{
	AlgorithmStats stats;
	if (auto size = std::size(p); size != 0)
		quicksort(p, 0, size - 1, pivotMiddle, stats);
	return stats;
}

} // namespace quicksort
