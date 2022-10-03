#pragma once

#include <stack>
#include <map>
#include <set>
#include "../SimpleToken.h"
#include "../validator/SimpleValidator.h"

class StmtStack {

public:
    StmtStack();
    SimpleToken parent;
    virtual void close(int statementNumber) = 0;
    virtual bool isIf() = 0;
    virtual void mergeStack(StmtStack &parentStack, StmtStack &childStack);
    std::vector<SimpleToken> modifies;
    std::vector<SimpleToken> uses;
    std::vector<SimpleToken> follows;
    void addFollows(SimpleToken token);

};
