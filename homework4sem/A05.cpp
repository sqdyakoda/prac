#include <iostream>
class OptInt {
private:
    int value;
    bool flag;
public:
    OptInt() {flag = false;}
    OptInt(int num) {
        this->value = num;
        flag = true;
    }
    OptInt& operator=(const OptInt& other) {
        this->value = other.get();
        this->flag = true;
        return *this;
    }
    bool isSet() const {return flag;}
    int get() const {return value;}
    
};
OptInt operator+(const OptInt& object1, const OptInt& object2) {
    if (!(object1.isSet() && object2.isSet()))
        return OptInt();
    return OptInt(object1.get() + object2.get());
}
std::ostream &operator<<(std::ostream &out, const OptInt &o) {
    if (!o.isSet()) {
        out << "undefined";
        return out;
    }
    out << o.get();
    return out;
}

// int main() {
//   OptInt i;
//   std::cout << i << std::endl;
//   i = 5;
//   if (i.isSet()) {
//     std::cout << i << std::endl;
//   }
//   OptInt j = i, k;
//   std::cout << i + j + k << std::endl;
//   j = k = i + 1;
//   std::cout << i + k << std::endl;
//   std::cout << j << std::endl;

//   return 0;
// }