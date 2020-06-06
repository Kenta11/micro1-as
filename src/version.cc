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
 * @file version.cc
 * @brief Implementation for displaying micro1-as version
 * @author Kenta Arai
 * @date 2020/05/24
 */

#include "micro1-as/version.h"

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

/**
* @brief Print version of micro1-as and C++
*/
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
