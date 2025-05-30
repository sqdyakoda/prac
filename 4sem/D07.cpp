#include <list>
#include <set>
#include <string>
#include <vector>
#include <iostream>

template<typename T>
void inputN(T& container, typename T::size_type N) {
	typename T::value_type val;
	for (typename T::size_type i = 0; i < N; ++i) {
		std::cin >> val;
		container.insert(container.end(), val);
	}
}

template<typename Iterator>
void output(Iterator first, Iterator last) {
	for (auto it = first; it != last; ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}