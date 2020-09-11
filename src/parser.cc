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
 * @file parser.cc
 * @brief Implementation for parsing tokens
 * @author Kenta Arai
 * @date 2020/05/24
 */

#include "micro1-as/parser.h"

#include "micro1-as/instruction.h"

#include <algorithm>
#include <iostream>

namespace {

using TokenIterator = micro1::Tokens::iterator;

enum class State {
    WAIT_TITLE,
    LOAD_TITLE_NAME,
    LOAD_TITLE_EOL,
    LOAD_LABEL,
    LOAD_COLON,
    LOAD_OPECODE,
    LOAD_RB,
    LOAD_COMMA,
    LOAD_OP1_OPERAND,
    LOAD_OP1_NEXT_OPERAND,
    LOAD_OP1_RA,
    LOAD_OP1_RPAREN,
    LOAD_OP2_OPERAND,
    LOAD_OP3_OPERAND,
    LOAD_OP4_OPERAND,
    LOAD_OP4_LPAREN,
    LOAD_OP4_RA,
    LOAD_OP4_RPAREN,
    LOAD_OP5_ADDRESS,
    LOAD_OP6_ADDRESS,
    LOAD_OP7_DEVICE,
    LOAD_DC_OPERAND,
    LOAD_DS_OPERAND,
    LOAD_ORG_OPERAND,
    LOAD_INST_EOL,
    LOAD_END_EOL,
    FINAL
};

void
skipToEOL(TokenIterator& iter, const TokenIterator end) {
    for (; iter < end; iter++) {
        if ((*iter).kind() == micro1::TokenKind::EOL)
            break;
    }
}

bool
isDecimal(std::string str) {
    return std::count_if(str.begin(), str.end(), [](unsigned char c) { return std::isdigit(c); }) == static_cast<int>(str.length());
}

bool
isHexadecimal(std::string str) {
    return std::count_if(str.begin(), str.end(), [](unsigned char c) { return std::isxdigit(c); }) == static_cast<int>(str.length());
}

bool
isOctal(std::string str) {
    return std::count_if(str.begin(), str.end(), [](unsigned char c) { return '0' <= c && c < '8'; }) == static_cast<int>(str.length());
}

bool
isBinary(std::string str) {
    return std::count_if(str.begin(), str.end(), [](unsigned char c) { return c == '0' || c == '1'; }) == static_cast<int>(str.length());
}

bool
expectPrefix(TokenIterator head, const TokenIterator tail) {
    if (head + 1 >= tail)
        return false;

    if ((*head).kind() != micro1::TokenKind::STRING || (*(head + 1)).kind() != micro1::TokenKind::DQUOTE) {
        return false;
    }

    return (*head).str() == "X" || (*head).str() == "O" || (*head).str() == "B";
}

bool
expectUInt(TokenIterator head, const TokenIterator tail) {
    if (head >= tail)
        return false;

    if ((*head).kind() == micro1::TokenKind::INTEGER) {
        return isDecimal((*head).str());
    } else if ((*head).kind() == micro1::TokenKind::STRING) {
        if (!expectPrefix(head, tail))
            return false;

        if ((*head).str() == "X")
            return isHexadecimal((*(head + 2)).str());
        if ((*head).str() == "O")
            return isOctal((*(head + 2)).str());
        if ((*head).str() == "B")
            return isBinary((*(head + 2)).str());
    }

    return false;
}

bool
expectSInt(TokenIterator head, const TokenIterator tail) {
    if (head >= tail)
        return false;

    if ((*head).kind() == micro1::TokenKind::SIGN)
        head++;

    return expectUInt(head, tail);
}

bool
expectAddress(TokenIterator head, const TokenIterator tail) {
    if (head >= tail)
        return false;

    // it is expected that first token is star or string
    if ((*head).kind() != micro1::TokenKind::STAR && (*head).kind() != micro1::TokenKind::STRING)
        return false;

    // if second token is sign, third token is decimal number
    if ((*(head + 1)).kind() != micro1::TokenKind::SIGN)
        return true;

    return isDecimal((*(head + 2)).str());
}

bool
expectConstant(TokenIterator head, const TokenIterator tail) {
    if (head >= tail)
        return false;

    // signed integer
    if (expectSInt(head, tail))
        return true;

    // two characters
    if ((*head).kind() == micro1::TokenKind::CHARS)
        return true;

    // address label
    return (*head).kind() == micro1::TokenKind::STRING;
}

}  // namespace

namespace micro1 {

/**
 * @brief Parse lexical tokens
 * @param[in] tokens tokens which parsed by lexical analyzer
 * @return std::vector<Row> parsed tokens
 */
Rows
parse(Tokens tokens) {
    ::State state = ::State::WAIT_TITLE;
    std::string label;
    M1Addr addr = 0;
    std::string reference;
    int64_t offset = 0;
    Rows ret;
    Tokens::iterator iter = tokens.begin();
    Tokens instruction;

    for (; iter < tokens.end(); iter++) {
        switch (state) {
            case ::State::WAIT_TITLE:
                if ((*iter).kind() == TokenKind::EOL) {
                    ret.emplace_back(Row("", addr, {}, DebugInfo(DebugInfoImportance::INFO, "", 0), ReferenceAddress("", 0)));
                } else if ((*iter).str() == "TITLE") {
                    state = ::State::LOAD_TITLE_NAME;
                    instruction.emplace_back(*iter);
                } else {
                    state = ::State::LOAD_LABEL;
                    instruction.emplace_back(*iter);
                    ret.emplace_back(Row("", addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required \"TITLE\".", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    ::skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_TITLE_NAME:
                instruction.emplace_back(*iter);

                if ((*iter).kind() == TokenKind::STRING) {
                    state = ::State::LOAD_TITLE_EOL;
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row("", addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required title name.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    ::skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_TITLE_EOL:
                state = ::State::LOAD_LABEL;

                if ((*iter).kind() == TokenKind::EOL) {
                    ret.emplace_back(Row("", addr, instruction, DebugInfo(DebugInfoImportance::INFO, "", 0), ReferenceAddress("", 0)));
                    instruction.clear();
                } else {
                    instruction.emplace_back(*iter);
                    ret.emplace_back(Row("", addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Too many tokens.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    ::skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_LABEL:
                if ((*iter).kind() == TokenKind::EOL) {
                    ret.emplace_back(Row("", addr, {}, DebugInfo(DebugInfoImportance::INFO, "", 0), ReferenceAddress("", 0)));
                } else if ((*iter).kind() == TokenKind::STRING) {
                    state = ::State::LOAD_COLON;
                    label = (*iter).str();
                    reference = "";
                    offset = 0;
                } else {
                    instruction.emplace_back(*iter);
                    ret.emplace_back(Row("", addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required label name or opecode.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    ::skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_COLON:
                state = ::State::LOAD_OPECODE;

                if ((*iter).kind() != TokenKind::COLON) {
                    label = "";
                    iter -= 2;
                }

                break;
            case ::State::LOAD_OPECODE:
                instruction.emplace_back(*iter);

                if ((*iter).kind() != TokenKind::STRING) {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required opecode.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                } else {
                    switch (getNumberOfGroup((*iter).str())) {
                        case InstGroup::GROUP1:
                            [[fallthrough]];
                        case InstGroup::GROUP2:
                            [[fallthrough]];
                        case InstGroup::GROUP3:
                            [[fallthrough]];
                        case InstGroup::GROUP4:
                            [[fallthrough]];
                        case InstGroup::GROUP5:
                            state = ::State::LOAD_RB;
                            break;
                        case InstGroup::GROUP6:
                            state = ::State::LOAD_OP6_ADDRESS;
                            break;
                        case InstGroup::GROUP7:
                            state = ::State::LOAD_OP7_DEVICE;
                            break;
                        case InstGroup::GROUP8:
                            state = ::State::LOAD_INST_EOL;
                            break;
                        case InstGroup::GROUP9:
                            if ((*iter).str() == "DC") {
                                state = ::State::LOAD_DC_OPERAND;
                            } else if ((*iter).str() == "DS") {
                                state = ::State::LOAD_DS_OPERAND;
                            } else /* if ((*iter).str() == "ORG") */ {
                                state = ::State::LOAD_ORG_OPERAND;
                            }

                            break;
                        default:
                            if ((*iter).str() == "END") {
                                state = ::State::LOAD_END_EOL;
                            } else {
                                state = ::State::LOAD_LABEL;
                                ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Unknown opecode.", instruction.size() - 1), ReferenceAddress("", 0)));
                                instruction.clear();
                                skipToEOL(iter, tokens.end());
                            }

                            break;
                    }
                }

                break;
            case ::State::LOAD_RB:
                instruction.emplace_back(*iter);

                if ((*iter).kind() == TokenKind::INTEGER) {
                    state = ::State::LOAD_COMMA;
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required integer for rb register.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_COMMA:
                instruction.emplace_back(*iter);

                if ((*iter).kind() == TokenKind::COMMA) {
                    switch (getNumberOfGroup((*(iter - 2)).str())) {
                        case InstGroup::GROUP1:
                            state = ::State::LOAD_OP1_OPERAND;
                            break;
                        case InstGroup::GROUP2:
                            state = ::State::LOAD_OP2_OPERAND;
                            break;
                        case InstGroup::GROUP3:
                            state = ::State::LOAD_OP3_OPERAND;
                            break;
                        case InstGroup::GROUP4:
                            state = ::State::LOAD_OP4_OPERAND;
                            break;
                        default:  // case InstGroup::GROUP5:
                            state = ::State::LOAD_OP5_ADDRESS;
                            break;
                    }
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required comma.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_OP1_OPERAND:
                instruction.emplace_back(*iter);

                if ((*iter).kind() == TokenKind::LPAREN) {
                    state = ::State::LOAD_OP1_RA;
                } else if (::expectUInt(iter, tokens.end())) {
                    state = ::State::LOAD_OP1_NEXT_OPERAND;
                    if (::expectPrefix(iter, tokens.end())) {
                        instruction.emplace_back(*(++iter));
                        instruction.emplace_back(*(++iter));
                    }
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required unsigned integer.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_OP1_NEXT_OPERAND:
                if ((*iter).kind() == TokenKind::LPAREN) {
                    instruction.emplace_back(*iter);
                    state = ::State::LOAD_OP1_RA;
                } else if ((*iter).kind() == TokenKind::EOL) {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::INFO, "", 0), ReferenceAddress("", 0)));
                    instruction.clear();
                    addr++;
                } else {
                    state = ::State::LOAD_LABEL;
                    instruction.emplace_back(*iter);
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required an end of line or a left parenthesis.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_OP1_RA:
                instruction.emplace_back(*iter);

                if ((*iter).kind() == TokenKind::INTEGER) {
                    state = ::State::LOAD_OP1_RPAREN;
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required integer for ra register.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_OP1_RPAREN:
                instruction.emplace_back(*iter);

                if ((*iter).kind() == TokenKind::RPAREN) {
                    state = ::State::LOAD_INST_EOL;
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required a right parenthesis.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_OP2_OPERAND:
                instruction.emplace_back(*iter);

                if (::expectUInt(iter, tokens.end())) {
                    state = ::State::LOAD_INST_EOL;
                    if (::expectPrefix(iter, tokens.end())) {
                        instruction.emplace_back(*(++iter));
                        instruction.emplace_back(*(++iter));
                    }
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required unsigned integer.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_OP3_OPERAND:
                instruction.emplace_back(*iter);

                if (::expectSInt(iter, tokens.end())) {
                    state = ::State::LOAD_INST_EOL;
                    if ((*iter).kind() == TokenKind::SIGN) {
                        instruction.emplace_back(*(++iter));
                    }
                    if (::expectPrefix(iter, tokens.end())) {
                        instruction.emplace_back(*(++iter));
                        instruction.emplace_back(*(++iter));
                    }
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required signed integer.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_OP4_OPERAND:
                instruction.emplace_back(*iter);

                if ((*iter).kind() == TokenKind::LPAREN) {
                    state = ::State::LOAD_OP4_RA;
                } else if (::expectSInt(iter, tokens.end())) {
                    state = ::State::LOAD_OP4_LPAREN;
                    if ((*iter).kind() == TokenKind::SIGN) {
                        instruction.emplace_back(*(++iter));
                    }
                    if (::expectPrefix(iter, tokens.end())) {
                        instruction.emplace_back(*(++iter));
                        instruction.emplace_back(*(++iter));
                    }
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required signed integer or a left parenthesis.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_OP4_LPAREN:
                instruction.emplace_back(*iter);

                if ((*iter).kind() == TokenKind::LPAREN) {
                    state = ::State::LOAD_OP4_RA;
                } else {
                    state = ::State::LOAD_LABEL;
                    instruction.emplace_back(*iter);
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required a left parenthesis.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_OP4_RA:
                instruction.emplace_back(*iter);

                if ((*iter).kind() == TokenKind::INTEGER) {
                    state = ::State::LOAD_OP4_RPAREN;
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required integer for ra register.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_OP4_RPAREN:
                instruction.emplace_back(*iter);

                if ((*iter).kind() == TokenKind::RPAREN) {
                    state = ::State::LOAD_INST_EOL;
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required a right parenthesis.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_OP5_ADDRESS:
                instruction.emplace_back(*iter);
                reference = (*iter).str();

                if (::expectAddress(iter, tokens.end())) {
                    state = ::State::LOAD_INST_EOL;
                    if (iter + 1 < tokens.end()) {
                        if ((*(iter + 1)).kind() == TokenKind::SIGN) {
                            offset = static_cast<int64_t>(((*(iter + 1)).str() == "+" ? 1 : -1)) * std::stoi((*(iter + 2)).str());
                            instruction.emplace_back(*(++iter));
                            instruction.emplace_back(*(++iter));
                        }
                    }
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required address.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_OP6_ADDRESS:
                instruction.emplace_back(*iter);
                reference = (*iter).str();

                if (::expectAddress(iter, tokens.end())) {
                    state = ::State::LOAD_INST_EOL;
                    if (iter + 1 < tokens.end()) {
                        if ((*(iter + 1)).kind() == TokenKind::SIGN) {
                            offset = static_cast<int64_t>(((*(iter + 1)).str() == "+" ? 1 : -1)) * std::stoi((*(iter + 2)).str());
                            instruction.emplace_back(*(++iter));
                            instruction.emplace_back(*(++iter));
                        }
                    }
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required address.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_OP7_DEVICE:
                instruction.emplace_back(*iter);

                if ((*iter).kind() == TokenKind::STRING) {
                    if ((*iter).str() == "CR" || (*iter).str() == "LPT") {
                        state = ::State::LOAD_INST_EOL;
                    } else {
                        state = ::State::LOAD_LABEL;
                        ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Unknown device name.", instruction.size() - 1), ReferenceAddress("", 0)));
                        instruction.clear();
                        skipToEOL(iter, tokens.end());
                    }
                } else if ((*iter).kind() == TokenKind::INTEGER) {
                    if ((*iter).str() == "0" || (*iter).str() == "1") {
                        state = ::State::LOAD_INST_EOL;
                    } else {
                        state = ::State::LOAD_LABEL;
                        ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Unknown device number.", instruction.size() - 1), ReferenceAddress("", 0)));
                        instruction.clear();
                        skipToEOL(iter, tokens.end());
                    }
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required device name or number.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_DC_OPERAND:
                instruction.emplace_back(*iter);

                if (::expectConstant(iter, tokens.end())) {
                    state = ::State::LOAD_INST_EOL;
                    if (::expectSInt(iter, tokens.end())) {
                        if ((*iter).kind() == TokenKind::SIGN) {
                            instruction.emplace_back(*(++iter));
                        }
                        if (::expectPrefix(iter, tokens.end())) {
                            instruction.emplace_back(*(++iter));
                            instruction.emplace_back(*(++iter));
                        }
                    }
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required constant value.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_DS_OPERAND:
                instruction.emplace_back(*iter);

                if (::isDecimal((*iter).str())) {
                    state = ::State::LOAD_INST_EOL;
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required decimal.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_ORG_OPERAND:
                instruction.emplace_back(*iter);

                if (::isHexadecimal((*iter).str())) {
                    state = ::State::LOAD_INST_EOL;
                } else {
                    state = ::State::LOAD_LABEL;
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Required hexadecimal.", instruction.size() - 1), ReferenceAddress("", 0)));
                    instruction.clear();
                    skipToEOL(iter, tokens.end());
                }

                break;
            case ::State::LOAD_INST_EOL:
                state = ::State::LOAD_LABEL;

                if ((*iter).kind() == TokenKind::EOL) {
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::INFO, "", 0), ReferenceAddress(reference, offset)));

                    if ((*(iter - 2)).str() == "ORG") {
                        addr = static_cast<M1Addr>(std::stoi((*(iter - 1)).str(), nullptr, 16));
                    }
                    else if ((*(iter - 2)).str() == "DS") {
                        addr = static_cast<M1Addr>(std::stoi((*(iter - 1)).str(), nullptr, 10));
                    } else {
                        addr++;
                    }
                } else {
                    instruction.emplace_back(*iter);
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Too many tokens.", instruction.size() - 1), ReferenceAddress("", 0)));
                    skipToEOL(iter, tokens.end());
                }

                instruction.clear();
                break;
            case ::State::LOAD_END_EOL:
                state = ::State::FINAL;

                if ((*iter).kind() == TokenKind::EOL) {
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::INFO, "", 0), ReferenceAddress("", 0)));
                } else {
                    instruction.emplace_back(*iter);
                    ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Too many tokens.", instruction.size() - 1), ReferenceAddress("", 0)));
                    skipToEOL(iter, tokens.end());
                }

                instruction.clear();
                break;
            case ::State::FINAL:
                instruction.emplace_back(*iter);
                goto EndOfParse;
            default:
                std::cerr << "Detected invalid state of parser." << std::endl;
                exit(2);
        }
    }

EndOfParse:

    for (; iter < tokens.end(); iter++) {
        if ((*iter).kind() == TokenKind::EOL) {
            ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Invalid token.", 0), ReferenceAddress("", 0)));
            skipToEOL(iter, tokens.end());
        } else {
            instruction.emplace_back(*iter);
        }
    }

    if (instruction.size() != 0) {
        ret.emplace_back(Row(label, addr, instruction, DebugInfo(DebugInfoImportance::ERROR, "Invalid token.", 0), ReferenceAddress("", 0)));
        skipToEOL(iter, tokens.end());
    }

    return ret;
}

}  // namespace micro1
