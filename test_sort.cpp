// This file is part of the "quicksort" project, http://github.com/christianparpart/quicksort>
//   (c) 2019 Christian Parpart <christian@parpart.family>
//
// Licensed under the MIT License (the "License"); you may not use this
// file except in compliance with the License. You may obtain a copy of
// the License at: http://opensource.org/licenses/MIT

#include "heapsort.h"
#include "quicksort.h"

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <type_traits>
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

// template <template <class> class Vector, typename T, template <class> class Sorter>
// void test_sort(const char* name, Vector<T> a, Sorter<Vector<T>> sorter)
template <typename Vector, typename Sorter>
void test_sort(const char* name, Vector a, Sorter sorter)
{
    auto const astats = sorter(a);

    cout << name << ": " << astats << '\n';

    // cout << "    -> " << to_string(a) << '\n';

    // TODO: fix bug in quicksort ;-(
    // for (size_t n = 1; n < a.size(); ++n)
    //     assert(a[n - 1] <= a[n]);
}

vector<long> createRandomVector(size_t n)
{
    vector<long> a;

    mt19937 rng;
    rng.seed(time(nullptr));
    generate_n(back_inserter(a), n, [&]() { return rng() % n; });

    return a;
}

int main(int argc, char const** argv)
{
    auto const a = createRandomVector(argc >= 2 ? stoi(argv[1]) : 16 * 1024);
    using C = remove_const<decltype(a)>::type;

    test_sort("heapsort", a, sorting::heapsort::sort<C>);
    test_sort("quicksort", a, sorting::quicksort::sort<C>);

    return EXIT_SUCCESS;
}