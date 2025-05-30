// Опишите абстрактный тип данных OptInt для хранения произвольных значений типа int.
// По умолчанию значение типа int считается не установленным. Установить значение можно только явно в момент инициализации
// или после при помощи операции присваивания. Класс OptInt должен хранить дополнительную информацию о том, установлено значение или нет.

// В реализации конструкторов рекомендуется использовать список инициализации. Также можно использовать инициализацию при
// описании полей класса для указания значений по умолчанию. Необходимо перегрузить операции << и +, чтобы они работали для
// объектов класса OptInt. Если значение не установлено, на экран следует напечатать undefined. Если хотя бы для одного из аргументов
// операции + значение int не установлено, то результат операции + также считается undefined.

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