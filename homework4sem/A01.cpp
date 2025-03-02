#include <iostream>
class A {
private:
    int num;
public:
    A() {
        num = 0;
        std::cout << "1 ";
    }
    A(const A & obj) {
        this->num = obj.num;
        std::cout << "2 ";
    }
    A(double num1) {
        this->num = int(num1);
        std::cout << "3 ";
    }
    A(float num1, unsigned short num2) {
        this->num = int(num1 + num2);
        std::cout << "4 ";
    }
    void m() {
        A();
        {
            A a2(0);
            A a3(a2);
        }
        A a4(*this);
        A a5(0.1, 0);
    }
    ~A() {
        std::cout << "5 ";
    }
};