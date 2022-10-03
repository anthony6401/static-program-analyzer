#include "./StmtStack.h"

StmtStack::StmtStack() {
    std::vector<ModifyRelationship*> modifies;
    std::vector<UsesRelationship*> uses;
    std::vector<SimpleToken> follows;
    std::vector<CallsRelationship*> calls;
    std::multimap<std::string, std::string> callProcedures;

    this->modifies = modifies;
    this->uses = uses;
    this->follows = follows;
    this->calls = calls;
    this->callProcedures = callProcedures;
}

void StmtStack::mergeStack(StmtStack &parentStack, StmtStack &childStack) {
    parentStack.uses.insert(parentStack.uses.begin(), childStack.uses.begin(), childStack.uses.end());
    parentStack.modifies.insert(parentStack.modifies.begin(), childStack.modifies.begin(), childStack.modifies.end());
    parentStack.callProcedures.merge(childStack.callProcedures);
}

void StmtStack::addFollows(SimpleToken token) {
    this->follows.push_back(token);
}

void StmtStack::addUses(UsesRelationship* relationship) {
    this->uses.push_back(relationship);
}

void StmtStack::addModify(ModifyRelationship* relationship) {
    this->modifies.push_back(relationship);
}

void StmtStack::addCall(CallsRelationship* relationship) {
    this->calls.push_back(relationship);
}
