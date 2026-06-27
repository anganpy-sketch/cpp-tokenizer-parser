# C++ Mini Compiler Frontend

A simple **Tokenizer + Parser** written in C++ as part of my compiler design learning journey.

This project takes source code as input, breaks it into tokens using a **lexer/tokenizer**, and then checks the structure of the code using a **parser**.

## What This Project Does

This project currently has two major parts:

1. **Tokenizer / Lexer**

   * Converts raw source code into tokens.
   * Example: keywords, identifiers, numbers, operators, semicolons, parentheses.

2. **Parser**

   * Reads the tokens.
   * Checks whether the code follows the expected grammar.
   * Supports statements like variable declaration, print statement, and assignment.

## Example Input

```txt
let x = 10;
print x;
x = 20;
```

## Example Token Output

```txt
KEYWORD_LET    => let
IDENTIFIER     => x
EQUAL          => =
NUMBER         => 10
SEMICOLON      => ;
KEYWORD_PRINT  => print
IDENTIFIER     => x
SEMICOLON      => ;
IDENTIFIER     => x
EQUAL          => =
NUMBER         => 20
SEMICOLON      => ;
END            =>
```

## Parser Output

```txt
Parsing completed successfully!
```

If the code has invalid syntax, the parser throws an error.

Example invalid input:

```txt
let x = ;
```

Possible output:

```txt
Parser Error: Expected expression
```

## Features

### Tokenizer Features

* Recognizes keywords
* Recognizes identifiers
* Recognizes numbers
* Recognizes arithmetic operators
* Recognizes assignment operator
* Recognizes semicolons
* Recognizes parentheses
* Ignores whitespace
* Stores tokens using `vector<Token>`

### Parser Features

* Parses variable declaration statements
* Parses print statements
* Parses assignment statements
* Parses arithmetic expressions
* Detects syntax errors
* Uses recursive parsing style
* Throws readable parser errors using `runtime_error`

## Supported Tokens

| Token Type      | Example                |
| --------------- | ---------------------- |
| `KEYWORD_LET`   | `let`                  |
| `KEYWORD_PRINT` | `print`                |
| `IDENTIFIER`    | `x`, `name`, `total_1` |
| `NUMBER`        | `10`, `25`, `100`      |
| `PLUS`          | `+`                    |
| `MINUS`         | `-`                    |
| `STAR`          | `*`                    |
| `SLASH`         | `/`                    |
| `EQUAL`         | `=`                    |
| `SEMICOLON`     | `;`                    |
| `LPAREN`        | `(`                    |
| `RPAREN`        | `)`                    |
| `END`           | End of input           |

## Supported Syntax

### Variable Declaration

```txt
let x = 10;
```

### Print Statement

```txt
print x;
```

### Assignment Statement

```txt
x = 20;
```

### Arithmetic Expression

```txt
let result = 10 + 20 * 3;
```

## Basic Grammar

```txt
program        -> statement* END

statement      -> letStatement
                | printStatement
                | assignmentStatement

letStatement   -> "let" IDENTIFIER "=" expression ";"

printStatement -> "print" expression ";"

assignment     -> IDENTIFIER "=" expression ";"

expression     -> term ((PLUS | MINUS) term)*

term           -> factor ((STAR | SLASH) factor)*

factor         -> NUMBER
                | IDENTIFIER
                | "(" expression ")"
```

## Concepts Used

* C++ classes
* `enum class`
* Structs
* Vectors
* Strings
* Character checking using `isalpha`, `isdigit`, and `isalnum`
* Tokenization
* Parsing
* Recursive descent parsing
* Error handling using `runtime_error`
* Compiler design fundamentals

## Project Structure

```txt
cpp-tokenizer/
│
├── main.cpp
├── README.md
└── .gitignore
```

If your file name is different, replace `main.cpp` in the compile command with your actual file name.

## How to Run

Compile the program:

```bash
g++ main.cpp -o compiler
```

Run it:

```bash
./compiler
```

On Windows:

```bash
g++ main.cpp -o compiler.exe
compiler.exe
```

## Example Run

```txt
Enter the Line: let x = 10;

TOKENS:
KEYWORD_LET=>let
IDENTIFIER=>x
EQUAL=>=
NUMBER=>10
SEMICOLON=>;
END=>

PARSER:
Parsing completed successfully!
```

## Current Limitations

* Does not generate machine code
* Does not execute the code yet
* Does not build a full AST yet
* Limited syntax support
* Limited error messages
* No variable storage yet
* No interpreter yet

## Future Improvements

* Add better error messages with line and column numbers
* Add string literal support
* Add comments support
* Build an Abstract Syntax Tree
* Add an interpreter
* Store variables in a symbol table
* Add boolean expressions
* Add `if` statements
* Add loops
* Add functions
* Generate intermediate representation

## Why I Built This

I built this project to understand how programming languages work internally.

This project is my first step toward building a mini programming language from scratch.

The tokenizer handles the first stage: converting source code into tokens.

The parser handles the second stage: checking whether the tokens form valid syntax.

## Author

Built by Angan as part of a compiler design learning journey.
