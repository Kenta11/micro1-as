// Copyright (c) 2020 Kenta Arai
// 
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace micro1 {

enum class TokenKind {
    STRING,  // [A-Za-z][A-Za-z0-9]*
    INTEGER, // [0-9][A-Fa-f0-9]*
    LPAREN,  // (
    RPAREN,  // )
    STAR,    // *
    CHARS,   // '{a printable character}{2}
    DQUOTE,  // "
    SIGN,    // +|-
    COMMA,   // ,
    COLON,   // :
    EOL,     // End of line
    INVALID  // others
};

class Token {
public:
    Token(TokenKind kind, std::string line, std::size_t size, uint64_t row, uint64_t column) : m_kind(kind), m_line(line), m_size(size), m_row(row), m_column(column) {}

    TokenKind kind() const { return m_kind; }
    std::string line() const { return m_line; }
    uint64_t row() const { return m_row; }
    uint64_t column() const { return m_column; }
    std::string str() const { return m_line.substr(m_column, m_size); }
private:
    TokenKind m_kind;
    std::string m_line;
    std::size_t m_size;
    uint64_t m_row;
    uint64_t m_column;
};

}

#endif // TOKEN_H