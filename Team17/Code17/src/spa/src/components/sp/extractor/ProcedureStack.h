#pragma once

#include "StmtStack.h"

class ProcedureStack : public StmtStack {
public:
    ProcedureStack(SimpleToken parent, Extractor* context);
    void close(int statementNumber);
    bool isIf();

private:
    SimpleToken parent;
    Extractor* context;

};
