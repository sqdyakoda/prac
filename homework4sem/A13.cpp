#include <iostream>
#include <sstream>
class OptInt {
	int* value;
	bool flag;
public:
	//constructors
	OptInt() : value(nullptr), flag(false) {}
	OptInt(const OptInt& other);
	OptInt(int x);
	~OptInt() {
		if (!flag)
			delete[] value;	
	}
	//operators
	int operator*() const;
	OptInt& operator+=(const OptInt& other);
	OptInt& operator++();
	OptInt operator++(int);
	//methods
	void check() const;
	bool present() const {return flag;}
};

OptInt::OptInt(const OptInt& other) {
	if (other.present()) {
		value = new int;
		*value = *other;
		flag = true;
	} else {
		flag = false;
		value = nullptr;
	}
}
OptInt::OptInt(int x) {
	flag = true;
	value = new int;
	*value = x;
}
int OptInt::operator*() const {
	check();
	return *value;	
}
OptInt& OptInt::operator+=(const OptInt& other) {
	check();
	*value = *value + *other;
	return *this;
}
OptInt& OptInt::operator++() {
	check();
	*value = *value + 1;
	return *this;
}
OptInt OptInt::operator++(int) {
	check();
	OptInt temp = *this;
	*value = *value + 1;
	return temp;
}
void OptInt::check() const {
	if (!flag) {
		std::cout << "undefined" << std::endl;
		exit(0);
	}
}
OptInt operator+(const OptInt& x, const OptInt& y) {
	if (!(x.present() && y.present())) {
		std::cout << "undefined" << std::endl;
		exit(0);
	}
	return OptInt(*x + *y);
}
std::ostream& operator<<(std::ostream& out, const OptInt& o) {
	if (!(o.present())) {
		std::cout << "undefined" << std::endl;
		exit(0);
	}
	out << *o;
	return out;
}
/*
int main()
{
    OptInt p1(4);
    std::cout << p1 << std::endl; // 4
    OptInt const &pp = p1;
    std::cout << pp << std::endl; // 4

    std::ostringstream s; s << "p1 == " << p1;
    std::cout << s.str() << std::endl; // p1 == 4

    std::cout << ++p1 << " " << p1 << std::endl; // 5 5
    std::cout << p1++ << " " << p1 << std::endl; // 5 6
    std::cout << *++p1 << std::endl; // 7
}
*/