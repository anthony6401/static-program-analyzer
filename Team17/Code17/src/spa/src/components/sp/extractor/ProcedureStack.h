#pragma once

#include "StmtStack.h"

class Extractor;
class Entity;

class ProcedureStack : public StmtStack {
public:
    ProcedureStack(SimpleToken parent, Extractor* context);
    void close(int statementNumber);
    bool isIf();
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
