#pragma once

#include "StmtStack.h"
#include "Extractor.h"

class WhileStack : public StmtStack {
public:
    WhileStack(SimpleToken parent, Extractor* context);
    void close(int statementNumber);
    bool isIf();

private:
    SimpleToken parent;
    Extractor* context;

};
