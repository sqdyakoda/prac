#include <iostream>
class DynArray {
    int* array;
    int size;
    int capacity;
public: 
    DynArray() : array(nullptr), size(0), capacity(0) {}
    DynArray(DynArray& other);
    int& operator[] (int i);
    const int& operator[] (int i) const;
    int length() const {return size;}
    ~DynArray() {delete[] array;}
};
DynArray::DynArray(DynArray& other) {
    this->size = other.size;
    this->capacity = other.capacity;
    array = new int[other.capacity];
    for (int j = 0; j < capacity; ++j)
        array[j] = other[j];
}
int& DynArray::operator[] (int i) {
    if (i >= capacity) {
        capacity = 8;
        while(i >= capacity)
            capacity *= 2;
        int* temp = new int[capacity];
        for (int j = 0; j < size; ++j)
            temp[j] = array[j];
        for (int j = size; j < capacity; ++j)
            temp[j] = 0;
        if (array != nullptr)
            delete[] array;
        array = temp;
        size = i + 1;
    } else if (i >= size) {
        size = i + 1;
    }
    return array[i];
}
const int& DynArray::operator[] (int i) const {
    if (i >= size) {
        std::cout << "Out of bounds\n";
        exit(0);
    }
    return array[i];
}
std::ostream& operator<<(std::ostream& out, const DynArray& other) {
    if (other.length() == 0)
        return out;
    out << other[0];
    for (int j = 1; j < other.length(); ++j)
        std::cout << " " << other[j];
    return out;
}
// int main()
// {
//     DynArray a;

//     int n, i = 0;
//     while(std::cin >> n) {
//         a[i++] = n;
//     }

//     std::cout << a.length() << std::endl;

//     const DynArray b(a);
//     std::cout << b << std::endl;
    // std::cout << b[4] << std::endl;

    // DynArray c;
    // c[200] = 200;
    // std::cout << c[3] << ' ' << c[199] << ' ' << c[200] << std::endl;

    // DynArray d = c;
    // std::cout << d.length() << std::endl;

    // DynArray a1;
    // a1[0] = 0; a1[1] = 1; a1[2] = 2;
    // std::cout << a1 << std::endl;
// }