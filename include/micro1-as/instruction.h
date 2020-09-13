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
 * @file instruction.h
 * @brief Declaration of instruction utility
 * @author Kenta Arai
 * @date 2020/05/24
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

namespace micro1 {

/**
 * @brief Instruction groups of MICRO-1 ISA
 */
enum class InstGroup {
    GROUP1,
    GROUP2,
    GROUP3,
    GROUP4,
    GROUP5,
    GROUP6,
    GROUP7,
    GROUP8,
    GROUP9,
    INVALID
};

/**
 * @brief Class for MICRO-1 instruction encoding
 */
class Instruction {
public:
    /**
     * @brief Constructor for Instruction
     */
    Instruction() { m_value = 0; }
    /**
     * @brief Constructor for Instruction
     * @param[in] value MICRO-1 encoding
     */
    Instruction(uint16_t value) : m_value(value) {}

private:
    uint16_t m_value;  //! MICRO-1 encoding
public:
    /**
     * @brief Getter for m_value
     * @return uint16_t& encoding
     */
    uint16_t& value() { return m_value; }
    /**
     * @brief Return opecode encoding
     * @return uint16_t& encoding
     */
    uint8_t op() const { return static_cast<uint8_t>((m_value >> 12)); }
    /**
     * @brief Return ra encoding
     * @return uint8_t ra encoding
     */
    uint8_t ra() const { return static_cast<uint8_t>((m_value >> 10) & 3); }
    /**
     * @brief Return rb encoding
     * @return uint8_t rb encoding
     */
    uint8_t rb() const { return static_cast<uint8_t>((m_value >> 8) & 3); }
    /**
     * @brief Return constant value in nd
     * @return uint8_t nd encoding
     */
    uint8_t nd() const { return static_cast<uint8_t>(m_value & 0xF); }
};

/**
 * @brief Return group number of mnemonic
 * @param[in] op MICRO-1 mnemonic
 * @return InstGroup number of instruction group
 */
InstGroup
getNumberOfGroup(std::string op);

/**
 * @brief Return instruction encoding
 * @param[in] op MICRO-1 mnemonic
 * @return std::tuple<uint8_t,uint8_t,uint8_t> encoding { op, ra, rb }
 */
std::tuple<uint8_t, uint8_t, uint8_t>
getEncoding(std::string op);

}  // namespace micro1

#endif  // INSTRUCTION_H
