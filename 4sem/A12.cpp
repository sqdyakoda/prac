#include <iostream>
class Logger {
Logger() {std::cout << "Logger is created\n";}
~Logger() {std::cout << "Logger is destroyed\n";}
public:
    Logger& log(int n) {
        std::cout << n;
        return *this;
    }
    Logger& log(const char* str) {
        std::cout << str;
        return *this;
    }
    Logger& log(char ch) {
        std::cout << ch;
        return *this;
    }
    static Logger& instance() {
        static Logger obj;
        return obj;
    }
};
class IntCharPair {
public:
    IntCharPair(int, char);
    friend Logger& log(Logger& logger, const IntCharPair& pair);
private:
    int n;
    char c;
};
IntCharPair::IntCharPair(int x, char y) {
    n = x;
    c = y;
}
Logger& log(Logger& logger, const IntCharPair& pair) {
    logger.log('(').log(pair.n).log(", ").log(pair.c).log(')');
    return logger;
}

// int main() {
//     IntCharPair pair(10, 'x');
//     log(Logger::instance(), pair).log('\n');
// }
