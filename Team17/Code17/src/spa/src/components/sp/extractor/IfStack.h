#pragma once

#include "StmtStack.h"

class IfStack : public StmtStack {
public:
    IfStack(SimpleToken parent);
    void put(SimpleToken token);
    bool isIf();
    std::vector<SimpleToken> ifFollows;// statementNumber

private:
    SimpleToken parent;
    bool expectElse;

};
