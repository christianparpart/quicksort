// This file is part of the "quicksort" project, http://github.com/christianparpart/quicksort>
//   (c) 2019 Christian Parpart <christian@parpart.family>
//
// Licensed under the MIT License (the "License"); you may not use this
// file except in compliance with the License. You may obtain a copy of
// the License at: http://opensource.org/licenses/MIT

#pragma once

#include <chrono>
#include <cstddef>
#include <iostream>

namespace sorting {

struct AlgorithmStats {
    size_t callCount = 0;
    size_t swapCount = 0;
    size_t iterationCount = 0;
    size_t recursionDepth = 0;
    size_t currentRecursionDepth = 0;

    std::chrono::time_point<std::chrono::steady_clock> const start = std::chrono::steady_clock::now();

    std::chrono::milliseconds elapsed() const noexcept
    {
		auto const ns = std::chrono::steady_clock::now() - start;
		auto const ms = std::chrono::duration_cast<std::chrono::milliseconds>(ns);
		return ms;
    }

    void enter() noexcept
    {
        ++callCount;
        ++currentRecursionDepth;
        if (currentRecursionDepth > recursionDepth)
            recursionDepth = currentRecursionDepth;
    }

    void leave() noexcept { --currentRecursionDepth; }
};

inline std::ostream& operator<<(std::ostream& out, AlgorithmStats const& stats)
{
    out << "{swaps: " << stats.swapCount << ", iterations, " << stats.iterationCount
        << ", recursion: " << stats.recursionDepth << ", calls: " << stats.callCount
        << ", msecs: " << stats.elapsed().count() << "}";
    return out;
}

}  // namespace sorting
