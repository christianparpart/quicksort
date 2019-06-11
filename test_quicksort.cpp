// This file is part of the "quicksort" project, http://github.com/christianparpart/quicksort>
//   (c) 2019 Christian Parpart <christian@parpart.family>
//
// Licensed under the MIT License (the "License"); you may not use this
// file except in compliance with the License. You may obtain a copy of
// the License at: http://opensource.org/licenses/MIT

#include "quicksort.h"
#include <iostream>
#include <array>
#include <sstream>
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

template<typename T, size_t N> string to_string(array<T, N> const& a) { return to_string(begin(a), end(a)); }
template<typename T, size_t N> string to_string(const T (&a)[N]) { return to_string(begin(a), end(a)); }

int main(int argc, char const** argv)
{
	auto a = array{5, 4, 2, 7, 10, 1};
	auto const astats = quicksort::sort(a);
	cout << "a: " << to_string(a) << '\n';
	cout << "-> " << astats << '\n';

	int b[6] = {5, 4, 2, 7, 10, 1};
	auto const bstats = quicksort::sort(b);
	cout << "b: " << to_string(b) << '\n';
	cout << "-> " << bstats << '\n';

	return 0;
}
