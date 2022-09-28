#include "ProcedureStack.h"
#include <stdexcept>

ProcedureStack::ProcedureStack(SimpleToken parent) : parent(parent) {
}

void ProcedureStack::put(SimpleToken token) {
    if (token.type == SpTokenType::TPROCEDURE) {
        throw std::invalid_argument("Received invalid SIMPLE code line " + std::to_string(token.statementNumber));
    }
    if (token.type == SpTokenType::TCLOSE) {
        std::vector<SimpleToken> children = parent.getChildren();
        SimpleToken stmtToken = SimpleToken(SpTokenType::TSTMTLIST, "", 0);
        stmtToken.setChildren(stmtList);
        children.push_back(stmtToken);
        parent.setChildren(children);
    } else {
        stmtList.push_back(token);
    }
}

SimpleToken ProcedureStack::dump() {
    if (stmtList.size() == 0) {
        throw std::invalid_argument("Received empty stmtlist" + std::to_string(parent.statementNumber));
    }
    return parent;
}

bool ProcedureStack::isIf() {
    return false;
}
