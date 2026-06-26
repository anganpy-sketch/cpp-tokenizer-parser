#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
using namespace std;

enum class TokenType{

NUMBER,
IDENTIFIER,
LET,
PRINT,
PLUS,
MINUS,
SLASH,
STAR,
LPAREN,
RPAREN,
END,
UNKNOWN,
SEMICOLON,
EQUAL
};

struct token {
TokenType type;
string value ;

};

string TokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::LET: return "KEYWORD_LET";
        case TokenType::PRINT: return "KEYWORD_PRINT";
        case TokenType::RPAREN: return "RPAREN";
        case TokenType::LPAREN: return "LPAREN";
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::STAR: return "STAR";
        case TokenType::SLASH: return "SLASH";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::END: return "END";
        case TokenType::UNKNOWN: return "UNKNOWN";
    };
    
};

class Lexer {
    private:
        string source;
        int pos;
        vector<token> tokens;

        bool isAtEnd() {
            return pos >= source.length();
        }

        char peek() {
            if (isAtEnd()) {
                return '\0';
            }
            return source[pos]; 
        }

        char advance() {
            char current = source[pos];
            pos++;
            return current; 
        }

        void addToken(TokenType type, string value) {
            tokens.push_back({type, value});
        }

        void readWord() {
            string word = "";
            while(!isAtEnd() && isalpha(peek())) { 
                word+=advance();
            }
            if (word == "manlo") {
                addToken(TokenType::LET, word);
            } else if (word == "chapo") {
                addToken(TokenType::PRINT, word);
            } else {
                addToken(TokenType::IDENTIFIER, word);
            }
        }

        void readNumber() {
            string num = "";
            while(!isAtEnd() && isdigit(peek())) { 
                num+=advance();
            }
            addToken(TokenType::NUMBER, num);
        }

        void readSymbol() {
            char curr = advance();
            if (curr == '+') {
                addToken(TokenType::PLUS, "+");
            } else if (curr == '-') {
                addToken(TokenType::MINUS, "-");
            } else if (curr == '*') {
                addToken(TokenType::STAR, "*");
            } else if (curr == '/') {
                addToken(TokenType::SLASH, "/");
            } else if (curr == ';') {
                addToken(TokenType::SEMICOLON, ";");
            } else if (curr == '(') {
                addToken(TokenType::LPAREN, "(");
            } else if (curr == ')') {
                addToken(TokenType::RPAREN, ")");
            } else if (curr == '=') {
                addToken(TokenType::EQUAL, "=");
            } else {
                addToken(TokenType::UNKNOWN, string(1, curr));
            }
        }


    public:
        Lexer (string input) {
            pos = 0; 
            source = input;
        }

        vector<token> Tokenizer() {
            while (!isAtEnd()) {
                char current = peek();
                if (isspace(current)) {
                    advance();
                    continue; 
                } else if (isalpha(current)) {
                    readWord();
                } else if (isdigit(current)) {
                    readNumber();
                } else {
                    readSymbol();
                } 
            }
            addToken(TokenType::END, ""); 
            return tokens;
        }
};
int main() {
    string input;
    cout << "Enter the Line:";
    getline(cin, input);

    Lexer lexer(input);
    vector<token> tokens = lexer.Tokenizer();

    cout << "\nTOKENS:\n";
    for (token token : tokens) {
        cout << TokenTypeToString(token.type) << "=>" << token.value << endl;
    }

    return 0;
}
