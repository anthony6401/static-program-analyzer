#pragma once

#include "StmtStack.h"
#include "Extractor.h"

class WhileStack : public StmtStack {
public:
    WhileStack(SimpleToken parent, Extractor* context);
    void close(int statementNumber);
    bool isIf();
    void extractFollows(std::vector<SimpleToken> follows);
    void extractParent(std::vector<SimpleToken> follows, int statementNumber);
    void extractUses(std::vector<SimpleToken> uses);
    void extractModify(std::vector<SimpleToken> modifies);

private:
    SimpleToken parent;
    Extractor* context;
};
