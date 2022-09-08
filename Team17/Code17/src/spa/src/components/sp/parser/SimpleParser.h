#pragma once

#include <string>
#include <stdexcept>
#include "../SimpleToken.h"
#include "../extractor/Extractor.h"

class SimpleParser {
    public:
        static int statementNumber;
        static SimpleToken parseLine(std::vector<std::string>& tokens, std::string code);
        static void parsePrint(SimpleToken& printStmt, std::vector<std::string>& tokens,
            Extractor* extractor, SPClient* client);
        static void parseRead(SimpleToken& readStmt, std::vector<std::string>& tokens,
            Extractor* extractor, SPClient* client);
        static SimpleToken parseVariable(std::string& token);
        static void parseHolder(SimpleToken& printStmt, std::vector<std::string>& tokens,
            Extractor* extractor, SPClient* client);

        static SPClient client; // to be changed
        static Extractor* extractor;
};
