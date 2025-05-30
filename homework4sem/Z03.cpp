#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

enum Type {END, INTEGER, BINARY, COMMA, L_BRACE, R_BRACE, ERROR};
enum State {S, A, B, C, D, error};

class Token {
    Type kind;
    std::string value;
public:
    Token() {}
    Token(Type type, std::string str) : kind(type), value(str) {}
    int getKind() { 
		if (kind == ERROR) {
			return 255;
		}
		return kind; 
	}
    std::string getValue() { return value; }
    operator bool() {
        if ((kind == END) || (kind == ERROR))
            return false;
        return true;
    }
};

class Scanner {
    std::istream &input = std::cin;
public:
    Token getToken() {
        State state = S;
        char c;
        std::string str;
        while (state != error && input.get(c)) {
            str += c;
            switch (state) {
				case S:
					if (std::isspace(c)) {
                        state = S;
                        str.pop_back();
                    }
                    else if (std::isdigit(c) && (c != '0')) state = A;
                    else if (c == '0') state = B;
                    else if (c == '{') return Token(L_BRACE, str);
                    else if (c == '}') return Token(R_BRACE, str);
                    else if (c == ',') return Token(COMMA, str);
                    else state = error;
					break;
				case A:
					if (std::isdigit(c)) state = A;
					else if (std::isalpha(c)) state = error;
					else {
                        input.unget();
                        str.pop_back();
                        return Token(INTEGER, str);
                    }
                    break;
                case B:
					if (c == 'b') state = C;
					else if (std::isdigit(c)) state = error;
					else {
                        input.unget();
                        str.pop_back();
                        return Token(INTEGER, str);
                    }
                    break;
                case C:
					if (c == '0' || c == '1') state = D;
					else state = error;
					break;
				case D:
					if (c == '0' || c == '1') state = D;
					else {
                        input.unget();
                        str.pop_back();
                        return Token(BINARY, str);
                    }
                    break;
                default:
                    state = error;
            }
        }
        if (state == S)
            return Token(END, str);
        return Token(ERROR, str);
    }
};

int main() {
    Scanner scanner;
    Token tk;

    while ((tk = scanner.getToken()).getKind() != END) {
        std::cout << tk.getKind() << " : " << tk.getValue() << std::endl;
        if (tk.getKind() == 255)
            break;
    }
}