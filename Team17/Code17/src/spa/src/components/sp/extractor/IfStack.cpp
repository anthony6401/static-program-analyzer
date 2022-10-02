#include "IfStack.h"
#include <stdexcept>

IfStack::IfStack(SimpleToken parent) : parent(parent) {
    this->expectElse = true;
}

void IfStack::put(SimpleToken token) {
    if (token.type == SpTokenType::TPROCEDURE) {
        throw std::invalid_argument("Received invalid SIMPLE code line " + std::to_string(token.statementNumber));
    }
    if (token.type == SpTokenType::TCLOSE) {
        if (follows.size() == 0) {
            throw std::invalid_argument("Received empty stmtlist" + std::to_string(parent.statementNumber));
        }
        //extractIf
    } else if (token.type == SpTokenType::TELSE) {
        if (!(expectElse)) {
            throw std::invalid_argument("Received unexpected else line " + std::to_string(token.statementNumber));
        }
        expectElse = false;
        ifFollows = follows;
        follows.clear();
    } else {
        follows.push_back(token);
    }
}

bool IfStack::isIf() {
    return expectElse;
}
