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
 * @file instruction.cc
 * @brief Inplementation of instruction utility
 * @author Kenta Arai
 * @date 2020/05/24
 */

#include "micro1-as/instruction.h"

#include <map>
#include <stdexcept>
#include <vector>

namespace {

std::map<micro1::InstGroup, std::vector<std::string> > group = {
    {micro1::InstGroup::GROUP1, {"ADD", "SUB", "AND", "OR", "XOR", "MULT", "DIV", "CMP", "EX"}},
    {micro1::InstGroup::GROUP2, {"LC", "PUSH", "POP"}},
    {micro1::InstGroup::GROUP3, {"SL", "SA", "SC", "BIX"}},
    {micro1::InstGroup::GROUP4, {"LEA", "LX", "STX"}},
    {micro1::InstGroup::GROUP5, {"L", "ST", "LA"}},
    {micro1::InstGroup::GROUP6, {"BDIS", "BP", "BZ", "BM", "BC", "BNP", "BNZ", "BNM", "BNC", "B", "BI", "BSR"}},
    {micro1::InstGroup::GROUP7, {"RIO", "WIO"}},
    {micro1::InstGroup::GROUP8, {"RET", "NOP", "HLT"}},
    {micro1::InstGroup::GROUP9, {"DC", "DS", "ORG"}}};

std::map<std::string, std::tuple<uint8_t, uint8_t, uint8_t> > encoding = {
    {"ADD", {0, 0, 0}},
    {"SUB", {1, 0, 0}},
    {"AND", {2, 0, 0}},
    {"OR", {3, 0, 0}},
    {"XOR", {4, 0, 0}},
    {"SL", {5, 0, 0}},
    {"SA", {5, 1, 0}},
    {"SC", {5, 2, 0}},
    {"MULT", {6, 0, 0}},
    {"DIV", {7, 0, 0}},
    {"CMP", {8, 0, 0}},
    {"L", {9, 0, 0}},
    {"ST", {9, 1, 0}},
    {"LA", {9, 2, 0}},
    {"LC", {9, 3, 0}},
    {"LEA", {0xA, 0, 0}},
    {"LX", {0xB, 0, 0}},
    {"STX", {0xC, 0, 0}},
    {"PUSH", {0xD, 0, 0}},
    {"POP", {0xD, 1, 0}},
    {"BIX", {0xD, 2, 0}},
    {"BDIS", {0xD, 3, 0}},
    {"BP", {0xE, 0, 0}},
    {"BZ", {0xE, 0, 1}},
    {"BM", {0xE, 0, 2}},
    {"BC", {0xE, 0, 3}},
    {"BNP", {0xE, 1, 0}},
    {"BNZ", {0xE, 1, 1}},
    {"BNM", {0xE, 1, 2}},
    {"BNC", {0xE, 1, 3}},
    {"B", {0xE, 2, 0}},
    {"BI", {0xE, 2, 1}},
    {"BSR", {0xE, 2, 2}},
    {"RET", {0xE, 2, 3}},
    {"RIO", {0xE, 3, 0}},
    {"WIO", {0xE, 3, 1}},
    {"NOP", {0xE, 3, 2}},
    {"HLT", {0xE, 3, 3}},
    {"EX", {0xF, 0, 0}}};

}  // namespace

namespace micro1 {

/**
 * @brief Return group number of mnemonic
 * @param[in] op MICRO-1 mnemonic
 * @return InstGroup number of instruction group
 */
InstGroup
getNumberOfGroup(std::string op) {
    for (auto g : group) {
        auto [n, insts] = g;
        for (auto inst : insts) {
            if (op == inst) {
                return n;
            }
        }
    }
    return InstGroup::INVALID;
}

/**
 * @brief Return instruction encoding
 * @param[in] op MICRO-1 mnemonic
 * @return std::tuple<uint8_t,uint8_t,uint8_t> encoding { op, ra, rb }
 */
std::tuple<uint8_t, uint8_t, uint8_t>
getEncoding(std::string op) {
    try {
        return encoding.at(op);
    } catch (std::out_of_range) {
        return {0, 0, 0};
    }
}

}  // namespace micro1
