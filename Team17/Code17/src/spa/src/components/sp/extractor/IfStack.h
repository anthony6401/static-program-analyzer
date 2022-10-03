#pragma once

#include "StmtStack.h"
#include "Extractor.h"

class IfStack : public StmtStack {
public:
    IfStack(SimpleToken parent, Extractor* context);
    void close(int statemetNumber);
    bool isIf();
    std::vector<SimpleToken> ifFollows; // statementNumber
    void extractFollows(std::vector<SimpleToken> follows);
    void extractParent(std::vector<SimpleToken> follows, int statementNumber);
    void extractUses(std::vector<SimpleToken> uses);
    void extractModify(std::vector<SimpleToken> modifies);
    Entity* generateEntity(SimpleToken token);

private:
    SimpleToken parent;
    bool expectElse;
    Extractor* context;

};
