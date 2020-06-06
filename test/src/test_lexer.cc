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
 * @file test_lexer.cc
 * @brief Test for lexer.cc
 * @author Kenta Arai
 * @date 2020/05/30
 */

#include "micro1-as/lexer.h"

#include <gtest/gtest.h>

namespace {

    TEST(tokenizeTest, STRING) {
        std::ifstream ifs("test/input/input_for_lexer_STRING.txt");
        ASSERT_FALSE(ifs.fail());

        micro1::Tokens expected = {
            micro1::Token(micro1::TokenKind::STRING,  "  ABC       D012    EFGhij     ", 3, 1,  2),
            micro1::Token(micro1::TokenKind::STRING,  "  ABC       D012    EFGhij     ", 4, 1, 12),
            micro1::Token(micro1::TokenKind::STRING,  "  ABC       D012    EFGhij     ", 6, 1, 20),
            micro1::Token(micro1::TokenKind::EOL,     "  ABC       D012    EFGhij     ", 1, 1, 31),
            micro1::Token(micro1::TokenKind::STRING,  "  V   WU3 P2NM",                  1, 2,  2),
            micro1::Token(micro1::TokenKind::STRING,  "  V   WU3 P2NM",                  3, 2,  6),
            micro1::Token(micro1::TokenKind::STRING,  "  V   WU3 P2NM",                  4, 2, 10),
            micro1::Token(micro1::TokenKind::EOL,     "  V   WU3 P2NM",                  1, 2, 14),
            micro1::Token(micro1::TokenKind::STRING,  " EGG  SYSTEM FT",                 3, 3,  1),
            micro1::Token(micro1::TokenKind::STRING,  " EGG  SYSTEM FT",                 6, 3,  6),
            micro1::Token(micro1::TokenKind::STRING,  " EGG  SYSTEM FT",                 2, 3, 13),
            micro1::Token(micro1::TokenKind::EOL,     " EGG  SYSTEM FT",                 1, 3, 15)
        };
        auto result = micro1::tokenize(ifs);

        ASSERT_EQ(expected, result);
    }

    TEST(tokenizeTest, INTEGER) {
        std::ifstream ifs("test/input/input_for_lexer_INTEGER.txt");
        ASSERT_FALSE(ifs.fail());

        micro1::Tokens expected = {
            micro1::Token(micro1::TokenKind::INTEGER, "1234 5678 90AB",   4, 1,  0),
            micro1::Token(micro1::TokenKind::INTEGER, "1234 5678 90AB",   4, 1,  5),
            micro1::Token(micro1::TokenKind::INTEGER, "1234 5678 90AB",   4, 1, 10),
            micro1::Token(micro1::TokenKind::EOL,     "1234 5678 90AB",   1, 1, 14),
            micro1::Token(micro1::TokenKind::INTEGER, "  0010101 101011", 7, 2,  2),
            micro1::Token(micro1::TokenKind::INTEGER, "  0010101 101011", 6, 2, 10),
            micro1::Token(micro1::TokenKind::EOL,     "  0010101 101011", 1, 2, 16),
            micro1::Token(micro1::TokenKind::INTEGER, " 6AB1 8EB3 0D12",  4, 3,  1),
            micro1::Token(micro1::TokenKind::INTEGER, " 6AB1 8EB3 0D12",  4, 3,  6),
            micro1::Token(micro1::TokenKind::INTEGER, " 6AB1 8EB3 0D12",  4, 3, 11),
            micro1::Token(micro1::TokenKind::EOL,     " 6AB1 8EB3 0D12",  1, 3, 15)
        };
        auto result = micro1::tokenize(ifs);

        ASSERT_EQ(expected, result);
    }


    TEST(tokenizeTest, LPAREN) {
        std::ifstream ifs("test/input/input_for_lexer_LPAREN.txt");
        ASSERT_FALSE(ifs.fail());

        micro1::Tokens expected = {
            micro1::Token(micro1::TokenKind::LPAREN, "    (   ( ", 1, 1,  4),
            micro1::Token(micro1::TokenKind::LPAREN, "    (   ( ", 1, 1,  8),
            micro1::Token(micro1::TokenKind::EOL,    "    (   ( ", 1, 1, 10),
            micro1::Token(micro1::TokenKind::LPAREN, "( ( ",       1, 2,  0),
            micro1::Token(micro1::TokenKind::LPAREN, "( ( ",       1, 2,  2),
            micro1::Token(micro1::TokenKind::EOL,    "( ( ",       1, 2,  4),
            micro1::Token(micro1::TokenKind::LPAREN, "  (",        1, 3,  2),
            micro1::Token(micro1::TokenKind::EOL,    "  (",        1, 3,  3)
        };
        auto result = micro1::tokenize(ifs);

        ASSERT_EQ(expected, result);
    }

    TEST(tokenizeTest, RPAREN) {
        std::ifstream ifs("test/input/input_for_lexer_RPAREN.txt");
        ASSERT_FALSE(ifs.fail());

        micro1::Tokens expected = {
            micro1::Token(micro1::TokenKind::RPAREN, ")   )  ) ) ", 1, 1,  0),
            micro1::Token(micro1::TokenKind::RPAREN, ")   )  ) ) ", 1, 1,  4),
            micro1::Token(micro1::TokenKind::RPAREN, ")   )  ) ) ", 1, 1,  7),
            micro1::Token(micro1::TokenKind::RPAREN, ")   )  ) ) ", 1, 1,  9),
            micro1::Token(micro1::TokenKind::EOL,    ")   )  ) ) ", 1, 1, 11),
            micro1::Token(micro1::TokenKind::RPAREN, "  )) ) )",    1, 2,  2),
            micro1::Token(micro1::TokenKind::RPAREN, "  )) ) )",    1, 2,  3),
            micro1::Token(micro1::TokenKind::RPAREN, "  )) ) )",    1, 2,  5),
            micro1::Token(micro1::TokenKind::RPAREN, "  )) ) )",    1, 2,  7),
            micro1::Token(micro1::TokenKind::EOL,    "  )) ) )",    1, 2,  8),
            micro1::Token(micro1::TokenKind::RPAREN, " )  )",       1, 3,  1),
            micro1::Token(micro1::TokenKind::RPAREN, " )  )",       1, 3,  4),
            micro1::Token(micro1::TokenKind::EOL,    " )  )",       1, 3,  5)
        };
        auto result = micro1::tokenize(ifs);

        ASSERT_EQ(expected, result);
    }

    TEST(tokenizeTest, STAR) {
        std::ifstream ifs("test/input/input_for_lexer_STAR.txt");
        ASSERT_FALSE(ifs.fail());

        micro1::Tokens expected = {
            micro1::Token(micro1::TokenKind::STAR, "*  *  ***", 1, 1,  0),
            micro1::Token(micro1::TokenKind::STAR, "*  *  ***", 1, 1,  3),
            micro1::Token(micro1::TokenKind::STAR, "*  *  ***", 1, 1,  6),
            micro1::Token(micro1::TokenKind::STAR, "*  *  ***", 1, 1,  7),
            micro1::Token(micro1::TokenKind::STAR, "*  *  ***", 1, 1,  8),
            micro1::Token(micro1::TokenKind::EOL,  "*  *  ***", 1, 1,  9),
            micro1::Token(micro1::TokenKind::STAR, "**  * * *", 1, 2,  0),
            micro1::Token(micro1::TokenKind::STAR, "**  * * *", 1, 2,  1),
            micro1::Token(micro1::TokenKind::STAR, "**  * * *", 1, 2,  4),
            micro1::Token(micro1::TokenKind::STAR, "**  * * *", 1, 2,  6),
            micro1::Token(micro1::TokenKind::STAR, "**  * * *", 1, 2,  8),
            micro1::Token(micro1::TokenKind::EOL,  "**  * * *", 1, 2,  9),
            micro1::Token(micro1::TokenKind::STAR, "** *  * ",  1, 3,  0),
            micro1::Token(micro1::TokenKind::STAR, "** *  * ",  1, 3,  1),
            micro1::Token(micro1::TokenKind::STAR, "** *  * ",  1, 3,  3),
            micro1::Token(micro1::TokenKind::STAR, "** *  * ",  1, 3,  6),
            micro1::Token(micro1::TokenKind::EOL,  "** *  * ",  1, 3,  8)
        };
        auto result = micro1::tokenize(ifs);

        ASSERT_EQ(expected, result);
    }

    TEST(tokenizeTest, CHARS) {
        std::ifstream ifs("test/input/input_for_lexer_CHARS.txt");
        ASSERT_FALSE(ifs.fail());

        micro1::Tokens expected = {
            micro1::Token(micro1::TokenKind::CHARS, "'AB  '1F   'F6",  3, 1,  0),
            micro1::Token(micro1::TokenKind::CHARS, "'AB  '1F   'F6",  3, 1,  5),
            micro1::Token(micro1::TokenKind::CHARS, "'AB  '1F   'F6",  3, 1, 11),
            micro1::Token(micro1::TokenKind::EOL,   "'AB  '1F   'F6",  1, 1, 14),
            micro1::Token(micro1::TokenKind::CHARS, "  ':  '_\\  ':;", 3, 2,  2),
            micro1::Token(micro1::TokenKind::CHARS, "  ':  '_\\  ':;", 3, 2,  6),
            micro1::Token(micro1::TokenKind::CHARS, "  ':  '_\\  ':;", 3, 2, 11),
            micro1::Token(micro1::TokenKind::EOL,   "  ':  '_\\  ':;", 1, 2, 14),
            micro1::Token(micro1::TokenKind::CHARS, " '%' '  '#\" ",   3, 3,  1),
            micro1::Token(micro1::TokenKind::CHARS, " '%' '  '#\" ",   3, 3,  5),
            micro1::Token(micro1::TokenKind::CHARS, " '%' '  '#\" ",   3, 3,  8),
            micro1::Token(micro1::TokenKind::EOL,   " '%' '  '#\" ",   1, 3, 12)
        };
        auto result = micro1::tokenize(ifs);

        ASSERT_EQ(expected, result);
    }

    TEST(tokenizeTest, DQUOTE) {
        std::ifstream ifs("test/input/input_for_lexer_DQUOTE.txt");
        ASSERT_FALSE(ifs.fail());

        micro1::Tokens expected = {
            micro1::Token(micro1::TokenKind::DQUOTE, "\"   \"  \"  ",  1, 1,  0),
            micro1::Token(micro1::TokenKind::DQUOTE, "\"   \"  \"  ",  1, 1,  4),
            micro1::Token(micro1::TokenKind::DQUOTE, "\"   \"  \"  ",  1, 1,  7),
            micro1::Token(micro1::TokenKind::EOL,    "\"   \"  \"  ",  1, 1, 10),
            micro1::Token(micro1::TokenKind::DQUOTE, "  \"\" \"",      1, 2,  2),
            micro1::Token(micro1::TokenKind::DQUOTE, "  \"\" \"",      1, 2,  3),
            micro1::Token(micro1::TokenKind::DQUOTE, "  \"\" \"",      1, 2,  5),
            micro1::Token(micro1::TokenKind::EOL,    "  \"\" \"",      1, 2,  6),
            micro1::Token(micro1::TokenKind::DQUOTE, " \"   \"    \"", 1, 3,  1),
            micro1::Token(micro1::TokenKind::DQUOTE, " \"   \"    \"", 1, 3,  5),
            micro1::Token(micro1::TokenKind::DQUOTE, " \"   \"    \"", 1, 3, 10),
            micro1::Token(micro1::TokenKind::EOL,    " \"   \"    \"", 1, 3, 11)
        };
        auto result = micro1::tokenize(ifs);

        ASSERT_EQ(expected, result);
    }

    TEST(tokenizeTest, SIGN) {
        std::ifstream ifs("test/input/input_for_lexer_SIGN.txt");
        ASSERT_FALSE(ifs.fail());

        micro1::Tokens expected = {
            micro1::Token(micro1::TokenKind::SIGN, "+  +     +",  1, 1,  0),
            micro1::Token(micro1::TokenKind::SIGN, "+  +     +",  1, 1,  3),
            micro1::Token(micro1::TokenKind::SIGN, "+  +     +",  1, 1,  9),
            micro1::Token(micro1::TokenKind::EOL,  "+  +     +",  1, 1, 10),
            micro1::Token(micro1::TokenKind::SIGN, "  --  -",     1, 2,  2),
            micro1::Token(micro1::TokenKind::SIGN, "  --  -",     1, 2,  3),
            micro1::Token(micro1::TokenKind::SIGN, "  --  -",     1, 2,  6),
            micro1::Token(micro1::TokenKind::EOL,  "  --  -",     1, 2,  7),
            micro1::Token(micro1::TokenKind::SIGN, "     -+  +-", 1, 3,  5),
            micro1::Token(micro1::TokenKind::SIGN, "     -+  +-", 1, 3,  6),
            micro1::Token(micro1::TokenKind::SIGN, "     -+  +-", 1, 3,  9),
            micro1::Token(micro1::TokenKind::SIGN, "     -+  +-", 1, 3, 10),
            micro1::Token(micro1::TokenKind::EOL,  "     -+  +-", 1, 3, 11)
        };
        auto result = micro1::tokenize(ifs);

        ASSERT_EQ(expected, result);
    }

    TEST(tokenizeTest, COMMA) {
        std::ifstream ifs("test/input/input_for_lexer_COMMA.txt");
        ASSERT_FALSE(ifs.fail());

        micro1::Tokens expected = {
            micro1::Token(micro1::TokenKind::COMMA, ",  , ,",    1, 1,  0),
            micro1::Token(micro1::TokenKind::COMMA, ",  , ,",    1, 1,  3),
            micro1::Token(micro1::TokenKind::COMMA, ",  , ,",    1, 1,  5),
            micro1::Token(micro1::TokenKind::EOL,   ",  , ,",    1, 1,  6),
            micro1::Token(micro1::TokenKind::COMMA, ",,  , ",    1, 2,  0),
            micro1::Token(micro1::TokenKind::COMMA, ",,  , ",    1, 2,  1),
            micro1::Token(micro1::TokenKind::COMMA, ",,  , ",    1, 2,  4),
            micro1::Token(micro1::TokenKind::EOL,   ",,  , ",    1, 2,  6),
            micro1::Token(micro1::TokenKind::COMMA, "  ,   ,,",  1, 3,  2),
            micro1::Token(micro1::TokenKind::COMMA, "  ,   ,,",  1, 3,  6),
            micro1::Token(micro1::TokenKind::COMMA, "  ,   ,,",  1, 3,  7),
            micro1::Token(micro1::TokenKind::EOL,   "  ,   ,,",  1, 3,  8)
        };
        auto result = micro1::tokenize(ifs);

        ASSERT_EQ(expected, result);
    }

    TEST(tokenizeTest, COLON) {
        std::ifstream ifs("test/input/input_for_lexer_COLON.txt");
        ASSERT_FALSE(ifs.fail());

        micro1::Tokens expected = {
            micro1::Token(micro1::TokenKind::COLON, ":   : :",          1, 1,  0),
            micro1::Token(micro1::TokenKind::COLON, ":   : :",          1, 1,  4),
            micro1::Token(micro1::TokenKind::COLON, ":   : :",          1, 1,  6),
            micro1::Token(micro1::TokenKind::EOL,   ":   : :",          1, 1,  7),
            micro1::Token(micro1::TokenKind::COLON, "  :    ::",        1, 2,  2),
            micro1::Token(micro1::TokenKind::COLON, "  :    ::",        1, 2,  7),
            micro1::Token(micro1::TokenKind::COLON, "  :    ::",        1, 2,  8),
            micro1::Token(micro1::TokenKind::EOL,   "  :    ::",        1, 2,  9),
            micro1::Token(micro1::TokenKind::COLON, " :     :   :    ", 1, 3,  1),
            micro1::Token(micro1::TokenKind::COLON, " :     :   :    ", 1, 3,  7),
            micro1::Token(micro1::TokenKind::COLON, " :     :   :    ", 1, 3, 11),
            micro1::Token(micro1::TokenKind::EOL,   " :     :   :    ", 1, 3, 16)
        };
        auto result = micro1::tokenize(ifs);

        ASSERT_EQ(expected, result);
    }

    TEST(tokenizeTest, INVALID) {
        std::ifstream ifs("test/input/input_for_lexer_INVALID.txt");
        ASSERT_FALSE(ifs.fail());

        micro1::Tokens expected = {
            micro1::Token(micro1::TokenKind::INVALID, "& $  ~", 1, 1,  0),
            micro1::Token(micro1::TokenKind::INVALID, "& $  ~", 1, 1,  2),
            micro1::Token(micro1::TokenKind::INVALID, "& $  ~", 1, 1,  5),
            micro1::Token(micro1::TokenKind::EOL,     "& $  ~", 1, 1,  6),
            micro1::Token(micro1::TokenKind::INVALID, "  ^^ !", 1, 2,  2),
            micro1::Token(micro1::TokenKind::INVALID, "  ^^ !", 1, 2,  3),
            micro1::Token(micro1::TokenKind::INVALID, "  ^^ !", 1, 2,  5),
            micro1::Token(micro1::TokenKind::EOL,     "  ^^ !", 1, 2,  6),
            micro1::Token(micro1::TokenKind::INVALID, " [ / ]", 1, 3,  1),
            micro1::Token(micro1::TokenKind::INVALID, " [ / ]", 1, 3,  3),
            micro1::Token(micro1::TokenKind::INVALID, " [ / ]", 1, 3,  5),
            micro1::Token(micro1::TokenKind::EOL,     " [ / ]", 1, 3,  6)
        };
        auto result = micro1::tokenize(ifs);

        ASSERT_EQ(expected, result);
    }

}
