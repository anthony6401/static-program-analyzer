#include "./StmtStack.h"

StmtStack::StmtStack() {

}

void StmtStack::mergeStack(StmtStack &parentStack, StmtStack &childStack) {
    parentStack.uses.insert(childStack.uses.begin(), childStack.uses.end());
    parentStack.modifies.insert(childStack.modifies.begin(), childStack.modifies.end());
    parentStack.callParents.merge(childStack.callParents);
    parentStack.callProcedures.merge(childStack.callProcedures);
}