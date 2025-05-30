#include <iostream>
#include <string>
#include <algorithm>

namespace std_string_hex_sum {
    constexpr int base = 16;
    int hextodec(char ch) {
        if (ch < 58) return int(ch - 48);
        else return int(ch - 55);
    }
    char dectohex(int n) {
        if (n < 10) return char(n + 48);
        else return char(n + 55);
    }
    std::string sum(const std::string& a, const std::string& b) {
        int digit1, digit2;
        std::string res;
        int len1 = a.size() - 1;
        int len2 = b.size() - 1;
        int p = 0;
        while (len1 >= 0 || len2 >= 0 || p > 0) {
            digit1 = len1 >= 0 ? hextodec(a[len1--]) : 0;
            digit2 = len2 >= 0 ? hextodec(b[len2--]) : 0;
            res += dectohex((digit1 + digit2 + p) % base);
            p = (digit1 + digit2 + p) / base;
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
}

int main() {
    std::string n1, n2;
    std::cin >> n1 >> n2;
    std::cout << std_string_hex_sum::sum(n1, n2);
}
//'0' = 48
//'A' = 65