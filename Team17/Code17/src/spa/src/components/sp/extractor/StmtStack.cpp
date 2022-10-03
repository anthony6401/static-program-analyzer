#include "./StmtStack.h"

StmtStack::StmtStack() {}

void StmtStack::mergeStack(StmtStack &parentStack, StmtStack &childStack) {
    parentStack.uses.insert(parentStack.uses.begin(), childStack.uses.begin(), childStack.uses.end());
    parentStack.modifies.insert(parentStack.modifies.begin(), childStack.modifies.begin(), childStack.modifies.end());
    parentStack.callProcedures.merge(childStack.callProcedures);
}