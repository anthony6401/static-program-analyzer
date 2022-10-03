#include "WhileStack.h"
#include <stdexcept>

WhileStack::WhileStack(SimpleToken parent, Extractor* context) : parent(parent) {
    this->context = context;
}

void WhileStack::close(int statementNumber) {
    extractFollows(context->currentStack->follows);
    extractParent(context->currentStack->follows, statementNumber);
    extractUses(context->currentStack->uses);
    extractModify(context->currentStack->modifies);

    //extractParent(stack.value, follows, statementNumber)
    //mergeStack(parent, cirrent)
    //modifies
    //uses

    context->currentStack = context->parentStack.top();
    context->parentStack.pop();
}

bool WhileStack::isIf() {
    return false;
}

void WhileStack::extractFollows(std::vector<SimpleToken> follows) {

}

void WhileStack::extractParent(std::vector<SimpleToken> follows, int statememtNumber) {

}

void WhileStack::extractUses(std::vector<SimpleToken> follows) {

}

void WhileStack::extractModify(std::vector<SimpleToken> follows) {

}
