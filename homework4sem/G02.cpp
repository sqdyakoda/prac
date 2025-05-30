#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
class DKA {
public:
enum State {S, A, B, C, D, E, ERROR};
bool accept(const std::string& in) {
	std::istringstream input(in);
	char c;
	State state = S;
	while (state != ERROR && input >> c) {
		switch (state) {
			case S:
                if (std::isalpha(c)) state = A;
                else if (std::isdigit(c) && (c != '0')) state = B;
                else if (c == '0') state = C;
                else state = ERROR;
				break;
            case A:
                if (std::isalnum(c) || (c == '_')) state = A;
                else state = ERROR;
                break;
            case B:
                if (std::isdigit(c)) state = B;
                else if (c == '.') state = D;
                else state = ERROR;
                break;
            case C:
                if (c == '.') state = D;
                else state = ERROR;
                break;
            case D:
                if (isdigit(c)) state = E;
                else state = ERROR;
                break;
            case E:
                if (isdigit(c)) state = E;
                else state = ERROR;
                break;
			default:
				state = ERROR;
		}
	}
	return ((state == A) || (state == B) || (state == C) || (state == E));
}
};

// int main() {
//     DKA g;

//     std::string str;
//     while (std::cin >> str) {
//         if (g.accept(str))
//             std::cout << "OK: ";
//         else
//             std::cout << "ERROR: ";
//         std::cout << str << std::endl;
//     }
// }