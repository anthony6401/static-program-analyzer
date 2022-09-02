#pragma once

#include <string>
#include <stdexcept>
#include "../SimpleToken.h"

class SimpleParser {
    public:
        static SimpleToken parseLine(std::vector<std::string>& tokens);
        static void initializeParser();
        static int statementNumber;

};
