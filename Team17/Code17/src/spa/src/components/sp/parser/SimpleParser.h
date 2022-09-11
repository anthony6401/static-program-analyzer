#pragma once

#include <string>
#include "../SimpleToken.h"
#include "../extractor/Extractor.h"

class SimpleParser {
    public:
        static int statementNumber;
        static SimpleToken parseLine(std::vector<std::string>& tokens, std::string code);
        static void parseProcedure(SimpleToken& printStmt, std::vector<std::string>& tokens,
            Extractor* extractor);
        static void parsePrint(SimpleToken& printStmt, std::vector<std::string>& tokens,
            Extractor* extractor);
        static void parseRead(SimpleToken& readStmt, std::vector<std::string>& tokens,
            Extractor* extractor);
        static void parseCall(SimpleToken& readStmt, std::vector<std::string>& tokens,
            Extractor* extractor);
        static void parseAssign(SimpleToken& readStmt, std::vector<std::string>& tokens,
            Extractor* extractor);
        static SimpleToken parseExpr(std::vector<std::string>& tokens);
        static SimpleToken parseVariable(std::string& token);
        static SimpleToken parseConstant(std::string& token);
        static void parseHolder(SimpleToken& printStmt, std::vector<std::string>& tokens,
            Extractor* extractor);

        static SPClient client; // to be changed
        static Extractor* extractor;
};
