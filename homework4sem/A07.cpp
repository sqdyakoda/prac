#include <cstring>
#include <iostream>
#include <utility>
class UniqueCharPtr {
private:
    char* data;
public:
    UniqueCharPtr() : data(nullptr) {}
    UniqueCharPtr(char* str) : data(str) {str = nullptr;}
    UniqueCharPtr(UniqueCharPtr&) = delete;
    UniqueCharPtr(UniqueCharPtr&& other) {
        data = other.data;
        other.data = nullptr;
    }
    UniqueCharPtr& operator=(UniqueCharPtr&) = delete;
    UniqueCharPtr& operator=(UniqueCharPtr&& other) {
        if (this != &other) {
            delete[] data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
    operator char*() {return data;}
    ~UniqueCharPtr() {delete[] data;}
};
// int main() {
//     UniqueCharPtr p1 = new char[15];
//     strcpy(p1, "Smart pointers");

//     // UniqueCharPtr p2 = p1; // Not allowed!
//     UniqueCharPtr p2 = std::move(p1);
//     std::cout << p2 << std::endl;
//     std::cout << *p2 << *(p2+1) << std::endl;

//     UniqueCharPtr p3;
//     // p3 = "Smart pointers"; // Not allowed!
//     // p3 = p2; // Not allowed!
//     p3 = new char[15];
//     p3 = new char[20];
//     strcpy(p3, p2);
//     std::cout << p3 << std::endl;

//     UniqueCharPtr p4;
// }
