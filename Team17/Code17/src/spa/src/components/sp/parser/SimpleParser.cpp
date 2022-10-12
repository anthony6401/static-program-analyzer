#include <stack>
#include <stdexcept>
#include "SimpleParser.h"
#include "../SimpleToken.h"
#include "../utils/SpUtils.h"
#include "../tokenizer/SimpleTokenizer.h"
#include "../parser/ExprStack/ExprStack.h"
#include "../validator/states/NestedState.h"
#include "../validator/states/IfState.h"
#include "../validator/states/ElseState.h"
#include "../validator/states/ProgramState.h"


SimpleParser::SimpleParser(Extractor* extractor) {
    this->extractor = extractor;
    this->validator = SimpleValidator();
    this->statementNumber = 1;
}

void SimpleParser::parseCode(std::string code) {
    std::vector<std::string> codeLines = SimpleTokenizer::tokenizeCode(code);
    if (codeLines.empty()) {
        throw std::invalid_argument("Received invalid SIMPLE code");
    }

    for (std::string line : codeLines) {
        SimpleParser::parseLine(line);
    }
    validator.isValidCode();
    validator.isValidCalls(callProcedures, procedures);
    extractor->endOfParser(callProcedures);
}

void SimpleParser::parseLine(std::string code) {
    std::vector<std::string> tokens = SimpleTokenizer::tokenizeLine(code);
    std::string first = tokens.front();
    if (first == "}") {
        tokens.erase(tokens.begin());
        validator.close();
        extractor->close(statementNumber);
    } else if (tokens.size() < 2) {
        throw std::invalid_argument("Received invalid SIMPLE code line not enough tokens::" + std::to_string(statementNumber));
    }
    if (tokens.at(1) == "=") {
        tokens.erase(tokens.begin() + 1);
        validator.validateLine(SpTokenType::TASSIGN, statementNumber);
        parseAssign(tokens);
    } else if (first == "procedure") {
        tokens.erase(tokens.begin());
        validator.validateLine(SpTokenType::TPROCEDURE, statementNumber);
        parseProcedure(tokens);
    } else if (first == "call") {
        tokens.erase(tokens.begin());
        validator.validateLine(SpTokenType::TCALL, statementNumber);
        parseCall(tokens);
    } else if (first == "read") {
        tokens.erase(tokens.begin());
        validator.validateLine(SpTokenType::TREAD, statementNumber);
        parseRead(tokens);
    } else if (first == "print") {
        tokens.erase(tokens.begin());
        validator.validateLine(SpTokenType::TPRINT, statementNumber);
        parsePrint(tokens);
    } else if (first == "while") {
        tokens.erase(tokens.begin());
        validator.validateLine(SpTokenType::TWHILE, statementNumber);
        parseWhile(tokens);
    } else if (first == "if") {
        tokens.erase(tokens.begin());
        validator.validateLine(SpTokenType::TIF, statementNumber);
        parseIf(tokens);
    } else if (first == "else") {
        parseElse(tokens);
        validator.validateLine(SpTokenType::TELSE, statementNumber);
        validator.close();
    } else {
        throw std::invalid_argument("Received invalid SIMPLE code line " + std::to_string(statementNumber));
    }
}

void SimpleParser::parseProcedure(std::vector<std::string>& tokens) {
    if (tokens.size() == 2 && tokens.at(1) == "{") {
        std::string procedureName = parseVariable(tokens.at(0));
        if (!(validator.isValidProcedure(procedureName))) {
            throw std::invalid_argument("Received invalid or duplicate Procedure:Line " + std::to_string(statementNumber));
        }
        SimpleToken procedureToken = SimpleToken(SpTokenType::TPROCEDURE, procedureName, 0);
        this->currentProcedure = procedureName;
        this->procedures.insert(procedureName);
        validator.setState(new NestedState(&validator));
        this->extractor->extractProcedure(procedureToken);
    }
    else {
        throw std::invalid_argument("Received invalid Procedure:Line " + std::to_string(statementNumber));
    }
}

void SimpleParser::parseCall(std::vector<std::string>& tokens) {
    if (tokens.size() == 2 && tokens.at(1) == ";") {
        std::string procedure = parseVariable(tokens.at(0));
        SimpleToken callToken = SimpleToken(SpTokenType::TCALL, procedure, statementNumber);
        statementNumber++;
        extractor->extractCall(callToken, procedure);
        this->callProcedures.insert(std::pair<std::string, std::string>(procedure, this->currentProcedure));
    }
    else {
        throw std::invalid_argument("Received invalid Call:Line " + std::to_string(statementNumber));
    }
}

void SimpleParser::parsePrint(std::vector<std::string>& tokens) {
    if (tokens.size() == 2 && tokens.at(1) == ";") {
        SimpleToken printToken = SimpleToken(SpTokenType::TPRINT, parseVariable(tokens.at(0)), statementNumber);
        statementNumber++;
        extractor->extractPrint(printToken);
    } else {
        throw std::invalid_argument("Received invalid Print:Line " + std::to_string(statementNumber));
    }
}

void SimpleParser::parseRead(std::vector<std::string>& tokens) {
    if (tokens.size() == 2 && tokens.at(1) == ";") {
        SimpleToken readToken = SimpleToken(SpTokenType::TREAD, parseVariable(tokens.at(0)), statementNumber);
        statementNumber++;
        this->extractor->extractRead(readToken);
    } else {
        throw std::invalid_argument("Received invalid Read:Line " + std::to_string(statementNumber));
    }
}

void SimpleParser::parseWhile(std::vector<std::string>& tokens) {
    if (tokens.size() < 6 || tokens.back() != "{") {
        throw std::invalid_argument("Received invalid While:Line " + std::to_string(statementNumber));
    }
    tokens.pop_back();
    SimpleToken whileToken = SimpleToken(SpTokenType::TWHILE, "", statementNumber);
    statementNumber++;
    whileToken.setChildren(parseCondition(tokens));
    validator.setState(new NestedState(&validator));
    extractor->extractWhile(whileToken);
}

void SimpleParser::parseIf(std::vector<std::string>& tokens) {
    if (tokens.size() < 7 || tokens.back() != "{") {
        throw std::invalid_argument("Received invalid If:Line " + std::to_string(statementNumber));
    }
    tokens.pop_back();
    if (tokens.back() != "then") {
        throw std::invalid_argument("Received invalid If:Line " + std::to_string(statementNumber));
    }
    tokens.pop_back();
    SimpleToken ifToken = SimpleToken(SpTokenType::TIF, "", statementNumber);
    statementNumber++;
    ifToken.setChildren(parseCondition(tokens));
    validator.setState(new IfState(&validator));
    extractor->extractIf(ifToken);
}

void SimpleParser::parseElse(std::vector<std::string>& tokens) {
    if (tokens.size() != 2) {
        throw std::invalid_argument("Received invalid Else:Line " + std::to_string(statementNumber));
    } else if (tokens.at(1) != "{") {
        throw std::invalid_argument("Received invalid Else:Line " + std::to_string(statementNumber));
    }
    tokens.erase(tokens.begin());
}

void SimpleParser::parseAssign(std::vector<std::string>& tokens) {
    if (SimpleValidator::isValidVariable(tokens.front()) && tokens.back() == ";") {
        tokens.pop_back();
        std::vector<SimpleToken> children;
        children.push_back(SimpleToken(SpTokenType::TVARIABLE, tokens.front(), 0));
        tokens.erase(tokens.begin());
        children.push_back(SimpleParser::parseExpr(tokens));
        SimpleToken assignToken = SimpleToken(SpTokenType::TASSIGN, "", statementNumber);
        statementNumber++;
        assignToken.setChildren(children);
        extractor->extractAssign(assignToken);
    } else {
        throw std::invalid_argument("Received invalid assign:Line " + std::to_string(statementNumber));
    }
}

std::vector<SimpleToken> SimpleParser::parseCondition(std::vector<std::string> tokens) {
    if (tokens.front() != "(" || tokens.back() != ")") {
        throw std::invalid_argument("Received invalid condition. Missing brackets");
    }
    tokens.erase(tokens.begin());
    tokens.pop_back();
    while (tokens.front() == "!") {
        tokens.erase(tokens.begin());
        if (tokens.front() != "(" || tokens.back() != ")") {
            throw std::invalid_argument("Received invalid condition. Missing brackets");
        }
        tokens.erase(tokens.begin());
        tokens.pop_back();
    }
    std::string condition = SpUtils::join(tokens);
    if (condition.find("&&") != std::string::npos || condition.find("||") != std::string::npos) {
        int indice = 0;
        for (std::string token : tokens) {
            if (token != "&&" && token != "||") {
                indice++;
                continue;
            }
            if (SimpleValidator::isAndOrCenter(tokens, indice)) {
                break;
            } else {
                indice++;
            }

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
        throw std::invalid_argument("Received invalid RelExpr missing comparator");
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
        SimpleToken expr = SimpleToken(SpTokenType::TEXPR, "", 0);
        expr.setChildren(stack.get());
        return expr;
    } else {
        throw std::invalid_argument("Received invalid expression. Wrong tokens. ");
    }
}

std::string SimpleParser::parseVariable(std::string& token) {
    if (SimpleValidator::isValidVariable(token)) {
        return token;
    } else {
        throw std::invalid_argument("Received invalid variable " + token);
    }
}

std::string SimpleParser::parseConstant(std::string& token) {
    if (SimpleValidator::isValidConstant(token)) {
        return token;
    } else {
        throw std::invalid_argument("Received invalid constant " + token);
    }
}
