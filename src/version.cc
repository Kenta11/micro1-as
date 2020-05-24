#include "version.h"

#include <iostream>

using std::cout;
using std::endl;

namespace {

const std::string PROGRAM_NAME  = "MICRO-1 ASSEMBLER";
const std::string CC_VERSION    = "C++17";
const uint32_t MAJOR_VERSION    = 1;
const uint32_t MINOR_VERSION    = 0;
const uint32_t BUILD_VERSION    = 0;
const uint32_t REVISION_VERSION = 0;

}

namespace micro1 {

void
printVersion() {
    cout << "   *** ";
    cout << PROGRAM_NAME << " ";
    cout << "(Ver. ";
    cout << MAJOR_VERSION    << ".";
    cout << MINOR_VERSION    << ".";
    cout << BUILD_VERSION    << ".";
    cout << REVISION_VERSION << ") ";
    cout << " ***" << endl;
}

}