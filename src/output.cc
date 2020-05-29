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
 * @file output.cc
 * @brief Implementation for outputting the result of parsing
 * @author Kenta Arai
 * @date 2020/05/24
 */

#include "output.h"

#include "micro1.h"
#include "instruction.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
#include <tuple>

namespace {

using TokenIterator = micro1::Tokens::iterator;

std::tuple< std::vector< micro1::M1Addr >, std::map< std::string, micro1::M1Addr > >
calculateAddress(const std::vector< micro1::Row > rows) {
	std::vector< micro1::M1Addr > addresses;
	std::map< std::string, micro1::M1Addr > labels;
	micro1::M1Addr addr = 0;

	for (auto row : rows) {
		if (row.instruction().size() == 0)
			continue;
		else if (row.instruction().at(0).str() == "TITLE")
			continue;
		else if (row.instruction().at(0).str() == "END")
			continue;
		else if (row.instruction().at(0).str() == "ORG") {
			addr = std::stoi(row.instruction().at(1).str(), nullptr, 16);
			continue;
		}

		if (row.label() != "")
			labels.insert(std::make_pair(row.label(), addr));

		if (row.instruction().at(0).str() == "DS" && row.dinfo().importance() == micro1::DebugInfoImportance::INFO) {
			auto storage_size = std::stoi(row.instruction().at(1).str(), nullptr, 10);
			for (micro1::M1Addr offset = 0; offset < storage_size; offset++) {
				addresses.emplace_back(addr + offset);
			}
			addr += storage_size;
		}
		else {
			addresses.emplace_back(addr++);
		}
	}

	return { addresses, labels };
}

std::uint16_t
extractUInt(TokenIterator head) {
	if ((*head).kind() == micro1::TokenKind::INTEGER)
		return std::stoi((*head).str());

	int base = 0;
	if ((*head).str() == "X")
		base = 16;
	if ((*head).str() == "B")
		base = 2;
	if ((*head).str() == "O")
		base = 8;

	return static_cast< std::uint16_t >(std::stoi((*(head + 2)).str(), nullptr, base) & 0xFFFF);
}

std::uint16_t
extractSInt(TokenIterator head) {
	if ((*head).kind() == micro1::TokenKind::SIGN) {
		if ((*head).str()[0] == '+')
			return extractSInt(head + 1);
		else
			return 256 - extractSInt(head + 1);
	}

	return extractUInt(head);
}

std::uint8_t
extractAddress(micro1::ReferenceAddress raddr, micro1::M1Addr current_address, std::map< std::string, micro1::M1Addr > labels) {
	return 0xFF & ((raddr.label() == "*" ? current_address : labels.at(raddr.label())) + raddr.offset());
}

std::tuple< std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t >
setRegister(micro1::Row row, std::vector< micro1::M1Addr > addresses, std::map< std::string, micro1::M1Addr > labels, std::int64_t index) {
	auto [op, ra, rb] = micro1::getEncoding(row.instruction().at(0).str());
	std::uint8_t nd = 0;

	switch (micro1::getNumberOfGroup(row.instruction().at(0).str())) {
	case micro1::InstGroup::GROUP1:
		if ((*(row.instruction().end() - 1)).kind() == micro1::TokenKind::RPAREN)
			ra = std::stoi((*(row.instruction().end() - 2)).str()) & 0x3;
		rb = std::stoi(row.instruction().at(1).str(), nullptr, 10) & 0x3;
		if ((*(row.instruction().begin() + 3)).kind() != micro1::TokenKind::LPAREN)
			nd = extractUInt(row.instruction().begin() + 3) & 0xFF;
		break;
	case micro1::InstGroup::GROUP2:
		rb = std::stoi(row.instruction().at(1).str(), nullptr, 10) & 0x3;
		nd = extractUInt(row.instruction().begin() + 3) & 0xFF;
		break;
	case micro1::InstGroup::GROUP3:
		rb = std::stoi(row.instruction().at(1).str(), nullptr, 10) & 0x3;
		nd = extractSInt(row.instruction().begin() + 3) & 0xFF;
		break;
	case micro1::InstGroup::GROUP4:
		ra = std::stoi((*(row.instruction().end() - 2)).str()) & 0x3;
		rb = std::stoi(row.instruction().at(1).str(), nullptr, 10) & 0x3;
		if (row.instruction().at(3).kind() != micro1::TokenKind::LPAREN)
			nd = extractSInt(row.instruction().begin() + 3) & 0xFF;
		break;
	case micro1::InstGroup::GROUP5:
		rb = std::stoi(row.instruction().at(1).str(), nullptr, 10) & 0x3;
		nd = extractAddress(row.raddr(), addresses.at(index), labels);
		break;
	case micro1::InstGroup::GROUP6:
		nd = extractAddress(row.raddr(), addresses.at(index), labels);
		break;
	case micro1::InstGroup::GROUP7:
		if (row.instruction().at(1).kind() == micro1::TokenKind::STRING) {
			if (row.instruction().at(1).str() == "CR")
				nd = 0;
			else if (row.instruction().at(1).str() == "CR")
				nd = 1;
		}
		else if (row.instruction().at(1).kind() == micro1::TokenKind::INTEGER) {
			nd = std::stoi(row.instruction().at(1).str());
		}
		break;
	case micro1::InstGroup::GROUP8:
		break;
	case micro1::InstGroup::GROUP9: {
		micro1::M1Word word;
		if (row.instruction().at(0).str() == "DC") {
			if (row.instruction().size() > 2 || row.instruction().at(1).kind() == micro1::TokenKind::INTEGER) {
				word = extractSInt(row.instruction().begin() + 1);
			}
			else if (row.instruction().at(1).kind() == micro1::TokenKind::CHARS) {
				word = static_cast<std::uint16_t>(row.instruction().at(1).str()[1]) << 8;
				word += static_cast<std::uint16_t>(row.instruction().at(1).str()[2]) & 0xFF;
			}
			else /* if (row.instruction().at(1).kind() == micro1::TokenKind::STRING) */ {
				word = labels.at(row.instruction().at(1).str());
			}
		}
		else if (row.instruction().at(0).str() == "DS") {
			word = std::stoi(row.instruction().at(1).str());
		}
		else /* if (row.instruction().at(0).str() == "ORG") */ {
			word = std::stoi(row.instruction().at(1).str(), nullptr, 16);
		}

		op = word >> 12;
		ra = (word >> 10) & 0x3;
		rb = (word >> 8) & 0x3;
		nd = word & 0xFF;

		break;
	}
	default:
		std::cerr << "FATAL ERROR: ";
		std::cerr << "FILE: " << __FILE__ << ", ";
		std::cerr << "LINE: " << __LINE__ << std::endl;
		std::cerr << "OPECODE: " << row.instruction().at(0).str() << std::endl;
		exit(2);
	}

	return { op, ra, rb, nd };
}

}

namespace micro1 {

/**
* @brief Write a listing file
* @param[in] rows parsed tokens
* @param[in] filename listing file name
*/
void
writeListingFile(const std::vector< Row > rows, const std::string filename) {
	std::ofstream ofs(filename);
	auto [addresses, labels] = ::calculateAddress(rows);

	if (!ofs) {
		std::cerr << "FILE " << filename << " CAN'T BE OPENED." << std::endl;
		exit(2);
	}

	std::int64_t index = 0;
	std::uint64_t num_of_errors = 0;
	for (auto row : rows) {
		if (row.instruction().size() == 0)
			continue;

		// print 'F'atal error or nothing
		if (row.dinfo().importance() == DebugInfoImportance::ERROR) {
			ofs << "F ";
			num_of_errors++;
		}
		else if (row.raddr().label() != "" && labels.find(row.raddr().label()) == labels.end()) {
			ofs << "F ";
			num_of_errors++;
		}
		else {
			ofs << "  ";
		}

		// print address & word data
		auto opecode = row.instruction().at(0).str();
		if (opecode == "TITLE" || opecode == "ORG" || opecode == "END") {
			for (int i = 0; i < 13; i++)
				ofs << ' ';
		}
		else {
			// address
			ofs << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << addresses.at(index);
			ofs << ' ';

			// word data
			if (row.dinfo().importance() != DebugInfoImportance::INFO) {
				for (int i = 0; i < 8; i++) {
					ofs << ' ';
				}
			}
			else {
				auto [op, ra, rb, nd] = ::setRegister(row, addresses, labels, index);
				if (row.instruction().at(0).str() == "DC") {
					ofs << std::hex << std::uppercase << static_cast<std::uint32_t>(op);
					ofs << std::hex << std::uppercase << static_cast<std::uint32_t>((ra << 2) + rb);
					ofs << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << static_cast<std::uint32_t>(nd) << "    ";
				}
				else if (row.instruction().at(0).str() == "DS") {
					ofs << "0000    " << row.instruction().at(0).line() << std::endl;

					for (int i = 0; i < (op << 12) + (ra << 10) + (rb << 8) + nd - 1; i++) {
						ofs << "  ";
						ofs << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << addresses.at(++index);
						ofs << " 0000" << std::endl;
					}

					continue;
				}
				else {
					ofs << std::hex << (op & 0xF);
					ofs << ' ';
					ofs << std::hex << (ra & 0x3) << (rb & 0x3);
					ofs << ' ';
					ofs << std::hex << std::setw(2) << std::setfill('0') << (nd & 0xF);
					ofs << ' ';
				}
			}
			index++;
		}

		// print a line of original program
		ofs << row.instruction().at(0).line() << std::endl;
	}

	// output number of errors
	ofs << std::endl << "THERE ";
	switch (num_of_errors) {
	case 0:
		ofs << "WERE NO ERRORS.";
		break;
	case 1:
		ofs << "WAS 1 ERROR.";
		break;
	default:
		ofs << "WERE" << num_of_errors << " ERRORS.";
		break;
	}
	ofs << std::endl << std::endl;

	// output labels
	ofs << "LABEL(S)" << std::endl;
	for (auto [key, value] : labels) {
		ofs << key << ": ";
		ofs << std::hex << std::setw(4) << std::setfill('0') << value;
		ofs << "    ";
	}
}

/**
* @brief Print syntax errors to standard error output
* @param[in] rows parsed tokens
*/
void
printSyntaxError(const std::vector< Row > rows) {
	for (auto row : rows) {
		if (row.dinfo().importance() == DebugInfoImportance::ERROR) {
			auto index = row.dinfo().index();
			auto number_of_row = row.instruction().at(0).row();
			auto number_of_column = row.instruction().at(index).column();
			
			// print "{row}:{column}: {message}"
			std::cerr << number_of_row << ":";
			std::cerr << number_of_column << ": ";
			std::cerr << row.dinfo().message() << std::endl;

			// print the line
			std::cerr << row.instruction().at(0).line() << std::endl;

			// print marks like "       ^^^^^"
			for (auto i = 0; i < number_of_column; i++) {
				std::cerr << " ";
			}
			for (auto i = 0; i < row.instruction().at(index).str().size(); i++) {
				std::cerr << "^";
			}
			std::cerr << std::endl;
		}
	}

	auto [addresses, labels] = ::calculateAddress(rows);
	
	for (auto row : rows) {
		if (row.raddr().label() == "")
			continue;

		if (labels.find(row.raddr().label()) == labels.end()) {
			auto number_of_row = row.instruction().at(0).row();
			
			// print "{row}:{message}"
			std::cerr << number_of_row << ": ";
			std::cerr << "Undefined reference to `" << row.raddr().label() << "`" << std::endl;
		}
	}
}

/**
* @brief Write a object file
* @param[in] rows parsed tokens
* @param[in] filename object file name
* @return bool If true, lines are syntactically correct
*/
bool
writeObjectFile(const std::vector< Row > rows, const std::string filename) {
	if (std::count_if(rows.begin(), rows.end(), [](auto row) { return row.dinfo().importance() == DebugInfoImportance::ERROR; }) != 0)
		return false;

	auto [addresses, labels] = ::calculateAddress(rows);
	for (auto row : rows) {
		if (row.raddr().label() == "")
			continue;

		if (labels.find(row.raddr().label()) == labels.end()) {
			return false;
		}
	}

	std::ofstream ofs(filename);
	if (!ofs) {
		std::cerr << "FILE " << filename << " CAN'T BE OPENED." << std::endl;
		exit(2);
	}

	std::int64_t index = 0;
	for (auto row : rows) {
		if (row.instruction().size() == 0)
			continue;

		auto opecode = row.instruction().at(0).str();
		if (opecode == "TITLE") {
			ofs << "MM " << row.instruction().at(1).str();
		}
		else if (opecode != "ORG" && opecode != "END") {
			ofs << std::endl;
			ofs << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << addresses.at(index);
			ofs << ' ';

			auto [op, ra, rb, nd] = ::setRegister(row, addresses, labels, index);
			M1Word word = op;
			word = (word << 2) + ra;
			word = (word << 2) + rb;
			word = (word << 8) + nd;
			if (row.instruction().at(0).str() == "DC") {
				ofs << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << word;
			}
			else if (row.instruction().at(0).str() == "DS") {
				ofs << "0000";

				for (int i = 0; i < word - 1; i++) {
					ofs << std::endl;
					ofs << std::hex << std::setw(4) << std::setfill('0') << std::uppercase << addresses.at(++index);
					ofs << " 0000";
				}

				continue;
			}
			else {
				ofs << std::hex << (op & 0xF);
				ofs << std::hex << ((ra & 0x3) << 2) + (rb & 0x3);
				ofs << std::hex << std::setw(2) << std::setfill('0') << (nd & 0xF);
			}

			index++;
		}
	}

	return true;
}

}
