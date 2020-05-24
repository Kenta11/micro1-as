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

#ifndef PARSER_H
#define PARSER_H

#include "token.h"

#include <cstdint>
#include <string>
#include <vector>

namespace micro1 {

enum class DebugInfoImportance {
    ERROR,
    WARNING,
    INFO
};

class DebugInfo {
public:
    DebugInfo(DebugInfoImportance importance, std::string message, uint64_t index) : m_importance(importance), m_message(message), m_index(index) {}
    DebugInfoImportance importance() const { return m_importance; }
    std::string message() const { return m_message; }
    uint64_t index() const { return m_index; }
private:
    DebugInfoImportance m_importance;
    std::string m_message;
    uint64_t m_index;
};

class ReferenceAddress {
public:
    ReferenceAddress(std::string label, std::int64_t offset) : m_label(label), m_offset(offset) {}
    std::string label() const { return m_label; }
    std::int64_t offset() const { return m_offset; }
private:
    std::string m_label;
    std::int64_t m_offset;
};

class Row {
public:
    Row(std::string label, std::vector< Token > instruction, DebugInfo dinfo, ReferenceAddress raddr) : m_label(label), m_instruction(instruction), m_dinfo(dinfo), m_raddr(raddr) {}
    std::string label() const { return m_label; }
    std::vector< Token > instruction() const { return m_instruction; }
    DebugInfo dinfo() const { return m_dinfo; }
    ReferenceAddress raddr() const { return m_raddr; }
private:
    std::string m_label;
    std::vector< Token > m_instruction;
    DebugInfo m_dinfo;
    ReferenceAddress m_raddr;
};

std::vector< Row >
parse(const std::vector< Token > tokens);

}

#endif // PARSER_H