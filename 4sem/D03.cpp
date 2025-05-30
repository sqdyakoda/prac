#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

template<typename T>
void input(T& v) {
    typename T::value_type x;
    while (std::cin >> x)
        v.push_back(x);
}

template<typename Iterator>
void output(Iterator first, Iterator last) {
    for (auto it = first; it != last; ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

// int main() {
//     std::vector<std::string> v;
//     input(v);
//     std::sort(v.begin(), v.end());
//     output(v.begin(), v.end());
//     output(v.rbegin(), v.rend());
// }