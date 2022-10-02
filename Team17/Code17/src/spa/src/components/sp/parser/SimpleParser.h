#pragma once

#include <string>
#include "../SimpleToken.h"
#include "../extractor/Extractor.h"

class SimpleParser {
    public:
        int statementNumber;
        SimpleParser(Extractor* client);
        void parseCode(std::string code);
        void parseLine(std::string code);
        void parseProcedure(std::vector<std::string>& tokens);
        void parseCall(std::vector<std::string>& tokens);
        void parsePrint(std::vector<std::string>& tokens);
        void parseRead(std::vector<std::string>& tokens);
        void parseWhile(std::vector<std::string>& tokens);
        void parseIf(std::vector<std::string>& tokens);
        void parseAssign(std::vector<std::string>& tokens);
        std::vector<SimpleToken> parseCondition(std::vector<std::string> tokens);
        std::vector<SimpleToken> parseRelExpr(std::vector<std::string>& tokens);
        SimpleToken parseExpr(std::vector<std::string>& tokens);
        std::string parseVariable(std::string& token);
        std::string parseConstant(std::string& token);

    private:
        Extractor* extractor;

};
