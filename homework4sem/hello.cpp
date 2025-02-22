#include <iostream>
class A {
private:
    int num;
public:
    A() {
        num = 0;
        std::cout << 1 << std::endl;
    }
    A(const A & obj) {
        this->num = obj.num;
        std::cout << 2 << std::endl;
    }
    A(double num) {
        this->num = int(num);
        std::cout << 3 << std::endl;
    }
    A(float num1, unsigned short num2) {
        this->num = int(num1 + num2);
        std::cout << 4 << std::endl;
    }
    void m() {
        A();
        {
            A a2(3);
            A a3(a2);
        }
        A a4;
        A a5(0.1, 1);
    }
    ~A() {
        std::cout << 5 << std::endl;
    }
};
//1 5 3 2 5 5 2 4 5 5
int main() {
    A obj = A(3);
    // std::cout << "start" << std::endl;
    // obj.m();
    // std::cout << "end" << std::endl;
    
}