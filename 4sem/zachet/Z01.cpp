#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

enum Type {END, ERROR, STRING, NUMBER, CONSTANTS, SEP};
enum State { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, error};
class Token {
    Type type;
    std::string value;
    int line, column;
public:
    Token() {}
    Token(Type kind, std::string str, int l, int c) : type(kind), value(str), line(l), column(c) {
        if (type == CONSTANTS) {
            if ((str != "true") && (str != "false") && (str != "null")) {
                std::cout << "(" << line << ", " << column << ") ERROR : " << str << std::endl;
                exit(0);
            }
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const Token& tk);
    int getKind() { return type; }
    std::string getValue() const { return value; }
    operator bool() {
        if ((type == END) || (type == ERROR))
            return false;
        return true;
    }
    bool operator==(int kind) const {
        return type == kind;
    }
    bool operator!=(int kind) const {
        return type != kind;
    }
};
std::ostream& operator<<(std::ostream& os, const Token& tk) {
	os << "(" << tk.line << ", " << tk.column << ") " << tk.getValue(); 

    return os;
}

class Scanner {
    std::istream &input = std::cin;
    int curcolumn = 0, line, column;
    int curline = 1;
public:
    Token getToken() {
        State state = S;
        char c;
        std::string str;
        while (state != error && input.get(c)) {
            str += c;
            
            if (c == '\n') {
				//std::cout << "new line" << std::endl; 
				curcolumn = 0; 
				curline++;
			} else {
				curcolumn++;
			}
			
            switch (state) {
                case S:
                    //space
                    if (std::isspace(c)) {
						
						
						
                        state = S;
                        str.pop_back();
                    } else {
						line = curline;
						column = curcolumn;
						
						//string
						if (c == '"') state = A;
						//number
						else if (c == '-')  state = E;
						else if (std::isdigit(c) && (c != '0')) state = F;
						else if (c == '0') state = I;
						//constants
						else if (std::isalpha(c)) state = L;
						//sep
						else if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == ':' || c == ',') return Token(SEP, str, line, column);
						else state = error;
					}
                    break;
                case A:
                    if (c == '\\') state = C;
                    else if (c == '"') return Token(STRING, str, line, column);
                    else state = B;
                    break;
                case B:
                    if (c == '"') return Token(STRING, str, line, column);
                    else if (c == '\\') state = D;
                    else state = A;
                    break;
                case C:
                    if (c == '"') state = A;
                    else state = error;
                    break;
                case D:
                    if (c == '"') state = B;
                    else state = error;
                    break;
                case E:
                    if (std::isdigit(c) && (c != '0')) state = F;
                    else if (c == '0') state = I;
                    else state = error;
                    break;
                case F:
                    if (std::isdigit(c)) state = F;
                    else if (c == '.') state = G;
                    else {
                        input.unget();
                        curcolumn--;
                        if (c == '\n') curline--;
						
                        str.pop_back();
                        return Token(NUMBER, str, line, column);
                    }
                    break;
                case G:
                    if (std::isdigit(c)) state = H;
                    else state = error;
                    break;
                case H:
                    if (std::isdigit(c)) state = H;
                    else {
                        input.unget();
                        curcolumn--;
                        if (c == '\n') curline--;
                        str.pop_back();
                        return Token(NUMBER, str, line, column);
                    }
                    break;
                case I:
                    if (c == '.') state = J;
                    else {
                        input.unget();
                        curcolumn--;
                        if (c == '\n') curline--;
                        str.pop_back();
                        return Token(NUMBER, str, line, column);
                    }
                    break;
                case J:
                    if (std::isdigit(c)) state = K;
                    else state = error;
                    break;
                case K:
                    if (std::isdigit(c)) state = K;
                    else {
                        input.unget();
                        curcolumn--;
                        if (c == '\n') curline--;
                        str.pop_back();
                        return Token(NUMBER, str, line, column);
                    }
                    break;
                case L:
                    if (std::isalnum(c) || (c == '_')) state = L;
                    else {
                        input.unget();
                        curcolumn--;
                        if (c == '\n') curline--;
                        str.pop_back();
                        return Token(CONSTANTS, str, line, column);
                    }
                    break;                
                default:
                    state = error;
            }
        }
        if (state == S)
            return Token(END, str, line, column);
        std::cout << "(" << line << ", " << column << ") ERROR : " << str << std::endl;
        exit(0);
    }
};


int main() {
    Scanner scanner;
    Token tk;

    while ((tk = scanner.getToken()) != END) {
        std::cout << tk << std::endl;
        if (tk == ERROR)
            break;
    }
}