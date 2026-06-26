# C++ Tokenizer

A simple tokenizer/lexer written in C++ as part of my compiler design learning journey.

This project breaks source code into tokens like keywords, identifiers, numbers, operators, parentheses, and semicolons.

## What is a Tokenizer?

A tokenizer, also called a lexer, is the first stage of a compiler.

It takes raw source code like this:

```txt
manlo x = 10;
chapo x;
```

And converts it into meaningful tokens like this:

```txt
KEYWORD_LET    : manlo
IDENTIFIER     : x
EQUAL          : =
NUMBER         : 10
SEMICOLON      : ;
KEYWORD_PRINT  : chapo
IDENTIFIER     : x
SEMICOLON      : ;
END
```

## Features

* Recognizes keywords
* Recognizes identifiers
* Recognizes numbers
* Recognizes operators
* Recognizes parentheses
* Recognizes semicolons
* Ignores whitespace
* Stores tokens using a `vector`
* Uses `enum class` for token types

## Supported Tokens

| Token Type      | Example                |
| --------------- | ---------------------- |
| `KEYWORD_LET`   | `manlo`                |
| `KEYWORD_PRINT` | `chapo`                |
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

## Example Input

```txt
manlo x = 10;
manlo y = 20;
chapo x + y;
```

## Example Output

```txt
KEYWORD_LET    : manlo
IDENTIFIER     : x
EQUAL          : =
NUMBER         : 10
SEMICOLON      : ;
KEYWORD_LET    : manlo
IDENTIFIER     : y
EQUAL          : =
NUMBER         : 20
SEMICOLON      : ;
KEYWORD_PRINT  : chapo
IDENTIFIER     : x
PLUS           : +
IDENTIFIER     : y
SEMICOLON      : ;
END
```

## Concepts Used

* C++ classes
* `enum class`
* Structs
* Vectors
* Strings
* Character checking with `isalpha`, `isdigit`, and `isalnum`
* Basic lexical analysis
* Compiler design fundamentals

## How to Run

Compile the program:

```bash
g++ tokenizer.cpp -o tokenizer
```

Run it:

```bash
./tokenizer
```

On Windows:

```bash
g++ tokenizer.cpp -o tokenizer.exe
tokenizer.exe
```

## Project Structure

```txt
cpp-tokenizer/
│
├── tokenizer.cpp
├── README.md
└── .gitignore
```

## Why I Built This

I built this project to understand how programming languages are processed internally.

This is the first step in building a mini compiler/interpreter from scratch.

The next stage after this tokenizer is building a parser.

## Future Improvements

* Add better error handling
* Add string literal support
* Add comments support
* Add line and column tracking
* Build a parser
* Build an AST
* Create a simple interpreter

## Author

Built by Angan as part of a compiler design learning journey.
