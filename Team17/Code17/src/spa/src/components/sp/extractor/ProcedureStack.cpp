#include "ProcedureStack.h"
#include <stdexcept>
#include "Extractor.h"

ProcedureStack::ProcedureStack(SimpleToken parent, Extractor* context) : parent(parent) {
    this->context = context;
}

void ProcedureStack::close(int statementNumber) {
    //extractFollows(follows)
    //extractParent(stack.value, follows, statementNumber)
    //mergeStack(lastStack, this)
    //modifies
    //uses
    context->procedures.insert(std::pair<std::string, ProcedureStack*>(parent.value, this));
}

bool ProcedureStack::isIf() {
    return false;
}
