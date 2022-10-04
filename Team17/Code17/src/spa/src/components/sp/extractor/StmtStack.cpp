#include "./StmtStack.h"

StmtStack::StmtStack(){}

void StmtStack::mergeStack(StmtStack* parentStack, StmtStack* childStack) {
    parentStack->parentT.insert(parentStack->parentT.end(), childStack->follows.begin(), childStack->follows.end());
    parentStack->uses.insert(parentStack->uses.end(), childStack->uses.begin(), childStack->uses.end());
    parentStack->modifies.insert(parentStack->modifies.end(), childStack->modifies.begin(), childStack->modifies.end());
    //parentStack.callProcedures.merge(childStack.callProcedures);
}

void StmtStack::addFollows(SimpleToken token) {
    this->follows.push_back(token);
}
