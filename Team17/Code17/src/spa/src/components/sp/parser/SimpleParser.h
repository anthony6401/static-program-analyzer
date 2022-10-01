#pragma once

#include <string>
#include "../SimpleToken.h"
#include "../extractor/Extractor.h"

class SimpleParser {
    public:
        int statementNumber;
        SimpleParser(Extractor* client);
        void parseCode(std::string code);
        SimpleToken parseLine(std::string code);
        void parseProcedure(SimpleToken& printStmt, std::vector<std::string>& tokens);
        void parsePrint(SimpleToken& printStmt, std::vector<std::string>& tokens);
        void parseRead(SimpleToken& readStmt, std::vector<std::string>& tokens);
        void parseCall(SimpleToken& readStmt, std::vector<std::string>& tokens);
        void parseWhile(SimpleToken& readStmt, std::vector<std::string>& tokens);
        void parseIf(SimpleToken& readStmt, std::vector<std::string>& tokens);
        void parseAssign(SimpleToken& readStmt, std::vector<std::string>& tokens);
        std::vector<SimpleToken> parseCondition(std::vector<std::string> tokens);
        std::vector<SimpleToken> parseRelExpr(std::vector<std::string>& tokens);
        SimpleToken parseExpr(std::vector<std::string>& tokens);
        SimpleToken parseVariable(std::string& token);
        SimpleToken parseConstant(std::string& token);

    private:
        Extractor* extractor;

};
