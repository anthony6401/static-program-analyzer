#pragma once

#include "StmtStack.h"
#include "Extractor.h"

class IfStack : public StmtStack {
public:
    IfStack(SimpleToken parent, Extractor* context);
    void close(int statemetNumber);
    bool isIf();
    std::vector<SimpleToken> ifFollows;// statementNumber

private:
    SimpleToken parent;
    bool expectElse;
    Extractor* context;

};
