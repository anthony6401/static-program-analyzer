#include "SimpleParser.h"
#include "../validator/SimpleValidator.h"
#include "../SimpleToken.h"

int SimpleParser::statementNumber = 1;

SimpleToken SimpleParser::parseLine(std::vector<std::string>& tokens, std::string code) {
    std::string first = tokens.front();
    if (first == "procedure") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(TokenType::TPROCEDURE, code,
            SimpleParser::statementNumber, &SimpleParser::parseRead);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "read") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(TokenType::TREAD, code,
            SimpleParser::statementNumber, &SimpleParser::parseRead);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "print") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(TokenType::TPRINT, code,
            SimpleParser::statementNumber, &SimpleParser::parsePrint);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "call") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(TokenType::TCALL, code,
            SimpleParser::statementNumber, &SimpleParser::parseRead);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "while") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(TokenType::TWHILE, code,
            SimpleParser::statementNumber, &SimpleParser::parseRead);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "else") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(TokenType::TELSE, code,
            0, &SimpleParser::parseRead);
        return token;
    } else if (first == "}") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(TokenType::TCLOSE, code,
            SimpleParser::statementNumber, &SimpleParser::parseRead);
        SimpleParser::statementNumber++;
        return token;
    } else {
        if (tokens.at(1) == "=") {
            SimpleToken token = SimpleToken(TokenType::TASSIGN, code,
                SimpleParser::statementNumber, &SimpleParser::parseRead);
            SimpleParser::statementNumber++;
            return token;
        }
        throw std::invalid_argument("Received invalid SIMPLE code line " + SimpleParser::statementNumber);
    }
}

void SimpleParser::parsePrint(SimpleToken& printStmt, std::vector<std::string>& tokens) {
    if (tokens.size() == 2 && tokens.at(1) != ";") {
        std::vector<SimpleToken*> children;
        children.push_back(&parseVariable(tokens.at(0)));
        printStmt.setChildren(children);
        //pass to extractor
    } else {
        throw std::invalid_argument("Received invalid Print:Line " + printStmt.statementNumber);
    }
}

void SimpleParser::parseRead(SimpleToken& readStmt, std::vector<std::string>& tokens) {
    if (tokens.size() == 2 && tokens.at(1) != ";") {
        std::vector<SimpleToken*> children;
        children.push_back(&parseVariable(tokens.at(0)));
        readStmt.setChildren(children);
        //pass to extractor
    }
    else {
        throw std::invalid_argument("Received invalid Print:Line " + readStmt.statementNumber);
    }
}

SimpleToken SimpleParser::parseVariable(std::string token) {
    if (SimpleValidator::validateLexical(token)) {
        return SimpleToken(TokenType::TVARIABLE, token, 0, NULL);
    } else {
        throw std::invalid_argument("Received invalid variable " + token);
    }
}