// Описать класс А так, чтобы:

// все конструкции функции main были верными
// явно в классе А было описано не более одного конструктора
// на экран выдалось 15 60 7

#include <iostream>
class A {
private:
    int value;
public:
    A (int n = 7) {value = n;}
    A operator*=(int n) {
        value *= n;
        return *this;
    }
    A operator*=(const A& other) {
        value *= other.get();
        return *this;
    }
    int get() const {return value;}
};
int main() {
    A a1(5), a2 = 4, a3;
    a2 *= a1 *= 3;
    std::cout << a1.get() << ' ' << a2.get() << ' ' << a3.get() << std::endl;
    return 0;
}
