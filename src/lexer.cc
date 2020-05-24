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

#include "lexer.h"

#include <cctype>
#include <iostream>

namespace micro1 {

std::vector< Token >
tokenize(std::ifstream& ifs) {
    std::vector< Token > tokens;

    std::string line;
    for (uint64_t row = 1; std::getline(ifs, line); row++) {
        for (uint64_t pos = 0; pos < line.length(); pos++) {
            // if line[pos] is whitespace, it's ignored.
            if (std::isspace(line[pos])) {
                continue;
            }
            
            // if line[pos] is comment, it's skipped.
            if (line[pos] == ';') {
                break;
            }

            switch (line[pos]) {
                case '(':
                    tokens.emplace_back(Token(TokenKind::LPAREN, line, 1, row, pos));
                    break;
                case ')':
                    tokens.emplace_back(Token(TokenKind::RPAREN, line, 1, row, pos));
                    break;
                case '*':
                    tokens.emplace_back(Token(TokenKind::STAR,   line, 1, row, pos));
                    break;
                case '+': [[fallthrough]];
                case '-':
                    tokens.emplace_back(Token(TokenKind::SIGN,   line, 1, row, pos));
                    break;
                case ',':
                    tokens.emplace_back(Token(TokenKind::COMMA,  line, 1, row, pos));
                    break;
                case ':':
                    tokens.emplace_back(Token(TokenKind::COLON,  line, 1, row, pos));
                    break;
                case '\'':
                    if (pos + 2 < line.length())
                        tokens.emplace_back(Token(TokenKind::CHARS, line, 3, row, pos));
                    else
                        tokens.emplace_back(Token(TokenKind::INVALID, line, 1, row, pos));
                    break;
                case '"':
                    tokens.emplace_back(Token(TokenKind::DQUOTE, line, 1, row, pos));
                    break;
                default: {
                    auto start = pos;
                    if (std::isdigit(line[pos])) {
                        while (++pos < line.length()) {
                            if (!(std::isxdigit(line[pos])))
                                break;
                        }
                        tokens.emplace_back(Token(TokenKind::INTEGER, line, pos - start, row,  start));
                        pos--;
                    } else if (std::isalpha(line[pos])) {
                        while (++pos < line.length()) {
                            if (!std::isalnum(line[pos]))
                                break;
                        }
                        tokens.emplace_back(Token(TokenKind::STRING,  line, pos - start, row,  start));
                        pos--;
                    } else {
                        tokens.emplace_back(Token(TokenKind::INVALID, line, 1, row, pos));
                    }

                    break;
                }
            }
        }

        tokens.emplace_back(Token(TokenKind::EOL, line, 1, row, line.length()));
    }

    return tokens;
}

}