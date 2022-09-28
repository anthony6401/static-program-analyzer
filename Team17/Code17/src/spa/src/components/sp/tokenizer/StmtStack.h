#pragma once

#include <stack>
#include <map>
#include <set>
#include "../SimpleToken.h"

class StmtStack {

public:
    StmtStack();
    virtual void put(SimpleToken value) = 0;
    virtual SimpleToken dump() = 0;
    virtual bool isIf() = 0;
    void mergeStack(StmtStack &parentStack, StmtStack &childStack);
    std::set<std::string> modifies;
    std::set<std::string> uses;
    std::multimap<std::string, SimpleToken> callParents;
    std::multimap<std::string, std::string> callProcedures;
};
