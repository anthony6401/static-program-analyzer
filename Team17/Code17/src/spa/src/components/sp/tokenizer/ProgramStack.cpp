#include "ProgramStack.h"

ProgramStack::ProgramStack(SimpleToken parent) : parent(parent) {

}

void ProgramStack::put(SimpleToken token) {
    if (token.type == SpTokenType::TPROCEDURE) {
        stmtList.push_back(token);
    }
    else {
        throw std::invalid_argument("Received invalid SIMPLE code line " + std::to_string(token.statementNumber));
    }
}

SimpleToken ProgramStack::dump() {
    parent.setChildren(stmtList);
    return parent;
}