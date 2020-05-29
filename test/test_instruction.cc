#include "instruction.h"

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

}
