#include <stack>
#include <stdexcept>
#include "SimpleParser.h"
#include "../validator/SimpleValidator.h"
#include "../SimpleToken.h"
#include "../utils/SpUtils.h"
#include "../tokenizer/ExprStack.h"


/// <summary>
/// SIMPLE statement number that is currently being processed
/// </summary>
int SimpleParser::statementNumber = 1;

/// <summary>
/// Identifies type of code line and returns a SimpleToken of it
/// </summary>
/// <param name="tokens">code of line that has been split into tokens</param>
/// <param name="code">original line of code before splitting</param>
/// <returns>SimpleToken identifying line type and value containing code</returns>
SimpleToken SimpleParser::parseLine(std::vector<std::string>& tokens, std::string code) {
    std::string first = tokens.front();
    if (first == "procedure") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(SpTokenType::TPROCEDURE, code,
            SimpleParser::statementNumber, &SimpleParser::parseProcedure);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "read") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(SpTokenType::TREAD, code,
            SimpleParser::statementNumber, &SimpleParser::parseRead);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "print") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(SpTokenType::TPRINT, code,
            SimpleParser::statementNumber, &SimpleParser::parsePrint);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "call") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(SpTokenType::TCALL, code,
            SimpleParser::statementNumber, &SimpleParser::parseCall);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "while") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(SpTokenType::TWHILE, code,
            SimpleParser::statementNumber, &SimpleParser::parseHolder);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "else") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(SpTokenType::TELSE, code,
            0, &SimpleParser::parseHolder);
        return token;
    } else if (first == "}") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(SpTokenType::TCLOSE, code,
            SimpleParser::statementNumber, &SimpleParser::parseHolder);
        SimpleParser::statementNumber++;
        return token;
    } else {
        if (tokens.at(1) == "=") {
            SimpleToken token = SimpleToken(SpTokenType::TASSIGN, code,
                SimpleParser::statementNumber, &SimpleParser::parseAssign);
            tokens.erase(tokens.begin() + 1);
            SimpleParser::statementNumber++;
            return token;
        }
        throw std::invalid_argument("Received invalid SIMPLE code line " + SimpleParser::statementNumber);
    }
}

void SimpleParser::parseProcedure(SimpleToken& procStmt, std::vector<std::string>& tokens,
    Extractor* extractor) {
    if (tokens.size() == 2 && tokens.at(1) == ";") {
        std::vector<SimpleToken> children;
        children.push_back(parseVariable(tokens.at(0)));
        procStmt.setChildren(children);
    }
    else {
        throw std::invalid_argument("Received invalid Procedure:Line " + procStmt.statementNumber);
    }
}

/// <summary>
/// Process print stmts for design extractor
/// </summary>
/// <param name="printStmt">SimpleToken of TPRINT type</param>
/// <param name="tokens">parameters for print statement</param>
void SimpleParser::parsePrint(SimpleToken& printStmt, std::vector<std::string>& tokens,
        Extractor* extractor) {
    if (tokens.size() == 2 && tokens.at(1) == ";") {
        std::vector<SimpleToken> children;
        children.push_back(parseVariable(tokens.at(0)));
        printStmt.setChildren(children);
        extractor->extractPrint(printStmt, tokens); //pass to extractor
    } else {
        throw std::invalid_argument("Received invalid Print:Line " + printStmt.statementNumber);
    }
}

/// <summary>
/// Process read stmts for design extractor
/// </summary>
/// <param name="printStmt">SimpleToken of TREAD type</param>
/// <param name="tokens">parameters for read statement</param>
void SimpleParser::parseRead(SimpleToken& readStmt, std::vector<std::string>& tokens,
        Extractor* extractor) {
    if (tokens.size() == 2 && tokens.at(1) == ";") {
        std::vector<SimpleToken> children;
        children.push_back(parseVariable(tokens.at(0)));
        readStmt.setChildren(children);
        extractor->extractRead(readStmt, tokens); //pass to extractor
    } else {
        throw std::invalid_argument("Received invalid Read:Line " + readStmt.statementNumber);
    }
}

void SimpleParser::parseCall(SimpleToken& callStmt, std::vector<std::string>& tokens,
    Extractor* extractor) {
    if (tokens.size() == 2 && tokens.at(1) == ";") {
        std::vector<SimpleToken> children;
        children.push_back(parseVariable(tokens.at(0)));
        callStmt.setChildren(children);
    }
    else {
        throw std::invalid_argument("Received invalid Call:Line " + callStmt.statementNumber);
    }
}

void SimpleParser::parseAssign(SimpleToken& assign, std::vector<std::string>& tokens,
    Extractor* extractor) {
    if (SimpleValidator::validateVariable(tokens.front()) && tokens.back() == ";") {
        tokens.pop_back();
        std::vector<SimpleToken> children;
        children.push_back(SimpleToken(SpTokenType::TVARIABLE, tokens.front(), 0, NULL));
        tokens.erase(tokens.begin());
        children.push_back(SimpleParser::parseExpr(tokens));
        assign.setChildren(children);
    } else {
        throw std::invalid_argument("Received invalid assign:Line " + assign.statementNumber);
    }
}

SimpleToken SimpleParser::parseExpr(std::vector<std::string>& tokens) {
    ExprStack stack = ExprStack();
    if (tokens.size() == 0) {
        throw std::invalid_argument("Received invalid expression ");
    }
    for (std::string i : tokens) {
        stack.put(i);
    }
    if (stack.valid()) {
        SimpleToken expr = SimpleToken(SpTokenType::TEXPR, "", 0, NULL);
        expr.setChildren(stack.get());
        return expr;
    } else {
        throw std::invalid_argument("Received invalid expression ");
    }
}

/// <summary>
/// Process variable for design extractor
/// </summary>
/// <param name="token">string to validate if valid variable</param>
/// <returns>SimpleToken of TVARIABLE with variable name as value</returns>
SimpleToken SimpleParser::parseVariable(std::string& token) {
    if (SimpleValidator::validateVariable(token)) {
        return SimpleToken(SpTokenType::TVARIABLE, token, 0, NULL);
    } else {
        throw std::invalid_argument("Received invalid variable " + token);
    }
}

SimpleToken SimpleParser::parseConstant(std::string& token) {
    if (SimpleValidator::validateConstant(token)) {
        return SimpleToken(SpTokenType::TCONSTANT, token, 0, NULL);
    } else {
        throw std::invalid_argument("Received invalid constant " + token);
    }
}

void SimpleParser::parseHolder(SimpleToken& printStmt, std::vector<std::string>& tokens,
    Extractor* extractor) {
}
