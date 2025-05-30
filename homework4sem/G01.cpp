#include <iostream>
#include <string>
#include <sstream>

class DKA {
public:
bool accept(const std::string& in) {
	enum State {Q0, Q1, Q2, Q3, ERROR};
	std::istringstream input(in);
	char c;
	State state = Q0;
	while (state != ERROR && input >> c) {
		switch (state) {
			case Q0:
				if (c == '1') state = Q1;
				else if (c == '0') state = Q2;
				else state = ERROR;
				break;
			case Q1:
				if (c == '1') state = Q0;
				else if (c == '0') state = Q3;
				else state = ERROR;
				break;
			case Q2:
				if (c == '1') state = Q3;
				else if (c == '0') state = Q0;
				else state = ERROR;
				break;
			case Q3:
				if (c == '1') state = Q2;
				else if (c == '0') state = Q1;
				else state = ERROR;
				break;
			default:
				state = ERROR;
		}
	}
	return state == Q0;
}
};
