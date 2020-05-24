#ifndef LEXER_H
#define LEXER_H

#include "token.h"

#include <fstream>
#include <vector>

namespace micro1 {

std::vector< Token > tokenize(std::ifstream& ifs);

}

#endif // LEXER_H