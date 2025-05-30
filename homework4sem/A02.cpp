//Описать класс B таким образом, чтобы все конструкции функции main были верными, а на экран выдалось 10 20 30.

class B {
private:
    int value;
public:
    B () {value = 10;}
    B (const B & other) {this->value = other.value + 10;}
    int get() {return value;}
};
