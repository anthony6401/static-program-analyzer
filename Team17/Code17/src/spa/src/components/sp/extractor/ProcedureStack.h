#pragma once

#include "StmtStack.h"

class Extractor;
class Entity;

class ProcedureStack : public StmtStack {
public:
    ProcedureStack(Entity* parent, Extractor* context);
    void close(int statementNumber);
    void mergeStack();
    void extractFollows(std::vector<Entity*> stmts);
    void extractFollowsT(std::vector<Entity*> stmts);
    void extractUses(std::unordered_set<Entity*, SimpleHash> varUse);
    void extractModify(std::unordered_set<Entity*, SimpleHash> varMod);
    void extractModify(Entity* left, Entity* right);
    void extractUses(Entity* left, Entity* right);
    void extractNext(Entity* entity);

private:
    Entity* parent;
    Extractor* context;
};
