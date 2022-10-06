#pragma once

#include "StmtStack.h"
#include "Extractor.h"

class IfStack : public StmtStack {
public:
    IfStack(SimpleToken parent, Extractor* context);
    void close(int statemetNumber);
    std::vector<SimpleToken> ifFollows; // statementNumber
    void extractFollows(std::vector<SimpleToken> follows);
    void extractParent(std::vector<SimpleToken> follows);
    void extractParentT(std::vector<SimpleToken> parentT);
    void extractUses(std::vector<SimpleToken> uses);
    void extractModify(std::vector<SimpleToken> modifies);
    Entity* generateEntity(SimpleToken token);
    void mergeStack();

private:
    SimpleToken parent;
    bool expectElse;
    Extractor* context;
};
