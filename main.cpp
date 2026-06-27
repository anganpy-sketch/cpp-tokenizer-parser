#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
using namespace std;

enum class TokenType
{
    IDENTIFIER,
    KEYWORD_LET,
    KEYWORD_PRINT,
    RPAREN,
    LPAREN,
    PLUS,
    MINUS,
    EQUAL,
    STAR,
    SLASH,
    SEMICOLON,
    NUMBER,
    END,
    UNKNOWN
};

struct Token
{
    TokenType type;
    string value;
};

string TokenTypeToString(TokenType type)
{
    switch (type)
    {
    case TokenType::IDENTIFIER:
        return "IDENTIFIER";
    case TokenType::KEYWORD_LET:
        return "KEYWORD_LET";
    case TokenType::KEYWORD_PRINT:
        return "KEYWORD_PRINT";
    case TokenType::RPAREN:
        return "RPAREN";
    case TokenType::LPAREN:
        return "LPAREN";
    case TokenType::PLUS:
        return "PLUS";
    case TokenType::MINUS:
        return "MINUS";
    case TokenType::EQUAL:
        return "EQUAL";
    case TokenType::STAR:
        return "STAR";
    case TokenType::SLASH:
        return "SLASH";
    case TokenType::SEMICOLON:
        return "SEMICOLON";
    case TokenType::NUMBER:
        return "NUMBER";
    case TokenType::END:
        return "END";
    };
    return "UNKNOWN";
};

class Lexer
{
private:
    string source;
    int pos;
    vector<Token> tokens;

    bool isAtEnd()
    {
        return pos >= source.length();
    }

    char peek()
    {
        if (isAtEnd())
        {
            return '\0';
        }
        return source[pos];
    }

    char advance()
    {
        char current = source[pos];
        pos++;
        return current;
    }

    void addToken(TokenType type, string value)
    {
        tokens.push_back({type, value});
    }

    void readWord()
    {
        string word = "";
        while (!isAtEnd() && isalpha(peek()))
        {
            word += advance();
        }
        if (word == "manlo")
        {
            addToken(TokenType::KEYWORD_LET, word);
        }
        else if (word == "chapo")
        {
            addToken(TokenType::KEYWORD_PRINT, word);
        }
        else
        {
            addToken(TokenType::IDENTIFIER, word);
        }
    }

    void readNumber()
    {
        string num = "";
        while (!isAtEnd() && isdigit(peek()))
        {
            num += advance();
        }
        addToken(TokenType::NUMBER, num);
    }

    void readSymbol()
    {
        char curr = advance();
        if (curr == '+')
        {
            addToken(TokenType::PLUS, "+");
        }
        else if (curr == '-')
        {
            addToken(TokenType::MINUS, "-");
        }
        else if (curr == '*')
        {
            addToken(TokenType::STAR, "*");
        }
        else if (curr == '/')
        {
            addToken(TokenType::SLASH, "/");
        }
        else if (curr == ';')
        {
            addToken(TokenType::SEMICOLON, ";");
        }
        else if (curr == '(')
        {
            addToken(TokenType::LPAREN, "(");
        }
        else if (curr == ')')
        {
            addToken(TokenType::RPAREN, ")");
        }
        else if (curr == '=')
        {
            addToken(TokenType::EQUAL, "=");
        }
        else
        {
            addToken(TokenType::UNKNOWN, string(1, curr));
        }
    }

public:
    Lexer(string input)
    {
        pos = 0;
        source = input;
    }

    vector<Token> Tokenizer()
    {
        while (!isAtEnd())
        {
            char current = peek();
            if (isspace(current))
            {
                advance();
                continue;
            }
            else if (isalpha(current))
            {
                readWord();
            }
            else if (isdigit(current))
            {
                readNumber();
            }
            else
            {
                readSymbol();
            }
        }
        addToken(TokenType::END, "");
        return tokens;
    }
};

class Parser
{
private:
    vector<Token> tokens;
    int pos;

    bool isAtEnd()
    {
        return peek().type == TokenType::END;
    }

    Token peek()
    {
        return tokens[pos];
    }

    Token previous()
    {
        return tokens[pos - 1];
    }

    Token advance()
    {
        if (!isAtEnd())
        {
            pos++;
        }
        return previous();
    }

    bool check(TokenType type)
    {
        if (isAtEnd())
        {
            return false;
        }
        return peek().type == type;
    }

    bool match(TokenType type)
    {
        if (check(type))
        {
            advance();
            return true;
        }
        return false;
    }

    Token consume(TokenType type, string errorMessage)
    {
        if (check(type))
        {
            return advance();
        }

        throw runtime_error(errorMessage);
    }

    void parseStatement()
    {
        if (match(TokenType::KEYWORD_LET))
        {
            parseLetStatement();
        }
        else if (match(TokenType::KEYWORD_PRINT))
        {
            parsePrintStatement();
        }
        else if (check(TokenType::IDENTIFIER) && pos + 1 < tokens.size() && tokens[pos + 1].type == TokenType::EQUAL)
        {
            parseAssignmentStatement();
        }
        else
        {
            throw runtime_error("Expected a statement: 'manlo', 'chapo', or an assignment");
        }
    }

    void parseAssignmentStatement()
    {
        Token name = consume(TokenType::IDENTIFIER, "Expected variable name in assignment");

        consume(TokenType::EQUAL, "Expected '=' after variable name");

        parseExpression();

        consume(TokenType::SEMICOLON, "Expected ';' after assignment statement");

        cout << "Parsed ASSIGNMENT statement for variable: " << name.value << endl;
    }

    void parseLetStatement()
    {
        Token name = consume(TokenType::IDENTIFIER, "Expected variable name after 'manlo'");

        consume(TokenType::EQUAL, "Expected '=' after variable name");

        parseExpression();

        consume(TokenType::SEMICOLON, "Expected ';' after let statement");

        cout << "Parsed LET statement for variable: " << name.value << endl;
    }

    void parsePrintStatement()
    {
        parseExpression();

        consume(TokenType::SEMICOLON, "Expected ';' after print statement");

        cout << "Parsed PRINT statement" << endl;
    }

    void parseExpression()
    {
        parseTerm();

        while (match(TokenType::PLUS) || match(TokenType::MINUS))
        {
            Token op = previous();
            parseTerm();

            cout << "Parsed expression operator: " << op.value << endl;
        }
    }

    void parseTerm()
    {
        parseFactor();

        while (match(TokenType::STAR) || match(TokenType::SLASH))
        {
            Token op = previous();
            parseFactor();

            cout << "Parsed term operator: " << op.value << endl;
        }
    }

    void parseFactor()
    {
        if (match(TokenType::NUMBER))
        {
            cout << "Parsed number: " << previous().value << endl;
            return;
        }

        if (match(TokenType::IDENTIFIER))
        {
            cout << "Parsed identifier: " << previous().value << endl;
            return;
        }

        if (match(TokenType::LPAREN))
        {
            parseExpression();
            consume(TokenType::RPAREN, "Expected ')' after expression");
            return;
        }

        throw runtime_error("Expected number, identifier, or '('");
    }

public:
    Parser(vector<Token> inputTokens)
    {
        tokens = inputTokens;
        pos = 0;
    }

    void parse()
    {
        while (!isAtEnd())
        {
            parseStatement();
        }

        cout << "Parsing completed successfully!" << endl;
    }
};
int main()
{
    string input;
    cout << "Enter the Line:";
    getline(cin, input);

    Lexer lexer(input);
    vector<Token> tokens = lexer.Tokenizer();

    cout << "\nTOKENS:\n";
    for (Token token : tokens)
    {
        cout << TokenTypeToString(token.type) << "=>" << token.value << endl;
    }

    cout << "\nPARSER:\n";

    try
    {
        Parser parser(tokens);
        parser.parse();
    }
    catch (runtime_error &error)
    {
        cout << "Parser Error: " << error.what() << endl;
    }
}
