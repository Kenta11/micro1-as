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
 * @file parser.h
 * @brief Declaration for parsing tokens
 * @author Kenta Arai
 * @date 2020/05/24
 */

#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "micro1.h"

namespace micro1 {

/**
 * @brief Importance of debug imformation
 */
enum class DebugInfoImportance {
    ERROR,
    WARNING,
    INFO
};

/**
 * @brief Class for debug information
 */
class DebugInfo {
public:
    /**
     * @brief Constructor for DebugInfo
     * @param[in] importance importance of debug information
     * @param[in] message an error message
     * @param[in] index index pointing to the token with error
     */
    DebugInfo(DebugInfoImportance importance, std::string message, uint64_t index) : m_importance(importance), m_message(message), m_index(index) {}
    /**
     * @brief Getter for m_importance
     */
    DebugInfoImportance importance() const { return m_importance; }
    /**
     * @brief Getter for m_message
     */
    std::string message() const { return m_message; }
    /**
     * @brief Getter for m_index
     */
    uint64_t index() const { return m_index; }
    /**
     * @brief Operator '==' for DebugInfo
     * @return Result of comparing two DebugInfo objects
     */
    bool operator==(DebugInfo d) const {
        return m_importance == d.importance() &&
               m_message == d.message() &&
               m_index == d.index();
    }
    /**
     * @brief Operator '!=' for DebugInfo
     * @return Result of comparing two DebugInfo objects
     */
    bool operator!=(DebugInfo d) const {
        return m_importance != d.importance() ||
               m_message != d.message() ||
               m_index != d.index();
    }

private:
    DebugInfoImportance m_importance;  //! importance of debug information
    std::string m_message;             //! error message
    uint64_t m_index;                  //! index pointing to the token with error
};

/**
 * @brief Class for reference address
 */
class ReferenceAddress {
public:
    /**
     * @brief Constructor for ReferenceAddress
     * @param[in] label label name of the referenced address
     * @param[in] offset of address
     */
    ReferenceAddress(std::string label, int64_t offset) : m_label(label), m_offset(offset) {}
    /**
     * @brief Getter for m_label
     * @return std::string label name
     */
    std::string label() const { return m_label; }
    /**
     * @brief Getter for m_offset
     * @return int64_t offset of address
     */
    int64_t offset() const { return m_offset; }
    /**
     * @brief Operator '==' for ReferenceAddress
     * @return Result of comparing two ReferenceAddress objects
     */
    bool operator==(ReferenceAddress a) const {
        return m_label == a.label() &&
               m_offset == a.offset();
    }
    /**
     * @brief Operator '!=' for ReferenceAddress
     * @return Result of comparing two ReferenceAddress objects
     */
    bool operator!=(ReferenceAddress a) const {
        return m_label != a.label() ||
               m_offset != a.offset();
    }

private:
    std::string m_label;  //! label name
    int64_t m_offset;     // ! offset of address
};

/**
 * @brief Class for a row which has tokens
 */
class Row {
public:
    /**
     * @brief Constructor for Row
     * @param[in] label label name in a line
     * @param[in] address
     * @param[in] instruction tokens which make up a instruction
     * @param[in] dinfo debug information
     * @param[in] raddr address referenced by the instruction
     */
    Row(std::string label, M1Addr addr, Tokens instruction, DebugInfo dinfo, ReferenceAddress raddr) : m_label(label), m_addr(addr), m_instruction(instruction), m_dinfo(dinfo), m_raddr(raddr) {}
    /**
     * @brief Getter for m_label
     * @return std::string label name in a line
     */
    std::string label() const { return m_label; }
    /**
     * @brief Getter for m_addr
     * @return M1Addr address
     */
    M1Addr addr() const { return m_addr; }
    /**
     * @brief Getter for m_instruction
     * @return Tokens tokens which make up a instruction
     */
    Tokens instruction() const { return m_instruction; }
    /**
     * @brief Getter for m_dinfo
     * @return DebugInfo debug information
     */
    DebugInfo dinfo() const { return m_dinfo; }
    /**
     * @brief Getter for m_raddr
     * @return ReferencedAddress address referenced by the instruction
     */
    ReferenceAddress raddr() const { return m_raddr; }
    /**
     * @brief Operator '==' for Row
     * @return Result of comparing two rows
     */
    bool operator==(Row r) const {
        return m_label == r.label() &&
               m_addr == r.addr() &&
               m_instruction == r.instruction() &&
               m_dinfo == r.dinfo() &&
               m_raddr == r.raddr();
    }
    /**
     * @brief Operator '!=' for Row
     * @return Result of comparing two rows
     */
    bool operator!=(Row r) const {
        return m_label != r.label() ||
               m_addr != r.addr() ||
               m_instruction != r.instruction() ||
               m_dinfo != r.dinfo() ||
               m_raddr != r.raddr();
    }

private:
    std::string m_label;       //! label name in a line
    M1Addr m_addr;             //! address
    Tokens m_instruction;      //! instruction tokens which make up a instruction
    DebugInfo m_dinfo;         //! debug information
    ReferenceAddress m_raddr;  //! address referenced by the instruction
};

/**
 * @brief Vector for row
 */
typedef std::vector<Row> Rows;

/**
 * @brief Parse lexical tokens
 * @param[in] tokens tokens which parsed by lexical analyzer
 * @return std::vector<Row> parsed tokens
 */
Rows
parse(const Tokens tokens);

}  // namespace micro1

#endif  // PARSER_H
