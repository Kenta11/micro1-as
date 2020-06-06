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
 * @file test_instruction.cc
 * @brief Test for instruction.cc
 * @author Kenta Arai
 * @date 2020/05/29
 */

#include "micro1-as/instruction.h"

#include <gtest/gtest.h>

namespace {

    TEST(getNumberOfGroupTest, GROUP1) {
        ASSERT_EQ(micro1::InstGroup::GROUP1, micro1::getNumberOfGroup("ADD"));
        ASSERT_EQ(micro1::InstGroup::GROUP1, micro1::getNumberOfGroup("SUB"));
        ASSERT_EQ(micro1::InstGroup::GROUP1, micro1::getNumberOfGroup("AND"));
        ASSERT_EQ(micro1::InstGroup::GROUP1, micro1::getNumberOfGroup("OR"));
        ASSERT_EQ(micro1::InstGroup::GROUP1, micro1::getNumberOfGroup("XOR"));
        ASSERT_EQ(micro1::InstGroup::GROUP1, micro1::getNumberOfGroup("MULT"));
        ASSERT_EQ(micro1::InstGroup::GROUP1, micro1::getNumberOfGroup("DIV"));
        ASSERT_EQ(micro1::InstGroup::GROUP1, micro1::getNumberOfGroup("CMP"));
        ASSERT_EQ(micro1::InstGroup::GROUP1, micro1::getNumberOfGroup("EX"));
    }

    TEST(getNumberOfGroupTest, GROUP2) {
        ASSERT_EQ(micro1::InstGroup::GROUP2, micro1::getNumberOfGroup("LC"));
        ASSERT_EQ(micro1::InstGroup::GROUP2, micro1::getNumberOfGroup("PUSH"));
        ASSERT_EQ(micro1::InstGroup::GROUP2, micro1::getNumberOfGroup("POP"));
    }

    TEST(getNumberOfGroupTest, GROUP3) {
        ASSERT_EQ(micro1::InstGroup::GROUP3, micro1::getNumberOfGroup("SL"));
        ASSERT_EQ(micro1::InstGroup::GROUP3, micro1::getNumberOfGroup("SA"));
        ASSERT_EQ(micro1::InstGroup::GROUP3, micro1::getNumberOfGroup("SC"));
        ASSERT_EQ(micro1::InstGroup::GROUP3, micro1::getNumberOfGroup("BIX"));
    }

    TEST(getNumberOfGroupTest, GROUP4) {
        ASSERT_EQ(micro1::InstGroup::GROUP4, micro1::getNumberOfGroup("LEA"));
        ASSERT_EQ(micro1::InstGroup::GROUP4, micro1::getNumberOfGroup("LX"));
        ASSERT_EQ(micro1::InstGroup::GROUP4, micro1::getNumberOfGroup("STX"));
    }

    TEST(getNumberOfGroupTest, GROUP5) {
        ASSERT_EQ(micro1::InstGroup::GROUP5, micro1::getNumberOfGroup("L"));
        ASSERT_EQ(micro1::InstGroup::GROUP5, micro1::getNumberOfGroup("ST"));
        ASSERT_EQ(micro1::InstGroup::GROUP5, micro1::getNumberOfGroup("LA"));
    }

    TEST(getNumberOfGroupTest, GROUP6) {
        ASSERT_EQ(micro1::InstGroup::GROUP6, micro1::getNumberOfGroup("BDIS"));
        ASSERT_EQ(micro1::InstGroup::GROUP6, micro1::getNumberOfGroup("BP"));
        ASSERT_EQ(micro1::InstGroup::GROUP6, micro1::getNumberOfGroup("BZ"));
        ASSERT_EQ(micro1::InstGroup::GROUP6, micro1::getNumberOfGroup("BM"));
        ASSERT_EQ(micro1::InstGroup::GROUP6, micro1::getNumberOfGroup("BC"));
        ASSERT_EQ(micro1::InstGroup::GROUP6, micro1::getNumberOfGroup("BNP"));
        ASSERT_EQ(micro1::InstGroup::GROUP6, micro1::getNumberOfGroup("BNZ"));
        ASSERT_EQ(micro1::InstGroup::GROUP6, micro1::getNumberOfGroup("BNM"));
        ASSERT_EQ(micro1::InstGroup::GROUP6, micro1::getNumberOfGroup("BNC"));
        ASSERT_EQ(micro1::InstGroup::GROUP6, micro1::getNumberOfGroup("B"));
        ASSERT_EQ(micro1::InstGroup::GROUP6, micro1::getNumberOfGroup("BI"));
        ASSERT_EQ(micro1::InstGroup::GROUP6, micro1::getNumberOfGroup("BSR"));
    }

    TEST(getNumberOfGroupTest, GROUP7) {
        ASSERT_EQ(micro1::InstGroup::GROUP7, micro1::getNumberOfGroup("RIO"));
        ASSERT_EQ(micro1::InstGroup::GROUP7, micro1::getNumberOfGroup("WIO"));
    }

    TEST(getNumberOfGroupTest, GROUP8) {
        ASSERT_EQ(micro1::InstGroup::GROUP8, micro1::getNumberOfGroup("RET"));
        ASSERT_EQ(micro1::InstGroup::GROUP8, micro1::getNumberOfGroup("NOP"));
        ASSERT_EQ(micro1::InstGroup::GROUP8, micro1::getNumberOfGroup("HLT"));
    }

    TEST(getNumberOfGroupTest, GROUP9) {
        ASSERT_EQ(micro1::InstGroup::GROUP9, micro1::getNumberOfGroup("DS"));
        ASSERT_EQ(micro1::InstGroup::GROUP9, micro1::getNumberOfGroup("DC"));
        ASSERT_EQ(micro1::InstGroup::GROUP9, micro1::getNumberOfGroup("ORG"));
    }

    TEST(getNumberOfGroupTest, INVALID) {
        ASSERT_EQ(micro1::InstGroup::INVALID, micro1::getNumberOfGroup("TITLE"));
        ASSERT_EQ(micro1::InstGroup::INVALID, micro1::getNumberOfGroup("END"));
        ASSERT_EQ(micro1::InstGroup::INVALID, micro1::getNumberOfGroup("HOGE"));
    }

}
