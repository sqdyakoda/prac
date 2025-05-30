#include <iostream>
#include <algorithm>
#include <vector>
int main() {
    int n;
    std::vector<int> vec;
    while (std::cin >> n)
        vec.push_back(n);
    std::sort(vec.begin(), vec.end());
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    for (auto it = vec.rbegin(); it != vec.rend(); ++it)
        std::cout << *it << " ";

}