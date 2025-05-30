#include <iostream>
class IntArray {
private:
    int* arrptr;
    int size;
public:
    IntArray(int num) {
        this->size = num;
        arrptr = new int[num];
    }
    IntArray(IntArray &other) {
        size = other.getSize();
        arrptr = new int[size];
        for (int i = 0; i < size; ++i)
            arrptr[i] = other[i];
    }
    ~IntArray() {delete [] arrptr;}
    const int& operator[] (int index) const {
        if ((index >= size) || (index < -size)) {
            std::cout << "Out of bounds\n" << std::endl;
            exit(0);
        }
        if (index < 0)
            return arrptr[size + index];
        return arrptr[index];

    }
    int& operator[] (int index) {
        if ((index >= size) || (index < -size)) {
            std::cout << "Out of bounds\n" << std::endl;
            exit(0);
        }
        if (index < 0)
            return arrptr[size + index];
        return arrptr[index];
    }
    int getSize() const {return size;}
};
std::ostream &operator<<(std::ostream &out, const IntArray &o) {
    out << o[0];
    for (int i = 1; i < o.getSize(); ++i)
        out << " " << o[i];
    return out;
}
// int main()
// {
//     int size;
//     std::cin >> size;
//     IntArray a(size);

//     int i = 0, n;
//     while(std::cin >> n) {
//         a[i++] = n;
//     }

//     std::cout << a << std::endl;

//     const IntArray b(a);
//     std::cout << b[-1] << ' ' << b[-2] << ' ' << b[-3] << std::endl;
//     std::cout << b[0] << ' ' << b[4] << std::endl;
// }
