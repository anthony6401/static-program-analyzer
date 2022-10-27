#pragma once

#include "StmtStack.h"
#include "Extractor.h"

class WhileStack : public StmtStack {
public:
    WhileStack(Entity* parent, Extractor* context);
    void close(int statementNumber);
    void mergeStack();
    void extractFollows(std::vector<Entity*> stmts);
    void extractFollowsT(std::vector<Entity*> stmts);
    void extractParent(std::vector<Entity*> stmts);
    void extractParentT(std::unordered_set<Entity*, SimpleHash> stmtsNested);
    void extractUses(std::unordered_set<Entity*, SimpleHash> varUse);
    void extractModify(std::unordered_set<Entity*, SimpleHash> varMod);
    void extractModify(Entity* left, Entity* right);
    void extractUses(Entity* left, Entity* right);
    void extractNext(Entity* entity);

private:
    Entity* parent;
    Extractor* context;
};
