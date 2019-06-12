// This file is part of the "quicksort" project, http://github.com/christianparpart/quicksort>
//   (c) 2019 Christian Parpart <christian@parpart.family>
//
// Licensed under the MIT License (the "License"); you may not use this
// file except in compliance with the License. You may obtain a copy of
// the License at: http://opensource.org/licenses/MIT

#include "heapsort.h"
#include "quicksort.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>

using namespace std;

auto to_string(auto i, auto e) -> string
{
    if (i == e)
        return string{};

    stringstream sstr;
    sstr << *i;
    while (++i != e)
        sstr << ", " << *i;
    return sstr.str();
}

template <typename T>
string to_string(vector<T> const& a)
{
    return to_string(begin(a), end(a));
}

template <typename T, size_t N>
string to_string(const T (&a)[N])
{
    return to_string(begin(a), end(a));
}

template <typename Sorter>
void test_sort(const char* name, Sorter sorter)
{
    auto a = vector{5, 4, 2, 7, 10, 1};
    auto const astats = sorter(a);
    cout << name << ": " << to_string(a) << '\n';
    cout << " -> " << astats << '\n';
}

int main(int argc, char const** argv)
{
    test_sort("quicksort", sorting::quicksort::sort<vector<int>>);
    test_sort("heapsort", sorting::heapsort::sort<vector<int>>);

    return EXIT_SUCCESS;
}
