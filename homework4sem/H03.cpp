#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

enum Type {END, ERROR, STRING, NUMBER, CONSTANTS, SEP};
enum State { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, error};
class Token {
    Type type;
    std::string value;
public:
    Token() {}
    Token(Type kind, std::string str) : type(kind), value(str) {
        if (type == CONSTANTS) {
            if ((str != "true") && (str != "false") && (str != "null")) {
                std::cout << "ERROR : " << str << std::endl;
                exit(0);
            }
        }
    }
    int getKind() const { return type; }
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
    os << tk.getValue();
    return os;
}
int max(int a, int b) {
	return (a > b) ? a : b;
}



class Scanner {
    std::istream &input;
public:
	Scanner(std::istream &in = std::cin) : input(in) {}
    Token getToken() {
        State state = S;
        char c;
        std::string str;
        while (state != error && input.get(c)) {
            str += c;
            switch (state) {
                case S:
                    //space
                    if (std::isspace(c)) {
                        state = S;
                        str.pop_back();
                    }
                    //string
                    else if (c == '"') state = A;
                    //number
                    else if (c == '-')  state = E;
                    else if (std::isdigit(c) && (c != '0')) state = F;
                    else if (c == '0') state = I;
                    //constants
                    else if (std::isalpha(c)) state = L;
                    //sep
                    else if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == ':' || c == ',') return Token(SEP, str);
                    else state = error;
                    break;
                case A:
                    if (c == '\\') state = C;
                    else if (c == '"') return Token(STRING, str);
                    else state = B;
                    break;
                case B:
                    if (c == '"') return Token(STRING, str);
                    else if (c == '\\') state = D;
                    else state = A;
                    break;
                case C:
                    if (c == '"' || c == '\\') state = A;
                    else state = error;
                    break;
                case D:
                    if (c == '"' || c == '\\') state = B;
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
                        str.pop_back();
                        return Token(NUMBER, str);
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
                        str.pop_back();
                        return Token(NUMBER, str);
                    }
                    break;
                case I:
                    if (c == '.') state = J;
                    else {
                        input.unget();
                        str.pop_back();
                        return Token(NUMBER, str);
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
                        str.pop_back();
                        return Token(NUMBER, str);
                    }
                    break;
                case L:
                    if (std::isalnum(c) || (c == '_')) state = L;
                    else {
                        input.unget();
                        str.pop_back();
                        return Token(CONSTANTS, str);
                    }
                    break;                
                default:
                    state = error;
            }
        }
        if (state == S)
            return Token(END, str);
        std::cout << "ERROR : " << str << std::endl;
        exit(0);
    }
};
class Parser {
    
    std::istringstream istr;
    Scanner scanner;
    Token tok;
    int depth = 0;
    int curdepth = 0;
    
    void gt() { tok = scanner.getToken(); }
public:
	int getDepth() {return depth;}
    Parser(const std::string& str) : istr(str), scanner(istr) { }
    Parser() { }
    bool parse() {
        try {
            gt();
            S();
            return (tok.getKind() == END);
        }
        catch (const Token& t) {
			std::cout << "ERROR : ";
			if (t.getKind() != END)
				std::cout << t.getValue();
			else
				std::cout << "EOF";
			return false;
		}
    }
    void S() {
        if (tok.getValue() == "{") {
			++curdepth;
			depth = max(depth, curdepth);
			gt();
			S2();
		}
		else if (tok.getValue() == "[") {
			++curdepth;
			depth = max(depth, curdepth);
			gt();
			A();
		}
		else throw tok;
    }
    void A() {
		if (tok.getValue() == "]") {
			--curdepth;
			gt();
		}
		else {
			
			V();
			if (tok.getValue() == "]") {--curdepth; gt();}
			else throw tok;
		}
	}
	void V() {
		Q();
		while (tok.getValue() == ",") {
			gt();
			Q();
		}
	}
	void Q() {
		if (tok.getKind() == CONSTANTS) gt();
		else if (tok.getKind() == NUMBER) gt();
		else if (tok.getKind() == STRING) gt();
		else S();
	}
	void S2() {
		if (tok.getValue() == "}") {--curdepth; gt();}
		else {
			P();
			if (tok.getValue() == "}") { --curdepth; gt();}
			else throw tok;
		}
	}
	void P() {
		T();
		while (tok.getValue() == ",") {
			gt();
			T();
		}
	}
	void T() {
		if (tok.getKind() == STRING) {
			gt();
			if (tok.getValue() == ":") {
				gt();
				Q();
			}
			else throw tok;
		}
		else throw tok;
	}
    
};

int main() {
    Parser parser;
    if (parser.parse()) {
        std::cout << "OK : depth = " << parser.getDepth() << std::endl;
    }
}