#include <iostream>
#include <string>
#include <utility>

using namespace std;

using T = string;

class SharedPtr {
private:
    T* ptr;
    int* count; 
public:
    SharedPtr();
    SharedPtr(T*);
    SharedPtr(const SharedPtr&);
    SharedPtr(SharedPtr&&);
    ~SharedPtr();
    SharedPtr& operator=(const SharedPtr&);
    SharedPtr& operator=(SharedPtr&&);
    T& operator*() const;
    bool operator==(const SharedPtr&) const;
    operator bool() const;
    void reset();
    void swap(SharedPtr&);
    T* get() const;
    int use_count() const;
};

SharedPtr::operator bool() const {
    return (ptr != nullptr);
}

bool SharedPtr::operator==(const SharedPtr& other) const {
    return (ptr == other.ptr);
}

T& SharedPtr::operator*() const {
    return *ptr;
}

int SharedPtr::use_count() const {
    if (count != nullptr)
        return *count;
    else 
        return 0;
}

T* SharedPtr::get() const{
    return ptr;
}

void SharedPtr::reset() {
    SharedPtr temp;
    SharedPtr::swap(temp);
}

void SharedPtr::swap(SharedPtr& other) {
    std::swap(ptr, other.ptr);
    std::swap(count, other.count);
}

SharedPtr& SharedPtr::operator=(SharedPtr&& other) {
    if (this != &other) {
        if (count) {
            --(*count);
            if (*count == 0) {
                delete ptr;
                delete count;
            }
        }
        ptr = other.ptr;
        count = other.count;
        other.ptr = nullptr;
        other.count = nullptr;
    }
    return *this;
}

SharedPtr::SharedPtr(SharedPtr&& other) {
    ptr = other.ptr;
    count = other.count;
    other.ptr = nullptr;
    other.count = nullptr;
}

SharedPtr& SharedPtr::operator=(const SharedPtr& other) {
    if (ptr != other.ptr) {
        if (count != nullptr) {
            --(*count);
            if (*count == 0) {
                delete ptr;
                delete count;
            }
        }
        count = other.count;
        ptr = other.ptr;
        if (count) 
            ++(*count);
    }
    return *this;
}

SharedPtr::SharedPtr(const SharedPtr& other) {
    count = other.count;
    ptr = other.ptr;
    if (count)
        ++(*count);
}

SharedPtr::SharedPtr(): ptr(nullptr), count(nullptr) { } // нет ни объекта, ни счётчика

SharedPtr::SharedPtr(T* val): ptr(val) {
    if (val) {
        count = new int(1);
    } else {
        count = nullptr;
    }
}

SharedPtr::~SharedPtr() {
    if (count != nullptr) {
        --(*count);
        if (*count == 0) {
            delete ptr;
            delete count;
        }
    }
}
// int main()
// {
//     const SharedPtr p1 = new std::string("Example");
//     SharedPtr p2;
//     SharedPtr p3 = nullptr;
//     std::cout << p1.use_count() << std::endl; // 1
//     std::cout << p2.use_count() << std::endl; // 0
//     std::cout << p3.use_count() << std::endl; // 0
//     if (p1) {
//         std::cout << *p1 << std::endl; // Example
//     }
//     if (p2 == p3) {
//         std::cout << "p2 == p3\n"; // p2 == p3
//     }
//     p2 = p3 = p1;
//     std::cout << p1.use_count() << std::endl; // 3
//     std::cout << p2.use_count() << std::endl; // 3
//     std::cout << p3.use_count() << std::endl; // 3
//     std::string* pStr = p3.get();
//     std::cout << *pStr << std::endl; // Example
//     if (p1.get() == p2.get()) {
//         std::cout << "p1 == p2\n"; // p1 == p2
//     }
//     p2 = std::move(p3);
//     std::cout << p1.use_count() << std::endl; // 2
//     std::cout << p2.use_count() << std::endl; // 2
//     std::cout << p3.use_count() << std::endl; // 0
//     if (p3 == nullptr) {
//         std::cout << "p3 is empty\n"; // p3 is empty
//     }
//     SharedPtr p4(std::move(p2));
//     std::cout << p1.use_count() << std::endl; // 2
//     if (!p2.get()) {
//         std::cout << "p2 is empty\n"; // p2 is empty
//     }
// }