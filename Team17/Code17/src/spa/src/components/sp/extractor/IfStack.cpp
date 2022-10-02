#include "IfStack.h"
#include <stdexcept>

IfStack::IfStack(SimpleToken parent, Extractor* context) : parent(parent) {
    this->expectElse = true;
    this->context = context;
}

void IfStack::close(int statementNumber) {
    if (expectElse) {
        ifFollows = follows;
        follows.clear();
    } else {
        //extractFollows(follows)
        //extractFollows(ifFollows)
        //extractParent(stack.value, follows, statemetNumber)
        //smergeStack(lastStack, this)
        context->currentStack = context->parentStack.top();
        context->parentStack.pop();
    }
}

bool IfStack::isIf() {
    return expectElse;
}
