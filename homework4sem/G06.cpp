#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

enum Type {END, IDENT, INTEGER, FLOAT, OP, SEP, ERROR};
enum State {S, ident, int1, int2, dot, Float, op1, op2, sep, error};
class Token {
    Type kind;
    std::string value;
public:
    Token() {}
    Token(Type type, std::string str) : kind(type), value(str) {}
    int getKind() { return kind; }
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
                    else if (std::isalpha(c)) state = ident;
                    else if (std::isdigit(c) && (c != 0)) state = int1;
                    else if (c == '0') state = int2;
                    else if (c == '+') state = op1;
                    else if (c == '-') state = op2;
                    else if (c == '*' || c == '/' || c == '=') return Token(OP, str);
                    else if (c == '(' || c == ')' || c == ';') return Token(SEP, str);
                    else state = error;
                    break;
                case ident:
                    if (std::isalnum(c) || c == '_') state = ident;
                    else {
                        input.unget();
                        str.pop_back();
                        return Token(IDENT, str);
                    }
                    break;
                case int1:
                    if (std::isdigit(c)) state = int1;
                    else if (c == '.') state = dot;
                    else {
                        input.unget();
                        str.pop_back();
                        return Token(INTEGER, str);
                    }
                    break;
                case int2:
                    if (c == '.') state = dot;
                    else {
                        input.unget();
                        str.pop_back();
                        return Token(INTEGER, str);
                    }
                    break;
                case dot:
                    if (std::isdigit(c)) state = Float;
                    else state = error;
                    break;
                case Float:
                    if (std::isdigit(c)) state = Float;
                    else {
                        input.unget();
                        str.pop_back();
                        return Token(FLOAT, str);
                    }
                    break;
                case op1:
                    if (c == '+') return Token(OP, str);
                    else {
                        input.unget();
                        str.pop_back();
                        return Token(OP, str);
                    }
                    break;
                case op2:
                    if (c == '-') return Token(OP, str);
                    else {
                        input.unget();
                        str.pop_back();
                        return Token(OP, str);
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
    }
}
