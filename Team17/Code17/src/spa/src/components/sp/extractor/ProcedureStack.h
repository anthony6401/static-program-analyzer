#pragma once

#include "StmtStack.h"

class Extractor;
class Entity;

class ProcedureStack : public StmtStack {
public:
    ProcedureStack(SimpleToken parent, Extractor* context);
    void close(int statementNumber);
    void mergeStack();
    void extractFollows(std::vector<SimpleToken> stmts);
    void extractFollowsT(std::vector<SimpleToken> stmts);
    void extractParent(std::vector<SimpleToken> stmts);
    void extractParentT(std::vector<SimpleToken> stmtsNested);
    void extractUses(std::vector<SimpleToken> varUse);
    void extractModify(std::vector<SimpleToken> varMod);
    Entity* generateEntity(SimpleToken token);

private:
    SimpleToken parent;
    Extractor* context;
};
