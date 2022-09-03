#pragma once

#include <string>
#include <stdexcept>
#include "../SimpleToken.h"

class SimpleParser {
    public:
        static int statementNumber;
        static SimpleToken parseLine(std::vector<std::string>& tokens, std::string code);
        static void parsePrint(SimpleToken& printStmt, std::vector<std::string>& tokens);
        static void parseRead(SimpleToken& readStmt, std::vector<std::string>& tokens);
        static SimpleToken parseVariable(std::string& token);

};
