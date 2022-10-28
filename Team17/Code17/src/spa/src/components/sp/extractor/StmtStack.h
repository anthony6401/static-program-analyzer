#pragma once

#include <unordered_set>
#include <vector>
#include <map>

#include "../utils/SpUtils.h"

class Extractor;
class Entity;

class StmtStack {
public:
    Entity* parent;
    virtual void close(int statementNumber) = 0;
    virtual void mergeStack() = 0;
    std::unordered_set<Entity*, SimpleHash> varMod;
    std::unordered_set<Entity*, SimpleHash> varUse;
    std::unordered_set<Entity*, SimpleHash> stmtsNested;
    std::vector<Entity*> stmts;
    std::vector<Entity*> callStmts;
    std::multimap<std::string, Entity*> whileIfCallMap;
    virtual void extractModify(Entity* left, Entity* right) = 0;
    virtual void extractUses(Entity* left, Entity* right) = 0;
    virtual void extractNext(Entity* entity) = 0;

protected:
    StmtStack(Entity* parent, Extractor* context) : parent(parent) {};
};
