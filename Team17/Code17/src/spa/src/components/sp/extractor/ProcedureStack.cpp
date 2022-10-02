#include "ProcedureStack.h"
#include <stdexcept>

ProcedureStack::ProcedureStack(SimpleToken parent) : parent(parent) {
}

void ProcedureStack::put(SimpleToken token) {
    if (token.type == SpTokenType::TPROCEDURE) {
        throw std::invalid_argument("Received invalid SIMPLE code line " + std::to_string(token.statementNumber));
    }
    if (token.type == SpTokenType::TCLOSE) {
        if (follows.size() == 0) {
            throw std::invalid_argument("Received empty stmtlist" + std::to_string(parent.statementNumber));
        }
        //extractProcedure
    } else {
        follows.push_back(token);
    }
}

bool ProcedureStack::isIf() {
    return false;
}
