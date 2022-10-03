#include "WhileStack.h"
#include <stdexcept>

WhileStack::WhileStack(SimpleToken parent, Extractor* context) : parent(parent) {
    this->context = context;
}

void WhileStack::close(int statementNumber) {
//extractFollows(follows)
//extractParent(stack.value, follows, statementNumber)
//mergeStack(lastStack, this)
//modifies
//uses
    context->currentStack = context->parentStack.top();
    context->parentStack.pop();
}

bool WhileStack::isIf() {
    return false;
}
