#ifndef OUTPUT_H
#define OUTPUT_H

#include "parser.h"

namespace micro1 {

void writeListingFile(const std::vector< Row > lines, const std::string filename);
void printSyntaxError(const std::vector< Row > lines);
bool writeObjectFile(const std::vector< Row > lines, const std::string filename);

}

#endif // OUTPUT_H