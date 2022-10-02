#include "ProcedureStack.h"
#include <stdexcept>

ProcedureStack::ProcedureStack(SimpleToken parent, Extractor* context) : parent(parent) {
    this->context = context;
}

void ProcedureStack::close(int statementNumber) {
    //extractFollows(follows)
    //extractParent(stack.value, follows, statementNumber)
    //mergeStack(lastStack, this)
    //modifies
    //uses
    context->procedures.insert(parent.value, this);
}

bool ProcedureStack::isIf() {
    return false;
}
