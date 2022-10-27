#pragma once

#include "StmtStack.h"
#include "Extractor.h"

class IfStack : public StmtStack {
public:
    IfStack(Entity* parent, Extractor* context);
    void close(int statemetNumber);
    void mergeStack();
    std::vector<Entity*> ifStmts; // statementNumber
    void extractFollows(std::vector<Entity*> stmts);
    void extractFollowsT(std::vector<Entity*> stmts);
    void extractParent(std::vector<Entity*> stmts);
    void extractParentT(std::unordered_set<Entity*, SimpleHash> stmtsNested);
    void extractUses(std::unordered_set<Entity*, SimpleHash> varUse);
    void extractModify(std::unordered_set<Entity*, SimpleHash> varMod);
    virtual void extractModify(Entity* left, Entity* right);
    virtual void extractUses(Entity* left, Entity* right);
    void extractNext(Entity* entity);
    std::vector<Entity*> endPoints;

private:
    bool expectElse;
    Entity* parent;
    Extractor* context;
};
