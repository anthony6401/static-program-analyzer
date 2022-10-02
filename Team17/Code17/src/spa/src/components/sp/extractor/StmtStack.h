#pragma once

#include <stack>
#include <map>
#include <set>
#include "../SimpleToken.h"

class StmtStack {

public:
    StmtStack();
    virtual void put(SimpleToken value) = 0;
    virtual bool isIf() = 0;
    void mergeStack(StmtStack &parentStack, StmtStack &childStack);
    std::vector<SimpleToken> modifies;//variable names for modifies
    std::vector<SimpleToken> uses;//variable names for uses
    std::vector<SimpleToken> follows;// statementNumber
    std::multimap<std::string, std::string> callProcedures;// call procedure <proc1,proc2>
};
