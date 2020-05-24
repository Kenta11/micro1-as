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
 * @file output.h
 * @brief Declaration for outputting the result of parsing
 * @author Kenta Arai
 * @date 2020/05/24
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include "parser.h"

namespace micro1 {

/**
* @brief Write a listing file
* @param[in] rows parsed tokens
* @param[in] filename listing file name
*/
void writeListingFile(const std::vector< Row > rows, const std::string filename);

/**
* @brief Print syntax errors to standard error output
* @param[in] rows parsed tokens
*/
void printSyntaxError(const std::vector< Row > rows);

/**
* @brief Write a object file
* @param[in] rows parsed tokens
* @param[in] filename object file name
* @return bool If true, lines are syntactically correct
*/
bool writeObjectFile(const std::vector< Row > rows, const std::string filename);

}

#endif // OUTPUT_H