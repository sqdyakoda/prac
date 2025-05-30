#include <iostream>
#include <algorithm>
#include <vector>
int main() {
    std::string str;
    std::vector<std::string> vec;
    while (std::cin >> str)
        vec.push_back(str);
    std::sort(vec.begin(), vec.end());
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    for (auto it = vec.rbegin(); it != vec.rend(); ++it)
        std::cout << *it << " ";

}