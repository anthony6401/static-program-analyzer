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
    void extractUses(std::unordered_set<SimpleToken, SimpleHash> varUse);
    void extractModify(std::unordered_set<SimpleToken, SimpleHash> varMod);
    Entity* generateEntity(SimpleToken token);
    void extractNext(SimpleToken stmtToken);

private:
    SimpleToken parent;
    Extractor* context;
};
