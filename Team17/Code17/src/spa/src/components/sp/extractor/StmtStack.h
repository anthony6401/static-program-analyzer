#pragma once

#include <stack>
#include <map>
#include <set>
#include "../SimpleToken.h"
#include "../validator/SimpleValidator.h"

class StmtStack {

public:
    StmtStack();
    //virtual void close(int statementNumber) = 0;
    //virtual bool isIf() = 0;
    //virtual void mergeStack(StmtStack &parentStack, StmtStack &childStack);
    void close(int statementNumber);
    bool isIf();
    void mergeStack(StmtStack& parentStack, StmtStack& childStack);
    std::vector<ModifyRelationship*> modifies;
    std::vector<UsesRelationship*> uses;
    std::vector<SimpleToken> follows;
    std::vector<CallsRelationship*> calls;
    std::multimap<std::string, std::string> callProcedures;

    void addFollows(SimpleToken token);
    void addUses(UsesRelationship* relationship);
    void addModify(ModifyRelationship* relationship);
    void addCall(CallsRelationship* relationship);

};
