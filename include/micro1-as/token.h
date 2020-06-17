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

/**
 * @file token.h
 * @brief Token definition for lexical parser
 * @author Kenta Arai
 * @date 2020/05/24
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

namespace micro1 {

/**
 * @brief Token kind
 */
enum class TokenKind {
    STRING,   //! [A-Za-z][A-Za-z0-9]*
    INTEGER,  //! [0-9][A-Fa-f0-9]*
    LPAREN,   //! (
    RPAREN,   //! )
    STAR,     //! *
    CHARS,    //! '{a printable character}{2}
    DQUOTE,   //! "
    SIGN,     //! +|-
    COMMA,    //! ,
    COLON,    //! :
    EOL,      //! End of line
    INVALID   //! others
};

/**
 * @brief Class for token
 */
class Token {
public:
    /**
     * @brief Constructor for Token
     * @param[in] kind token kind
     * @param[in] line line where the token exists
     * @param[in] size size of string
     * @param[in] row row number
     * @param[in] column column number
     */
    Token(TokenKind kind, std::string line, size_t size, uint64_t row, uint64_t column) : m_kind(kind), m_line(line), m_size(size), m_row(row), m_column(column) {}

    /**
     * @brief Getter for m_kind
     * @return token kind
     */
    TokenKind kind() const { return m_kind; }
    /**
     * @brief Getter for m_line
     * @return line where the token exists
     */
    std::string line() const { return m_line; }
    /**
     * @brief Getter for m_row
     * @return row number
     */
    uint64_t row() const { return m_row; }
    /**
     * @brief Getter for m_column
     * @return column number
     */
    uint64_t column() const { return m_column; }
    /**
     * @brief Return string corresponding to the token
     * @return std::string a token string
     */
    std::string str() const { return m_line.substr(m_column, m_size); }
    /**
     * @brief Operator '==' for Token
     * @return Result of comparing two tokens
     */
    bool operator==(Token t) const {
        return m_kind == t.kind() &&
               m_line == t.line() &&
               m_row == t.row() &&
               m_column == t.column() &&
               str() == t.str();
    }
    /**
     * @brief Operator '!=' for Token
     * @return Result of comparing two tokens
     */
    bool operator!=(Token t) const {
        return m_kind != t.kind() ||
               m_line != t.line() ||
               m_row != t.row() ||
               m_column != t.column() ||
               str() != t.str();
    }

private:
    TokenKind m_kind;    //! token kind
    std::string m_line;  //! a line with token
    size_t m_size;       //! size of string
    uint64_t m_row;      //! row number
    uint64_t m_column;   //! column number
};

/**
 * @brief Vector for token
 */
typedef std::vector<Token> Tokens;

}  // namespace micro1

#endif  // TOKEN_H
