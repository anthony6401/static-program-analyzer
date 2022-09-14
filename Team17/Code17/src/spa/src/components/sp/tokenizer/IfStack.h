#pragma once

#include "StmtStack.h"

class IfStack : public StmtStack {
public:
    IfStack(SimpleToken parent);
    void put(SimpleToken token);

private:
    SimpleToken parent;
    std::vector<SimpleToken> stmtList;
    bool expectElse;

};
