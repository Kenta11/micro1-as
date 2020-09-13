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
 * @file symbol.cc
 * @brief Implementation for symbol resolver for MICRO-1 assembly program
 * @author Kenta Arai
 * @date 2020/06/28
 */

#include "micro1-as/symbol.h"

namespace micro1 {

std::map<std::string, micro1::M1Addr>
generateSymbolTable(Rows rows) {
    std::map<std::string, micro1::M1Addr> symbol_table;

    for (auto row : rows) {
        if (row.label() != "")
            symbol_table.insert(std::make_pair(row.label(), row.addr()));
    }

    return symbol_table;
}

Rows
resolveSymbols(Rows rows) {
    auto symbol_table = generateSymbolTable(rows);

    for (auto & row : rows) {
        if (row.raddr().label() == "*") {
            auto r = row.raddr();
            r.val(r.offset());
            row.raddr(r);
        }
        else if (symbol_table.find(row.raddr().label()) != symbol_table.end()) {
            auto r = row.raddr();
            r.val(symbol_table.at(row.raddr().label()) - row.addr() + r.offset());
            row.raddr(r);
        }
    }

    return rows;
}

}  // namespace micro1
