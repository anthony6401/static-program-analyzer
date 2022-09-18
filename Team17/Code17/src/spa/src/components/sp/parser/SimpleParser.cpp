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
    if (first == "}") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(SpTokenType::TCLOSE, code,
        SimpleParser::statementNumber, &SimpleParser::parseHolder);
        return token;
    } else if (tokens.at(1) == "=") {
        SimpleToken token = SimpleToken(SpTokenType::TASSIGN, code,
            SimpleParser::statementNumber, &SimpleParser::parseAssign);
        tokens.erase(tokens.begin() + 1);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "procedure") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(SpTokenType::TPROCEDURE, tokens.at(0),//need to change
            0, &SimpleParser::parseProcedure);
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
    } else if (first == "while") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(SpTokenType::TWHILE, code,
            SimpleParser::statementNumber, &SimpleParser::parseWhile);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "if") {
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(SpTokenType::TIF, code,
            SimpleParser::statementNumber, &SimpleParser::parseIf);
        SimpleParser::statementNumber++;
        return token;
    } else if (first == "else") {
        if (tokens.at(1) != "{") {
            throw std::invalid_argument("Received invalid SIMPLE code line " + std::to_string(SimpleParser::statementNumber));
        }
        tokens.erase(tokens.begin());
        SimpleToken token = SimpleToken(SpTokenType::TELSE, code,
            0, &SimpleParser::parseHolder);
        return token;
    } else {
        throw std::invalid_argument("Received invalid SIMPLE code line " + std::to_string(SimpleParser::statementNumber));
    }
}

void SimpleParser::parseProcedure(SimpleToken& procStmt, std::vector<std::string>& tokens,
    Extractor* extractor) {
    if (tokens.size() == 2 && tokens.at(1) == "{") {
        std::vector<SimpleToken> children;
        children.push_back(parseVariable(tokens.at(0)));
        procStmt.setChildren(children);
    }
    else {
        throw std::invalid_argument("Received invalid Procedure:Line " + std::to_string(procStmt.statementNumber));
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
        // extractor->extractPrintStmt(printStmt); //pass to extractor
    } else {
        throw std::invalid_argument("Received invalid Print:Line " + std::to_string(printStmt.statementNumber));
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
        // extractor->extractReadStmt(readStmt); //pass to extractor
    } else {
        throw std::invalid_argument("Received invalid Read:Line " + std::to_string(readStmt.statementNumber));
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
        throw std::invalid_argument("Received invalid Call:Line " + std::to_string(callStmt.statementNumber));
    }
}

void SimpleParser::parseWhile(SimpleToken& whileStmt, std::vector<std::string>& tokens,
    Extractor* extractor) {
    if (tokens.size() < 6 || tokens.back() != "{" || tokens.front() == "!") {
        throw std::invalid_argument("Received invalid While:Line " + std::to_string(whileStmt.statementNumber));
    }
    tokens.pop_back();
    SimpleToken stmtList = SimpleToken(SpTokenType::TCONDEXPR, "", 0, NULL);
    stmtList.setChildren(parseCondition(tokens));
    std::vector<SimpleToken> children;
    children.push_back(stmtList);
    whileStmt.setChildren(children);
}

void SimpleParser::parseIf(SimpleToken& ifStmt, std::vector<std::string>& tokens,
    Extractor* extractor) {
    if (tokens.size() < 7 || tokens.back() != "{" || tokens.front() == "!") {
        throw std::invalid_argument("Received invalid If:Line " + std::to_string(ifStmt.statementNumber));
    }
    tokens.pop_back();
    if (tokens.back() != "then") {
        throw std::invalid_argument("Received invalid If:Line " + std::to_string(ifStmt.statementNumber));
    }
    tokens.pop_back();
    SimpleToken stmtList = SimpleToken(SpTokenType::TCONDEXPR, "", 0, NULL);
    stmtList.setChildren(parseCondition(tokens));
    std::vector<SimpleToken> children;
    children.push_back(stmtList);
    ifStmt.setChildren(children);
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
        throw std::invalid_argument("Received invalid assign:Line " + std::to_string(assign.statementNumber));
    }
}

std::vector<SimpleToken> SimpleParser::parseCondition(std::vector<std::string> tokens) {
    if (tokens.front() != "(" || tokens.back() != ")") {
        throw std::invalid_argument("Received invalid condition. Missing brackets");
    }
    tokens.erase(tokens.begin());
    tokens.pop_back();
    std::string condition = SpUtils::join(tokens);
    if (condition.find("&&") != std::string::npos || condition.find("||") != std::string::npos) {
        int indice = 0;
        for (std::string token : tokens) {
            if (token == "&&" || token == "||") {
                if (SimpleValidator::isAndOrCenter(tokens, indice)) {
                    break;
                }
            }
            indice++;
        }
        if (indice == tokens.size()) {
            throw std::invalid_argument("Received invalid condition. invalid && or ||");
        }
        std::vector<std::string> firstTokens(tokens.begin(), tokens.begin() + indice);
        std::vector<SimpleToken> firstCondition = parseCondition(firstTokens);
        std::vector<std::string> secondTokens(tokens.begin() + indice + 1, tokens.end());
        std::vector<SimpleToken> secondCondition = parseCondition(secondTokens);
        firstCondition.insert(firstCondition.end(), secondCondition.begin(), secondCondition.end());
        return firstCondition;
    } else {
        if (tokens.front() == "!") {
            tokens.erase(tokens.begin());
            if (tokens.front() != "(" || tokens.back() != ")") {
                throw std::invalid_argument("Received invalid condition. Missing brackets");
            }
            tokens.erase(tokens.begin());
            tokens.pop_back();
        }
        return SimpleParser::parseRelExpr(tokens);
    }

}

std::vector<SimpleToken> SimpleParser::parseRelExpr(std::vector<std::string>& tokens) {
    int indice = 0;
    int endIndice = tokens.size();
    int comparatorCount = 0;
    std::regex comparators = std::regex("(==)|(!=)|(>=)|(<=)|[<>]");
    for (int i = 0; i < endIndice; i++) {
        if (std::regex_match(tokens.at(i), comparators)) {
            indice = i;
            comparatorCount++;
        }
    }
    if (comparatorCount != 1) {
        throw std::invalid_argument("Received invalid RelExpr");
    }
    std::vector<std::string> firstTokens(tokens.begin(), tokens.begin() + indice);
    SimpleToken firstRelFactor = parseExpr(firstTokens);
    std::vector<SimpleToken> firstContents = firstRelFactor.getChildren();
    std::vector<std::string> secondTokens(tokens.begin() + indice + 1, tokens.end());
    SimpleToken secondRelFactor = parseExpr(secondTokens);
    std::vector<SimpleToken> secondContents = secondRelFactor.getChildren();
    firstContents.insert(firstContents.end(), secondContents.begin(), secondContents.end());
    return firstContents;
}

SimpleToken SimpleParser::parseExpr(std::vector<std::string>& tokens) {
    ExprStack stack = ExprStack();
    if (tokens.size() == 0) {
        throw std::invalid_argument("Received invalid expression. No tokens ");
    }
    for (std::string i : tokens) {
        stack.put(i);
    }
    if (stack.valid()) {
        SimpleToken expr = SimpleToken(SpTokenType::TEXPR, "", 0, NULL);
        expr.setChildren(stack.get());
        return expr;
    } else {
        throw std::invalid_argument("Received invalid expression. Wrong tokens. ");
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
