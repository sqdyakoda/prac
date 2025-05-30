#include <iostream>
class A {
    static int x;
public:
    void f() {++x;}
    static int get() {return x;}
};
// int A::x = 0;
// int main() {
//     A a;
//     a.f();
//     a.f();
//     a.f();
//     std::cout << A::get() << std::endl; // 3
//     a.f();
//     std::cout << A::get() << std::endl; // 4
// }
