#pragma once

#include "StmtStack.h"

class ProgramStack : public StmtStack {
public:
    ProgramStack(SimpleToken parent);
    void put(SimpleToken token);
    SimpleToken dump();

private:
    SimpleToken parent;
    std::vector<SimpleToken> stmtList;

};
