#include "NestedStack.h"
#include <stdexcept>

NestedStack::NestedStack(SimpleToken parent) : parent(parent) {
}

void NestedStack::put(SimpleToken token) {
    if (token.type == SpTokenType::TPROCEDURE) {
        throw std::invalid_argument("Received invalid SIMPLE code line " + std::to_string(token.statementNumber));
    }
    if (token.type == SpTokenType::TCLOSE) {
        std::vector<SimpleToken> children = parent.getChildren();
        SimpleToken stmtToken = SimpleToken(SpTokenType::TSTMTLIST, "", 0, NULL);
        stmtToken.setChildren(stmtList);
        children.push_back(stmtToken);
        parent.setChildren(children);
    } else {
        stmtList.push_back(token);
    }
}

SimpleToken NestedStack::dump() {
    return parent;
}

bool NestedStack::isIf() {
    return false;
}