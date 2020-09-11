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
 * @file test_parser.cc
 * @brief Test for parser.cc
 * @author Kenta Arai
 * @date 2020/05/30
 */

#include "micro1-as/parser.h"

#include "micro1-as/lexer.h"

#include <gtest/gtest.h>

namespace {

    TEST(parseTest, GROUP1) {
        std::ifstream ifs("test/unittest/input/input_for_parser_GROUP1.asm");
        ASSERT_FALSE(ifs.fail());

        micro1::Rows expected = {
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP1",           5,  1,  0),
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP1",          20,  1,  6)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    ADD  1, 37 (0)",                   3,  2,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    ADD  1, 37 (0)",                   1,  2,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "    ADD  1, 37 (0)",                   1,  2, 10),
                    micro1::Token(micro1::TokenKind::INTEGER, "    ADD  1, 37 (0)",                   2,  2, 12),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    ADD  1, 37 (0)",                   1,  2, 15),
                    micro1::Token(micro1::TokenKind::INTEGER, "    ADD  1, 37 (0)",                   1,  2, 16),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    ADD  1, 37 (0)",                   1,  2, 17)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                1,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    SUB  2, X\"B3DF (1)",              3,  3,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SUB  2, X\"B3DF (1)",              1,  3,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "    SUB  2, X\"B3DF (1)",              1,  3, 10),
                    micro1::Token(micro1::TokenKind::STRING,  "    SUB  2, X\"B3DF (1)",              1,  3, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    SUB  2, X\"B3DF (1)",              1,  3, 13),
                    micro1::Token(micro1::TokenKind::STRING,  "    SUB  2, X\"B3DF (1)",              4,  3, 14),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    SUB  2, X\"B3DF (1)",              1,  3, 19),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SUB  2, X\"B3DF (1)",              1,  3, 20),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    SUB  2, X\"B3DF (1)",              1,  3, 21)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                2,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    AND  3, O\"314232 (2)",            3,  4,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    AND  3, O\"314232 (2)",            1,  4,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "    AND  3, O\"314232 (2)",            1,  4, 10),
                    micro1::Token(micro1::TokenKind::STRING,  "    AND  3, O\"314232 (2)",            1,  4, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    AND  3, O\"314232 (2)",            1,  4, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    AND  3, O\"314232 (2)",            6,  4, 14),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    AND  3, O\"314232 (2)",            1,  4, 21),
                    micro1::Token(micro1::TokenKind::INTEGER, "    AND  3, O\"314232 (2)",            1,  4, 22),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    AND  3, O\"314232 (2)",            1,  4, 23)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                3,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    OR   0, B\"1010010110100101 (3)",  2,  5,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    OR   0, B\"1010010110100101 (3)",  1,  5,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "    OR   0, B\"1010010110100101 (3)",  1,  5, 10),
                    micro1::Token(micro1::TokenKind::STRING,  "    OR   0, B\"1010010110100101 (3)",  1,  5, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    OR   0, B\"1010010110100101 (3)",  1,  5, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    OR   0, B\"1010010110100101 (3)", 16,  5, 14),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    OR   0, B\"1010010110100101 (3)",  1,  5, 31),
                    micro1::Token(micro1::TokenKind::INTEGER, "    OR   0, B\"1010010110100101 (3)",  1,  5, 32),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    OR   0, B\"1010010110100101 (3)",  1,  5, 33)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                4,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    XOR  1, 43",                       3,  6,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    XOR  1, 43",                       1,  6,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "    XOR  1, 43",                       1,  6, 10),
                    micro1::Token(micro1::TokenKind::INTEGER, "    XOR  1, 43",                       2,  6, 12)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                5,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    MULT 2, X\"B2F2",                  4,  7,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    MULT 2, X\"B2F2",                  1,  7,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "    MULT 2, X\"B2F2",                  1,  7, 10),
                    micro1::Token(micro1::TokenKind::STRING,  "    MULT 2, X\"B2F2",                  1,  7, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    MULT 2, X\"B2F2",                  1,  7, 13),
                    micro1::Token(micro1::TokenKind::STRING,  "    MULT 2, X\"B2F2",                  4,  7, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                6,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    DIV  3, O\"172712",                3,  8,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    DIV  3, O\"172712",                1,  8,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "    DIV  3, O\"172712",                1,  8, 10),
                    micro1::Token(micro1::TokenKind::STRING,  "    DIV  3, O\"172712",                1,  8, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    DIV  3, O\"172712",                1,  8, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    DIV  3, O\"172712",                6,  8, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                7,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    CMP  0, B\"1011010011001101",      3,  9,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    CMP  0, B\"1011010011001101",      1,  9,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "    CMP  0, B\"1011010011001101",      1,  9, 10),
                    micro1::Token(micro1::TokenKind::STRING,  "    CMP  0, B\"1011010011001101",      1,  9, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    CMP  0, B\"1011010011001101",      1,  9, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    CMP  0, B\"1011010011001101",     16,  9, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                8,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    EX   1, (0)",                      2, 10,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    EX   1, (0)",                      1, 10,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "    EX   1, (0)",                      1, 10, 10),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    EX   1, (0)",                      1, 10, 12),
                    micro1::Token(micro1::TokenKind::INTEGER, "    EX   1, (0)",                      1, 10, 13),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    EX   1, (0)",                      1, 10, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                9,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "END",                                  3, 11,  0)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            )
        };
        auto result = micro1::parse(micro1::tokenize(ifs));

        ASSERT_EQ(expected, result);
    }

    TEST(parseTest, GROUP2) {
        std::ifstream ifs("test/unittest/input/input_for_parser_GROUP2.asm");
        ASSERT_FALSE(ifs.fail());

        micro1::Rows expected = {
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP2",       5,  1,  0),
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP2",      20,  1,  6)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    LC   0, 108",                  2,  2,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LC   0, 108",                  1,  2,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "    LC   0, 108",                  1,  2, 10),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LC   0, 108",                  3,  2, 12)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                1,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    PUSH 1, X\"E0B3",              4,  3,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    PUSH 1, X\"E0B3",              1,  3,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "    PUSH 1, X\"E0B3",              1,  3, 10),
                    micro1::Token(micro1::TokenKind::STRING,  "    PUSH 1, X\"E0B3",              1,  3, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    PUSH 1, X\"E0B3",              1,  3, 13),
                    micro1::Token(micro1::TokenKind::STRING,  "    PUSH 1, X\"E0B3",              4,  3, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                2,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    POP  2, O\"173210",            3,  4,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    POP  2, O\"173210",            1,  4,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "    POP  2, O\"173210",            1,  4, 10),
                    micro1::Token(micro1::TokenKind::STRING,  "    POP  2, O\"173210",            1,  4, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    POP  2, O\"173210",            1,  4, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    POP  2, O\"173210",            6,  4, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                3,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    LC   3, B\"1001010101101001",  2,  5,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LC   3, B\"1001010101101001",  1,  5,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "    LC   3, B\"1001010101101001",  1,  5, 10),
                    micro1::Token(micro1::TokenKind::STRING,  "    LC   3, B\"1001010101101001",  1,  5, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    LC   3, B\"1001010101101001",  1,  5, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LC   3, B\"1001010101101001", 16,  5, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                4,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "END",                              3,  6,  0)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            )
        };
        auto result = micro1::parse(micro1::tokenize(ifs));

        ASSERT_EQ(expected, result);
    }

    TEST(parseTest, GROUP3) {
        std::ifstream ifs("test/unittest/input/input_for_parser_GROUP3.asm");
        ASSERT_FALSE(ifs.fail());

        micro1::Rows expected = {
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP3",       5,  1,  0),
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP3",      20,  1,  6)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    SL  0, 4",                     2,  2,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SL  0, 4",                     1,  2,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    SL  0, 4",                     1,  2,  9),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SL  0, 4",                     1,  2, 11)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                1,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    SA  1, +34",                   2,  3,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SA  1, +34",                   1,  3,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    SA  1, +34",                   1,  3,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    SA  1, +34",                   1,  3, 11),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SA  1, +34",                   2,  3, 12)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                2,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    SC  2, -49",                   2,  4,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SC  2, -49",                   1,  4,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    SC  2, -49",                   1,  4,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    SC  2, -49",                   1,  4, 11),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SC  2, -49",                   2,  4, 12)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                3,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    BIX 3, X\"B24F",               3,  5,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    BIX 3, X\"B24F",               1,  5,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    BIX 3, X\"B24F",               1,  5,  9),
                    micro1::Token(micro1::TokenKind::STRING,  "    BIX 3, X\"B24F",               1,  5, 11),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    BIX 3, X\"B24F",               1,  5, 12),
                    micro1::Token(micro1::TokenKind::STRING,  "    BIX 3, X\"B24F",               4,  5, 13)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                4,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    SL  0, +X\"3BA",               2,  6,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SL  0, +X\"3BA",               1,  6,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    SL  0, +X\"3BA",               1,  6,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    SL  0, +X\"3BA",               1,  6, 11),
                    micro1::Token(micro1::TokenKind::STRING,  "    SL  0, +X\"3BA",               1,  6, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    SL  0, +X\"3BA",               1,  6, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SL  0, +X\"3BA",               3,  6, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                5,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    SA  1, -X\"23AA",              2,  7,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SA  1, -X\"23AA",              1,  7,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    SA  1, -X\"23AA",              1,  7,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    SA  1, -X\"23AA",              1,  7, 11),
                    micro1::Token(micro1::TokenKind::STRING,  "    SA  1, -X\"23AA",              1,  7, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    SA  1, -X\"23AA",              1,  7, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SA  1, -X\"23AA",              4,  7, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                6,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    SC  2, O\"36723",              2,  8,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SC  2, O\"36723",              1,  8,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    SC  2, O\"36723",              1,  8,  9),
                    micro1::Token(micro1::TokenKind::STRING,  "    SC  2, O\"36723",              1,  8, 11),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    SC  2, O\"36723",              1,  8, 12),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SC  2, O\"36723",              5,  8, 13)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                7,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    BIX 3, +O\"21734",             3,  9,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    BIX 3, +O\"21734",             1,  9,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    BIX 3, +O\"21734",             1,  9,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    BIX 3, +O\"21734",             1,  9, 11),
                    micro1::Token(micro1::TokenKind::STRING,  "    BIX 3, +O\"21734",             1,  9, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    BIX 3, +O\"21734",             1,  9, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    BIX 3, +O\"21734",             5,  9, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                8,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    SL  0, -O\"3234",              2, 10,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SL  0, -O\"3234",              1, 10,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    SL  0, -O\"3234",              1, 10,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    SL  0, -O\"3234",              1, 10, 11),
                    micro1::Token(micro1::TokenKind::STRING,  "    SL  0, -O\"3234",              1, 10, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    SL  0, -O\"3234",              1, 10, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SL  0, -O\"3234",              4, 10, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                9,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    SA  1, B\"1010100",            2, 11,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SA  1, B\"1010100",            1, 11,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    SA  1, B\"1010100",            1, 11,  9),
                    micro1::Token(micro1::TokenKind::STRING,  "    SA  1, B\"1010100",            1, 11, 11),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    SA  1, B\"1010100",            1, 11, 12),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SA  1, B\"1010100",            7, 11, 13)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                10,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    SC  2, +B\"101010110010110",   2, 12,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SC  2, +B\"101010110010110",   1, 12,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    SC  2, +B\"101010110010110",   1, 12,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    SC  2, +B\"101010110010110",   1, 12, 11),
                    micro1::Token(micro1::TokenKind::STRING,  "    SC  2, +B\"101010110010110",   1, 12, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    SC  2, +B\"101010110010110",   1, 12, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    SC  2, +B\"101010110010110",  15, 12, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                11,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    BIX 3, -B\"10101001001",       3, 13,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    BIX 3, -B\"10101001001",       1, 13,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    BIX 3, -B\"10101001001",       1, 13,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    BIX 3, -B\"10101001001",       1, 13, 11),
                    micro1::Token(micro1::TokenKind::STRING,  "    BIX 3, -B\"10101001001",       1, 13, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    BIX 3, -B\"10101001001",       1, 13, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    BIX 3, -B\"10101001001",      11, 13, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                12,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "END",                              3, 14,  0)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            )
        };
        auto result = micro1::parse(micro1::tokenize(ifs));

        ASSERT_EQ(expected, result);
    }

    TEST(parseTest, GROUP4) {
        std::ifstream ifs("test/unittest/input/input_for_parser_GROUP4.asm");
        ASSERT_FALSE(ifs.fail());

        micro1::Rows expected = {
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP4",       5,  1,  0),
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP4",      20,  1,  6)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    LEA 0,87 (3) ",                3,  2,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LEA 0,87 (3) ",                1,  2,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    LEA 0,87 (3) ",                1,  2,  9),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LEA 0,87 (3) ",                2,  2, 10),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    LEA 0,87 (3) ",                1,  2, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LEA 0,87 (3) ",                1,  2, 14),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    LEA 0,87 (3) ",                1,  2, 15)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                1,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    LX  1, +124 (0)",              2,  3,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LX  1, +124 (0)",              1,  3,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    LX  1, +124 (0)",              1,  3,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    LX  1, +124 (0)",              1,  3, 11),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LX  1, +124 (0)",              3,  3, 12),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    LX  1, +124 (0)",              1,  3, 16),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LX  1, +124 (0)",              1,  3, 17),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    LX  1, +124 (0)",              1,  3, 18)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                2,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    STX 2, -93 (1)",               3,  4,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    STX 2, -93 (1)",               1,  4,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    STX 2, -93 (1)",               1,  4,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    STX 2, -93 (1)",               1,  4, 11),
                    micro1::Token(micro1::TokenKind::INTEGER, "    STX 2, -93 (1)",               2,  4, 12),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    STX 2, -93 (1)",               1,  4, 15),
                    micro1::Token(micro1::TokenKind::INTEGER, "    STX 2, -93 (1)",               1,  4, 16),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    STX 2, -93 (1)",               1,  4, 17)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                3,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    LEA 3, X\"39 (2)",             3,  5,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LEA 3, X\"39 (2)",             1,  5,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    LEA 3, X\"39 (2)",             1,  5,  9),
                    micro1::Token(micro1::TokenKind::STRING,  "    LEA 3, X\"39 (2)",             1,  5, 11),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    LEA 3, X\"39 (2)",             1,  5, 12),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LEA 3, X\"39 (2)",             2,  5, 13),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    LEA 3, X\"39 (2)",             1,  5, 16),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LEA 3, X\"39 (2)",             1,  5, 17),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    LEA 3, X\"39 (2)",             1,  5, 18)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                4,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    LX  0, +X\"C23 (3)",           2,  6,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LX  0, +X\"C23 (3)",           1,  6,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    LX  0, +X\"C23 (3)",           1,  6,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    LX  0, +X\"C23 (3)",           1,  6, 11),
                    micro1::Token(micro1::TokenKind::STRING,  "    LX  0, +X\"C23 (3)",           1,  6, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    LX  0, +X\"C23 (3)",           1,  6, 13),
                    micro1::Token(micro1::TokenKind::STRING,  "    LX  0, +X\"C23 (3)",           3,  6, 14),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    LX  0, +X\"C23 (3)",           1,  6, 18),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LX  0, +X\"C23 (3)",           1,  6, 19),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    LX  0, +X\"C23 (3)",           1,  6, 20)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                5,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    STX 1, -X\"23D (0)",           3,  7,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    STX 1, -X\"23D (0)",           1,  7,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    STX 1, -X\"23D (0)",           1,  7,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    STX 1, -X\"23D (0)",           1,  7, 11),
                    micro1::Token(micro1::TokenKind::STRING,  "    STX 1, -X\"23D (0)",           1,  7, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    STX 1, -X\"23D (0)",           1,  7, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    STX 1, -X\"23D (0)",           3,  7, 14),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    STX 1, -X\"23D (0)",           1,  7, 18),
                    micro1::Token(micro1::TokenKind::INTEGER, "    STX 1, -X\"23D (0)",           1,  7, 19),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    STX 1, -X\"23D (0)",           1,  7, 20)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                6,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    LEA 2, O\"3723 (1)",           3,  8,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LEA 2, O\"3723 (1)",           1,  8,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    LEA 2, O\"3723 (1)",           1,  8,  9),
                    micro1::Token(micro1::TokenKind::STRING,  "    LEA 2, O\"3723 (1)",           1,  8, 11),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    LEA 2, O\"3723 (1)",           1,  8, 12),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LEA 2, O\"3723 (1)",           4,  8, 13),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    LEA 2, O\"3723 (1)",           1,  8, 18),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LEA 2, O\"3723 (1)",           1,  8, 19),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    LEA 2, O\"3723 (1)",           1,  8, 20)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                7,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    LX  3, +O\"3243 (2)",          2,  9,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LX  3, +O\"3243 (2)",          1,  9,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    LX  3, +O\"3243 (2)",          1,  9,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    LX  3, +O\"3243 (2)",          1,  9, 11),
                    micro1::Token(micro1::TokenKind::STRING,  "    LX  3, +O\"3243 (2)",          1,  9, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    LX  3, +O\"3243 (2)",          1,  9, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LX  3, +O\"3243 (2)",          4,  9, 14),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    LX  3, +O\"3243 (2)",          1,  9, 19),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LX  3, +O\"3243 (2)",          1,  9, 20),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    LX  3, +O\"3243 (2)",          1,  9, 21)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                8,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    STX 0, -O\"42 (3)",            3, 10,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    STX 0, -O\"42 (3)",            1, 10,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    STX 0, -O\"42 (3)",            1, 10,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    STX 0, -O\"42 (3)",            1, 10, 11),
                    micro1::Token(micro1::TokenKind::STRING,  "    STX 0, -O\"42 (3)",            1, 10, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    STX 0, -O\"42 (3)",            1, 10, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    STX 0, -O\"42 (3)",            2, 10, 14),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    STX 0, -O\"42 (3)",            1, 10, 17),
                    micro1::Token(micro1::TokenKind::INTEGER, "    STX 0, -O\"42 (3)",            1, 10, 18),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    STX 0, -O\"42 (3)",            1, 10, 19)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                9,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    LEA 1, B\"10101101 (0)",       3, 11,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LEA 1, B\"10101101 (0)",       1, 11,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    LEA 1, B\"10101101 (0)",       1, 11,  9),
                    micro1::Token(micro1::TokenKind::STRING,  "    LEA 1, B\"10101101 (0)",       1, 11, 11),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    LEA 1, B\"10101101 (0)",       1, 11, 12),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LEA 1, B\"10101101 (0)",       8, 11, 13),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    LEA 1, B\"10101101 (0)",       1, 11, 22),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LEA 1, B\"10101101 (0)",       1, 11, 23),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    LEA 1, B\"10101101 (0)",       1, 11, 24)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                10,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    LX  2, +B\"11010 (1)",         2, 12,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LX  2, +B\"11010 (1)",         1, 12,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    LX  2, +B\"11010 (1)",         1, 12,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    LX  2, +B\"11010 (1)",         1, 12, 11),
                    micro1::Token(micro1::TokenKind::STRING,  "    LX  2, +B\"11010 (1)",         1, 12, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    LX  2, +B\"11010 (1)",         1, 12, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LX  2, +B\"11010 (1)",         5, 12, 14),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    LX  2, +B\"11010 (1)",         1, 12, 20),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LX  2, +B\"11010 (1)",         1, 12, 21),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    LX  2, +B\"11010 (1)",         1, 12, 22)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                11,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    STX 3, -B\"10010111 (2)",      3, 13,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    STX 3, -B\"10010111 (2)",      1, 13,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    STX 3, -B\"10010111 (2)",      1, 13,  9),
                    micro1::Token(micro1::TokenKind::SIGN,    "    STX 3, -B\"10010111 (2)",      1, 13, 11),
                    micro1::Token(micro1::TokenKind::STRING,  "    STX 3, -B\"10010111 (2)",      1, 13, 12),
                    micro1::Token(micro1::TokenKind::DQUOTE,  "    STX 3, -B\"10010111 (2)",      1, 13, 13),
                    micro1::Token(micro1::TokenKind::INTEGER, "    STX 3, -B\"10010111 (2)",      8, 13, 14),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    STX 3, -B\"10010111 (2)",      1, 13, 23),
                    micro1::Token(micro1::TokenKind::INTEGER, "    STX 3, -B\"10010111 (2)",      1, 13, 24),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    STX 3, -B\"10010111 (2)",      1, 13, 25)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                12,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    LEA 0, (3)",                   3, 14,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LEA 0, (3)",                   1, 14,  8),
                    micro1::Token(micro1::TokenKind::COMMA,   "    LEA 0, (3)",                   1, 14,  9),
                    micro1::Token(micro1::TokenKind::LPAREN,  "    LEA 0, (3)",                   1, 14, 11),
                    micro1::Token(micro1::TokenKind::INTEGER, "    LEA 0, (3)",                   1, 14, 12),
                    micro1::Token(micro1::TokenKind::RPAREN,  "    LEA 0, (3)",                   1, 14, 13)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                13,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "END",                              3, 15,  0)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            )
        };
        auto result = micro1::parse(micro1::tokenize(ifs));

        ASSERT_EQ(expected, result);
    }

    TEST(parseTest, GROUP5) {
        std::ifstream ifs("test/unittest/input/input_for_parser_GROUP5.asm");
        ASSERT_FALSE(ifs.fail());

        micro1::Rows expected = {
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP5",       5,  1,  0),
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP5",      20,  1,  6)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "      L  0, *",                    1,  2,  6),
                    micro1::Token(micro1::TokenKind::INTEGER, "      L  0, *",                    1,  2,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "      L  0, *",                    1,  2, 10),
                    micro1::Token(micro1::TokenKind::STAR,    "      L  0, *",                    1,  2, 12)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "*", 0 }
            ),
            micro1::Row(
                "",
                1,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "      ST 1, * + 8",                2,  3,  6),
                    micro1::Token(micro1::TokenKind::INTEGER, "      ST 1, * + 8",                1,  3,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "      ST 1, * + 8",                1,  3, 10),
                    micro1::Token(micro1::TokenKind::STAR,    "      ST 1, * + 8",                1,  3, 12),
                    micro1::Token(micro1::TokenKind::SIGN,    "      ST 1, * + 8",                1,  3, 14),
                    micro1::Token(micro1::TokenKind::INTEGER, "      ST 1, * + 8",                1,  3, 16)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "*", 8 }
            ),
            micro1::Row(
                "",
                2,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "      LA 2, * - 92",               2,  4,  6),
                    micro1::Token(micro1::TokenKind::INTEGER, "      LA 2, * - 92",               1,  4,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "      LA 2, * - 92",               1,  4, 10),
                    micro1::Token(micro1::TokenKind::STAR,    "      LA 2, * - 92",               1,  4, 12),
                    micro1::Token(micro1::TokenKind::SIGN,    "      LA 2, * - 92",               1,  4, 14),
                    micro1::Token(micro1::TokenKind::INTEGER, "      LA 2, * - 92",               2,  4, 16)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "*", -92 }
            ),
            micro1::Row(
                "",
                3,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "      ORG 100",                    3,  5,  6),
                    micro1::Token(micro1::TokenKind::INTEGER, "      ORG 100",                    3,  5, 10)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "HOGE",
                256,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "HOGE: L  3, HOGE",                 1,  6,  6),
                    micro1::Token(micro1::TokenKind::INTEGER, "HOGE: L  3, HOGE",                 1,  6,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "HOGE: L  3, HOGE",                 1,  6, 10),
                    micro1::Token(micro1::TokenKind::STRING,  "HOGE: L  3, HOGE",                 4,  6, 12)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "HOGE", 0 }
            ),
            micro1::Row(
                "",
                257,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "      ST 0, HOGE + 23",            2,  7,  6),
                    micro1::Token(micro1::TokenKind::INTEGER, "      ST 0, HOGE + 23",            1,  7,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "      ST 0, HOGE + 23",            1,  7, 10),
                    micro1::Token(micro1::TokenKind::STRING,  "      ST 0, HOGE + 23",            4,  7, 12),
                    micro1::Token(micro1::TokenKind::SIGN,    "      ST 0, HOGE + 23",            1,  7, 17),
                    micro1::Token(micro1::TokenKind::INTEGER, "      ST 0, HOGE + 23",            2,  7, 19)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "HOGE", 23 }
            ),
            micro1::Row(
                "",
                258,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "      LA 1, HOGE - 12",            2,  8,  6),
                    micro1::Token(micro1::TokenKind::INTEGER, "      LA 1, HOGE - 12",            1,  8,  9),
                    micro1::Token(micro1::TokenKind::COMMA,   "      LA 1, HOGE - 12",            1,  8, 10),
                    micro1::Token(micro1::TokenKind::STRING,  "      LA 1, HOGE - 12",            4,  8, 12),
                    micro1::Token(micro1::TokenKind::SIGN,    "      LA 1, HOGE - 12",            1,  8, 17),
                    micro1::Token(micro1::TokenKind::INTEGER, "      LA 1, HOGE - 12",            2,  8, 19)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "HOGE", -12 }
            ),
            micro1::Row(
                "",
                259,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "END",                              3,  9,  0)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            )
        };
        auto result = micro1::parse(micro1::tokenize(ifs));

        ASSERT_EQ(expected, result);
    }

    TEST(parseTest, GROUP6) {
        std::ifstream ifs("test/unittest/input/input_for_parser_GROUP6.asm");
        ASSERT_FALSE(ifs.fail());

        micro1::Rows expected = {
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP6",       5,  1,  0),
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP6",      20,  1,  6)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "         BDIS *",                  4,  2,  9),
                    micro1::Token(micro1::TokenKind::STAR,    "         BDIS *",                  1,  2, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "*", 0 }
            ),
            micro1::Row(
                "",
                1,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "         BP   * + 34",             2,  3,  9),
                    micro1::Token(micro1::TokenKind::STAR,    "         BP   * + 34",             1,  3, 14),
                    micro1::Token(micro1::TokenKind::SIGN,    "         BP   * + 34",             1,  3, 16),
                    micro1::Token(micro1::TokenKind::INTEGER, "         BP   * + 34",             2,  3, 18)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "*", 34 }
            ),
            micro1::Row(
                "",
                2,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "         BZ   * - 32",             2,  4,  9),
                    micro1::Token(micro1::TokenKind::STAR,    "         BZ   * - 32",             1,  4, 14),
                    micro1::Token(micro1::TokenKind::SIGN,    "         BZ   * - 32",             1,  4, 16),
                    micro1::Token(micro1::TokenKind::INTEGER, "         BZ   * - 32",             2,  4, 18)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "*", -32 }
            ),
            micro1::Row(
                "",
                3,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "         ORG 10",                  3,  5,  9),
                    micro1::Token(micro1::TokenKind::INTEGER, "         ORG 10",                  2,  5, 13)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "SAMPLE",
                16,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "SAMPLE:  BM   SAMPLE",             2,  6,  9),
                    micro1::Token(micro1::TokenKind::STRING,  "SAMPLE:  BM   SAMPLE",             6,  6, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "SAMPLE", 0 }
            ),
            micro1::Row(
                "",
                17,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "         BC   SAMPLE + 23",        2,  7,  9),
                    micro1::Token(micro1::TokenKind::STRING,  "         BC   SAMPLE + 23",        6,  7, 14),
                    micro1::Token(micro1::TokenKind::SIGN,    "         BC   SAMPLE + 23",        1,  7, 21),
                    micro1::Token(micro1::TokenKind::INTEGER, "         BC   SAMPLE + 23",        2,  7, 23)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "SAMPLE", 23 }
            ),
            micro1::Row(
                "",
                18,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "         BNP  SAMPLE - 3",         3,  8,  9),
                    micro1::Token(micro1::TokenKind::STRING,  "         BNP  SAMPLE - 3",         6,  8, 14),
                    micro1::Token(micro1::TokenKind::SIGN,    "         BNP  SAMPLE - 3",         1,  8, 21),
                    micro1::Token(micro1::TokenKind::INTEGER, "         BNP  SAMPLE - 3",         1,  8, 23)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "SAMPLE", -3 }
            ),
            micro1::Row(
                "",
                19,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "         BNZ  *",                  3,  9,  9),
                    micro1::Token(micro1::TokenKind::STAR,    "         BNZ  *",                  1,  9, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "*", 0 }
            ),
            micro1::Row(
                "",
                20,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "         BNM  * + 87",             3, 10,  9),
                    micro1::Token(micro1::TokenKind::STAR,    "         BNM  * + 87",             1, 10, 14),
                    micro1::Token(micro1::TokenKind::SIGN,    "         BNM  * + 87",             1, 10, 16),
                    micro1::Token(micro1::TokenKind::INTEGER, "         BNM  * + 87",             2, 10, 18)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "*", 87 }
            ),
            micro1::Row(
                "",
                21,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "         BNC  * - 98",             3, 11,  9),
                    micro1::Token(micro1::TokenKind::STAR,    "         BNC  * - 98",             1, 11, 14),
                    micro1::Token(micro1::TokenKind::SIGN,    "         BNC  * - 98",             1, 11, 16),
                    micro1::Token(micro1::TokenKind::INTEGER, "         BNC  * - 98",             2, 11, 18)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "*", -98 }
            ),
            micro1::Row(
                "",
                22,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "         B    SAMPLE",             1, 12,  9),
                    micro1::Token(micro1::TokenKind::STRING,  "         B    SAMPLE",             6, 12, 14)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "SAMPLE", 0 }
            ),
            micro1::Row(
                "",
                23,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "         BI   SAMPLE + 81",        2, 13,  9),
                    micro1::Token(micro1::TokenKind::STRING,  "         BI   SAMPLE + 81",        6, 13, 14),
                    micro1::Token(micro1::TokenKind::SIGN,    "         BI   SAMPLE + 81",        1, 13, 21),
                    micro1::Token(micro1::TokenKind::INTEGER, "         BI   SAMPLE + 81",        2, 13, 23)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "SAMPLE", 81 }
            ),
            micro1::Row(
                "",
                24,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "         BSR  SAMPLE - 98",        3, 14,  9),
                    micro1::Token(micro1::TokenKind::STRING,  "         BSR  SAMPLE - 98",        6, 14, 14),
                    micro1::Token(micro1::TokenKind::SIGN,    "         BSR  SAMPLE - 98",        1, 14, 21),
                    micro1::Token(micro1::TokenKind::INTEGER, "         BSR  SAMPLE - 98",        2, 14, 23)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "SAMPLE", -98 }
            ),
            micro1::Row(
                "",
                25,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "END",                              3, 15,  0)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            )
        };
        auto result = micro1::parse(micro1::tokenize(ifs));

        ASSERT_EQ(expected, result);
    }

    TEST(parseTest, GROUP7) {
        std::ifstream ifs("test/unittest/input/input_for_parser_GROUP7.asm");
        ASSERT_FALSE(ifs.fail());

        micro1::Rows expected = {
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP7",       5,  1,  0),
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP7",      20,  1,  6)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    RIO CR",                       3,  2,  4),
                    micro1::Token(micro1::TokenKind::STRING,  "    RIO CR",                       2,  2,  8)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                1,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    WIO LPT",                      3,  3,  4),
                    micro1::Token(micro1::TokenKind::STRING,  "    WIO LPT",                      3,  3,  8)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                2,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    RIO 0",                        3,  4,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    RIO 0",                        1,  4,  8)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                3,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    WIO 1",                        3,  5,  4),
                    micro1::Token(micro1::TokenKind::INTEGER, "    WIO 1",                        1,  5,  8)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                4,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "END",                              3,  6,  0)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            )
        };
        auto result = micro1::parse(micro1::tokenize(ifs));

        ASSERT_EQ(expected, result);
    }

    TEST(parseTest, GROUP8) {
        std::ifstream ifs("test/unittest/input/input_for_parser_GROUP8.asm");
        ASSERT_FALSE(ifs.fail());

        micro1::Rows expected = {
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP8",       5,  1,  0),
                    micro1::Token(micro1::TokenKind::STRING,  "TITLE InputForParserGROUP8",      20,  1,  6)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                0,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    RET",                          3,  2,  4)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                1,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    NOP",                          3,  3,  4)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                2,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "    HLT",                          3,  4,  4)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            ),
            micro1::Row(
                "",
                3,
                {
                    micro1::Token(micro1::TokenKind::STRING,  "END",                              3,  5,  0)
                },
                { micro1::DebugInfoImportance::INFO, "", 0 },
                { "", 0 }
            )
        };
        auto result = micro1::parse(micro1::tokenize(ifs));

        ASSERT_EQ(expected, result);
    }

}
