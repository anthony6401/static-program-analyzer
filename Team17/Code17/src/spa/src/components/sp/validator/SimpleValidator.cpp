#include <locale>
#include <regex>
#include <stack>
#include "SimpleValidator.h"
#include "./states/ValidatorState.h"
#include "./states/ProgramState.h"
#include "../utils/SpUtils.h"

SimpleValidator::SimpleValidator() {
    state = new ProgramState(this);
}

bool SimpleValidator::validCode() {
    return state->validCode();
}

void SimpleValidator::close() {
    state->close();
}

void SimpleValidator::setState(ValidatorState* newState) {
    parentStates.push(state);
    state = newState;
}

void SimpleValidator::validLine(SpTokenType type, int statementNumber) {
    state->validLine(type, statementNumber);
}

bool SimpleValidator::validateVariable(std::string& token) {
    std::regex constant = std::regex("[a-zA-Z][a-zA-Z0-9]*");
    return std::regex_match(token, std::regex(constant));
}

bool SimpleValidator::validateConstant(std::string& token) {
    std::regex numeric = std::regex("(0|[1-9][0-9]*)");
    return std::regex_match(token, numeric);
}

bool SimpleValidator::validateExprOpr(std::string& token) {
    std::regex operand = std::regex("([+-/*%])");
    return std::regex_match(token, operand);
}

bool SimpleValidator::isAndOrCenter(std::vector<std::string> tokens, int connectorPosition) {
    return (SpUtils::findOpenBracket(tokens, connectorPosition - 1) == 0 &&
        SpUtils::findCloseBracket(tokens, connectorPosition + 1) == tokens.size() - 1);
}

bool SimpleValidator::isValidCalls(std::multimap<std::string, std::string> &callProcedures,
    std::set<std::string> &procedures) {
    std::map<std::string, bool> visited;
    for (std::string procedure : procedures) {
        visited.insert(std::pair<std::string, bool>(procedure, false));
    }
    for (const auto& procedure : procedures) {
        if (SimpleValidator::isCyclic(callProcedures, visited, procedure)) {
            return false;
        }
    }
    return true;
}

bool SimpleValidator::isCyclic(std::multimap<std::string, std::string>& callProcedures,
    std::map<std::string, bool> visited, std::string procedure) {
    std::map<std::string, bool>::iterator visit = visited.find(procedure);
    if (visit == visited.end()) {
        throw std::invalid_argument("Called invalid procedure name" + procedure);
    }
    if (!(visit->second)) {
        visit->second = true;
        auto range = callProcedures.equal_range(procedure);
        for (auto i = range.first; i != range.second; ++i) {
            if (SimpleValidator::isCyclic(callProcedures, visited, i->second)) {
                return true;
            }
        }
        return false;
    }
    return true;
}