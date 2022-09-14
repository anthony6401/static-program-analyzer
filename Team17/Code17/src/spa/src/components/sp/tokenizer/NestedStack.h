#pragma once

#include "StmtStack.h"

class NestedStack : public StmtStack {
public:
    NestedStack(SimpleToken parent);
    void put(SimpleToken token);
    SimpleToken dump();

private:
    SimpleToken parent;
    std::vector<SimpleToken> stmtList;

};
