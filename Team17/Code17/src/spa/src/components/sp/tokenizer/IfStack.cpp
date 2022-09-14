#include "IfStack.h"

IfStack::IfStack(SimpleToken parent) {
    this->parent = parent;
    this->expectElse = false;
}

void IfStack::put(SimpleToken token) {
    if (token.type == SpTokenType::TPROCEDURE) {
        throw std::invalid_argument("Received invalid SIMPLE code line " + token.statementNumber);
    }
    if (token.type == SpTokenType::TCLOSE) {
        std::vector<SimpleToken> children = parent.getChildren();
        SimpleToken stmtToken = SimpleToken(SpTokenType::TSTMTLIST, "", 0, NULL);
        stmtToken.setChildren(stmtList);
        children.push_back(stmtToken);
        parent.setChildren(children);
        expectElse = true;
    } else if (token.type == SpTokenType::TELSE) {
        if (!(expectElse)) {
            throw std::invalid_argument("Received unexpected else line " + token.statementNumber);
        }
        stmtList.clear();
    } else {
        stmtList.push_back(token);
    }
}
