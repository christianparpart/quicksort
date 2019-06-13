#! /usr/bin/env python3
# This file is part of the "quicksort" project, http://github.com/christianparpart/quicksort>
#   (c) 2019 Christian Parpart <christian@parpart.family>
#   (c) 2019 Kei Thoma <thomakei@gmail.com>
#
# Licensed under the MIT License (the "License"); you may not use this
# file except in compliance with the License. You may obtain a copy of
# the License at: http://opensource.org/licenses/MIT

import time

class StatsBuilder:
    def __init__(self):
        self.compares_ = 0
        self.swaps_ = 0
        self.calls_ = 0
        self.iterations_ = 0
        self.recursionDepth_ = 0
        self.currentRecursionDepth_ = 0
        self.startTime_ = time.time()

    def compare(self):
        self.compares_ = self.compares_ + 1

    def swap(self):
        self.swaps_ = self.swaps_ + 1

    def call(self):
        self.calls_ = self.calls_ + 1

    def iterate(self):
        self.iterations_ = self.iterations_ + 1

    def enter(self):
        self.currentRecursionDepth_ = self.currentRecursionDepth_ + 1
        if self.currentRecursionDepth_ > self.recursionDepth_:
            self.recursionDepth_ = self.currentRecursionDepth_

    def leave(self):
        self.currentRecursionDepth_ = self.currentRecursionDepth_ - 1

    def elapsed(self):
        return time.time() - self.startTime_

    def __str__(self):
        return "{{compares: {}, swaps: {}, calls: {}, iterations: {}, recursion: {}, elapsed: {}}}".format(
                self.compares_, self.swaps_, self.calls_, self.iterations_, self.recursionDepth_,
                self.elapsed())

class HeapSort:
    @staticmethod
    def heapify(a, n, i, stats):
        largest = i
        l = 2 * i + 1
        r = 2 * i + 2

        stats.enter()
        
        if l < n:
            stats.compare()
            if a[l] > a[largest]:
                largest = l

        if r < n:
            stats.compare()
            if a[r] > a[largest]:
                largest = r;

        if largest != i:
            stats.swap()
            a[i], a[largest] = a[largest], a[i]
            heapify(a, n, largest, stats)

        stats.leave()

    @staticmethod
    def sort(a):
        stats = StatsBuilder()

        # short-circuit trivial inputs
        if len(a) < 2:
            return stats

        # build heap by rearranging array
        i = n / 2 - 1
        while i >= 0:
            stats.iterate()
            heapify(a, n, i, stats)
            i = i - 1

        # one-by-one, extract an element from the heap
        i = n - 1
        while i >= 0:
            stats.iterate()

            # move current root to the end
            stats.swap()
            a[0], a[i] = a[i], a[0]

            # call max heapify on the reduced heap
            heapify(a, i, 0, stats)

            i = i - 1

        return stats

class QuickSort:
    @staticmethod
    def sort(a):
        "TODO"

# as per home-assignment
def sort_A(a):
    return QuickSort.sort(a)

# as per home-assignment
def sort_B(a):
    return HeapSort.sort(a)

if __name__ == "__main__":
    print("Hello, World; TODO: test me")

    x = StatsBuilder()
    print("stats: {}".format(x))
