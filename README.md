*******************************
**Building and running tests:**
*******************************
```
cmake .                        # generate build files
cmake --build .                # build sources
cmake --build . --target test  # run tests
```

For implementation class hierarchy, please open `README.html`.


************
**Language**
************

In this document we define what is considered to be a valid program for our language and what is the expected
behaviour for a valid program.

This language is a simple programming language composed of expressions.
The input consists of a file that contains one expression or no expressions at all.

The first stage of our application will convert the text input to an AST (Abstract Syntax Tree), which is an alternative
representation of the program.
This conversion is done in 2 steps: lexing and parsing.
The Lexer converts the text input to a list of tokens.
The Parser will use these tokens to create the AST.

We can think of tokens as the "words" of our language, while the AST contains "sentences" that are grammatically correct.

*********
**Lexer**
*********

In this section we define what the tokens of our language are.
If an input text can't be decomposed in the tokens described here, the input is not considered valid.

Tokens are the words of our language and they can be described using regular expressions.

Valid tokens for our language are:
```
"if"        - keyword
"else"      - keyword
"then"      - keyword
"print"     - keyword
"undefined" - keyword
ID          - [A-Za-z]+ A string with at least one character. Only upper-case and lower-case letters are permitted.
NUMBER      - [0-9]+ A string with at least one character. All characters must be digits.
END         - special token that marks the end-of-file.
"*"
"+"
"-"
"/"
"("
")"
";"
"="
"{"
"}"
"**"
```

Keywords have priority over identifier names, so we can't have an identifier called "if", "else", "then", "print" or "undefined".

All whitespace characters are ignored by the Lexer and are not represented as tokens.

**********
**Parser**
**********

The parser groups some of the tokens into the AST structure.

In this section we defined the grammar for our language, for reference purposes.
This grammar is in a simplified form (i.e. it's not directly usable by the compiler).
Our compiler uses a right-recursive grammar, implemented using a recursive descendent parser.

```
program: expression?;

expression: NUMBER
          | ID
          | "undefined"
          | "(" expression ")"
          | assignmentExpression
          | binaryExpression
          | conditionalExpression
          | printExpression
          | unaryExpression
          | block
          ;

assignmentExpression : ID "=" expression;

printExpression : "print" expression;

binaryExpression : expression "**" expression
                 | expression "*" expression
                 | expression "/" expression
                 | expression "+" expression
                 | expression "-" expression
                 ;

unaryExpression : "-" expression
                | "+" expression
                ;

conditionalExpression : "if" expression "then" expression ("else" expression);

block : "{" ((expression ";")* expression)? "}";
```

The priority list for the binary operations is, highest to lowest priority:
```
0: **
1: *, /
2: +, -
```

**************
**Expression**
**************

Expressions supported by this language can be grouped in 3 categories: basic expressions, composite expressions and blocks.

Basic expressions correspond to a Lexer token.
There are 3 types of basic expressions that we can use in this language:

Number: an integer value.
While numbers can be negative in our language, in the AST there are only non-negative numbers.
When we parse "-5" we don't obtain the number "-5", we obtain an unary expression with type "minus" and the number "5" as a
sub-expression.
Example of numbers: 0, 3, 5, 42

Identifier: the name of a variable.
Using identifiers we can save values for use at a future date.
Reading the value corresponding to an identifier that has not been assigned will result in the undefined value.
Example of identifiers: i, sum, etc

Undefined: keyword for the undefined value.
This is a special keyword in our language in order to prevent assigning values to a variable called "undefined".
The following code will result in a syntax error:
```
undefined = 1
```

Composite expressions contain sub-expressions.
The types of expressions are: UnaryExpression, BinaryExpression, ConditionalExpression, PrintExpression and Assignment.


UnaryExpression: either "-" or "+" performed on a single subexpression.
Parsing "-5" will result in a UnaryExpression with 5 as its subexpression.

BinaryExpression: these are arithmetic operations: `+, -, *, ** and /`

Binary expressions contain 2 subexpressions.

ConditionalExpression: these are the if-s of our language.

A Block is a list of expression, that evaluate to the last expression.
If a Block is empty, it evaluates to undefined.

*******************
**Lazy evaluation**
*******************

From the AST point of view, blocks are "values".
A Value is something that can be assigned to an Identifier.
When we assign a Block to an Identifier, we do not execute that Block, we save the Block for later usage.

Besides from Value, we also have the notion of "constants".
A Constant is either a Number or the Undefined Value.
A Constant is always a value, but a Value may not be a Constant.
Some expressions only work with Constant and will convert the value to a Constant (i.e. they will execute the Block).
These expressions are the UnaryExpression, the BinaryExpression and the PrintExpression.

*************************
**Recommended resources**
*************************

- [CMake](https://cmake.org/download/)
- [Visual Studio Community](https://visualstudio.microsoft.com/vs/)

Alternative to Visual Studio:
- [Clang](http://releases.llvm.org/download.html)
- [Ninja](https://github.com/ninja-build/ninja/releases)
