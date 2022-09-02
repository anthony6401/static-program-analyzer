#include "SimpleParser.h"
#include "../SimpleToken.h"

int SimpleParser::statementNumber = 1;

SimpleToken SimpleParser::parseLine(std::vector<std::string>& tokens) {
    std::string first = tokens.front();
    if (first == "procedure") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(TokenType::TPROCEDURE, tokens, SimpleParser::statementNumber);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "read") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(TokenType::TREAD, tokens, SimpleParser::statementNumber);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "print") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(TokenType::TPRINT, tokens, SimpleParser::statementNumber);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "call") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(TokenType::TCALL, tokens, SimpleParser::statementNumber);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "while") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(TokenType::TWHILE, tokens, SimpleParser::statementNumber);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "else") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(TokenType::TELSE, tokens, 0);
        return token;
    } else if (first == "}") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(TokenType::TCLOSE, tokens, SimpleParser::statementNumber);
        SimpleParser::statementNumber++;
        return token;
    } else {
        if (tokens.at(1) == "=") {
            SimpleToken token = SimpleToken(TokenType::TASSIGN, tokens, SimpleParser::statementNumber);
            SimpleParser::statementNumber++;
            return token;
        }
        throw std::invalid_argument("Received invalid SIMPLE code line " + SimpleParser::statementNumber);
    }
}

void SimpleParser::initializeParser() {
    SimpleParser::statementNumber = 1;
}