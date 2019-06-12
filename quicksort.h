// This file is part of the "quicksort" project,
// http://github.com/christianparpart/quicksort>
//   (c) 2019 Christian Parpart <christian@parpart.family>
//
// Licensed under the MIT License (the "License"); you may not use this
// file except in compliance with the License. You may obtain a copy of
// the License at: http://opensource.org/licenses/MIT

#pragma once

#include "stats.h"

#include <cassert>
#include <cstddef>
#include <iterator>
#include <utility>

namespace sorting::quicksort {

// various pivot selector implementations
constexpr size_t pivotNaive(size_t low, size_t high)
{
    return high;
}

constexpr size_t pivotMiddle(size_t low, size_t high)
{
    return (low + high) / 2;
}

template <typename Container, typename Pivot>
auto partition(Container& p, size_t low, size_t high, Pivot selectPivot, AlgorithmStats& stats) -> size_t
{
    auto i = low - 1;
    auto const pivot = selectPivot(low, high);  // p[high];
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

template <typename Container, typename Pivot>
void sort(Container& p, size_t low, size_t high, Pivot pivot, AlgorithmStats& stats)
{
    stats.enter();

    if (low < high)
    {
        auto const pi = partition(p, low, high, pivot, stats);
        if (pi > 0)
            sort(p, low, pi - 1, pivot, stats);
        sort(p, pi + 1, high, pivot, stats);
    }

    stats.leave();
}

template <typename Container>
auto sort(Container& p) -> AlgorithmStats
{
    AlgorithmStats stats;
    if (auto size = std::size(p); size != 0)
        sort(p, 0, size - 1, pivotMiddle, stats);
    return stats;
}

}  // namespace sorting::quicksort
