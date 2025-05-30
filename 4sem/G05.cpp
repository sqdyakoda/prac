#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

enum Type {END, IDENT, NUMBER, ERROR};
enum State {S, A, B, C, D, E, ERR};
class Token {
    Type kind;
    std::string value;
public:
    Token() {}
    Token(Type type, std::string str) : kind(type), value(str) {}
    int getKind() {
        switch (kind) {
            case END:
                return 0;
            case IDENT:
                return 1;
            case NUMBER:
                return 2;
            case ERROR:
                return 255;
            default:
                return -1;
        }
    }
    operator bool() {
        if ((kind == END) || (kind == ERROR))
            return false;
        return true;
    }
    std::string getValue() {return value;}
};

class Scanner {
    std::istream &input = std::cin;
public:
    Token getToken() {
        char c;
        std::string str;
        State state = S;
        while ((input.get(c) || input.eof())) {
            if (input.eof() && str.empty())
                return Token(END, str);
            // std::cout << "current symb = '" << c << "'\n";
            switch (state) {
                case S:
                    if (std::isspace(c)) state = S;
                    else if (std::isalpha(c)) state = A;
                    else if (std::isdigit(c) && (c != '0')) state = B;
                    else if (c == '0') state = C;
                    // else if (input.eof()) {
                    //     return Token(END, str);
                    // }
                    else state = ERR;
                    break;
                case A:
                    if (std::isalnum(c) || (c == '_')) state = A;
                    else if (std::isspace(c) || input.eof()) {
                        input.unget();
                        return Token(IDENT, str);
                    }
                    else state = ERR;
                    break;
                case B:
                    if (std::isdigit(c)) state = B;
                    else if (c == '.') state = D;
                    else if (std::isspace(c) || input.eof()) {
                        input.unget();
                        return Token(NUMBER, str);
                    }
                    else state = ERR;
                    break;
                case C:
                    if (c == '.') state = D;
                    else if (std::isspace(c) || input.eof()) {
                        input.unget();
                        return Token(NUMBER, str);
                    }
                    else state = ERR;
                    break;
                case D:
                    if (isdigit(c)) state = E;
                    else state = ERR;
                    break;
                case E:
                    if (isdigit(c)) state = E;
                    else if (std::isspace(c) || input.eof()) {
                        input.unget();
                        return Token(NUMBER, str);
                    }
                    else state = ERR;
                    break;
                case ERR:
                    if (std::isspace(c) || input.eof()) {
                        input.unget();
                        return Token(ERROR, str);
                    }
                    else state = ERR;
                default:
                    state = ERR;
            }

            if (!std::isspace(c) && !input.eof())
                str.push_back(c);
        }
        return Token(END, str);
        
    }
};

int main() {
    Scanner scanner;
    Token tk;

    while ((tk = scanner.getToken())) {
        std::cout << tk.getKind() << " : " << tk.getValue() << std::endl;
    }
}