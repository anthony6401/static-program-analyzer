#pragma once

#include "StmtStack.h"

class ProcedureStack : public StmtStack {
public:
    ProcedureStack(SimpleToken parent);
    void put(SimpleToken token);
    bool isIf();

private:
    SimpleToken parent;

};
