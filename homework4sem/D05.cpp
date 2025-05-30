#include <algorithm>
#include <vector>
#include <iostream>

// bool isChet(int x) {
//     return x % 2 == 0;
// }
template<typename T>
void input(T& v) {
    typename T::value_type x;
    while (std::cin >> x)
        v.push_back(x);
}
template<typename T, typename Function>
void filter(T& container, Function predicate) {
    typename T::iterator it = container.begin();
    while (it != container.end()) {
        if (!predicate(*it))
            it = container.erase(it);
        else
            ++it;
    }
}
template<typename Iterator>
void output(Iterator first, Iterator last) {
    for (auto it = first; it != last; ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}
// int main() {
//     std::vector<int> v;
//     input(v);
//     filter(v, isChet);
//     output(v.begin(), v.end());
// }