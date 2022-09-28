#pragma once

#include "StmtStack.h"

class ProcedureStack : public StmtStack {
public:
    ProcedureStack(SimpleToken parent);
    void put(SimpleToken token);
    SimpleToken dump();
    bool isIf();

private:
    SimpleToken parent;
    std::vector<SimpleToken> stmtList;

};
