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
template<typename T>
void f(T& v1, T& v2) {
    for (auto& elem : v1)
        if ((elem & 1) == 0)
            v2.push_back(elem);
}
template<typename Iterator>
void output(Iterator first, Iterator last) {
    for (auto it = first; it != last; ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

int main() {
    using T = std::vector<int>;
    T container1, container2;
    input(container1);
    f(container1, container2);
    output(container2.begin(), container2.end());
}