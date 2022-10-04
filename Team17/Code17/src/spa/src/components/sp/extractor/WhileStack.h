#pragma once

#include "StmtStack.h"
#include "Extractor.h"

class WhileStack : public StmtStack {
public:
    WhileStack(SimpleToken parent, Extractor* context);
    void close(int statementNumber);
    void mergeStack();
    void extractFollows(std::vector<SimpleToken> follows);
    void extractParent(std::vector<SimpleToken> follows);
    void extractParentT(std::vector<SimpleToken> parentT);
    void extractUses(std::vector<SimpleToken> uses);
    void extractModify(std::vector<SimpleToken> modifies);
    Entity* generateEntity(SimpleToken token);

private:
    SimpleToken parent;
    Extractor* context;
};
