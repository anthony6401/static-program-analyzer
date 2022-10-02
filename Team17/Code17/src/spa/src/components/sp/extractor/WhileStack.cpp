#include "WhileStack.h"
#include <stdexcept>

WhileStack::WhileStack(SimpleToken parent) : parent(parent) {
}

void WhileStack::put(SimpleToken token) {
    if (token.type == SpTokenType::TPROCEDURE) {
        throw std::invalid_argument("Received invalid SIMPLE code line " + std::to_string(token.statementNumber));
    }
    if (token.type == SpTokenType::TCLOSE) {
        if (follows.size() == 0) {
            throw std::invalid_argument("Received empty stmtlist" + std::to_string(parent.statementNumber));
        }
        //extractWhile
    }
    else {
        follows.push_back(token);
    }
}

bool WhileStack::isIf() {
    return false;
}
