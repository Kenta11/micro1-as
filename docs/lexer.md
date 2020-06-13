# lexical analyzer

Related files: include/micro1-as/lexer.h, include/micro1-as/token.h, src/lexer.cc

## Overview

Lexical analyzer generates tokens from input source code. Tokens are parsed by [syntatic analyzer](parser.md).

## Token

### Kind

| kind    | BNF                         |
|:-------:|:----------------------------|
| STRING  | \[A-Za-z\]\[A-Za-z0-9\]     |
| INTEGER | \[0-9\]\[A-Fa-f0-9\]        |
| LPAREN  | (                           |
| RPAREN  | )                           |
| STAR    | *                           |
| CHARS   | '{a printable character}{2} |
| DQUOTE  | "                           |
| SIGN    | +|-                         |
| COMMA   | ,                           |
| COLON   | :                           |
| EOL     | End of line                 |
| INVALID | others                      |

### Structure

| member    | description                      |
|:---------:|:---------------------------------|
| m\_kind   | token kind                       |
| m\_size   | number of characters             |
| m\_row    | row number which token exists    |
| m\_column | column number which token exists |
