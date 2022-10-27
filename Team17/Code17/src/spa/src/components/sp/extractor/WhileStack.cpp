#include "WhileStack.h"
#include <stdexcept>

WhileStack::WhileStack(Entity* parent, Extractor* context) : parent(parent), StmtStack(parent, context) {
    this->context = context;
}

void WhileStack::close(int statementNumber) {
    for (Entity* stmt : this->context->previousStmt) {
        Entity* prev = stmt;
        Entity* next = this->parent;
        NextRelationship* nextRel = new NextRelationship(prev, next);
        this->context->client->storeRelationship(nextRel);
    }
    this->context->previousStmt.clear();
    this->context->previousStmt.push_back(this->parent);
    extractFollows(context->currentStack->stmts);
    extractFollowsT(context->currentStack->stmts);
    extractParent(context->currentStack->stmts);
    extractParentT(context->currentStack->stmtsNested);
    extractUses(context->currentStack->varUse);
    extractModify(context->currentStack->varMod);
    mergeStack();
    this->context->currentStack = context->parentStack.top();
    this->context->parentStack.pop();
}

void WhileStack::mergeStack() {
    for (Entity* callStmt : this->callStmts) {
        this->whileIfCallMap.insert(std::pair<std::string, Entity*>(callStmt->getValue(), this->parent));
    }
    StmtStack* parent = context->parentStack.top();
    for (Entity* stmt : this->stmts) {
        parent->stmtsNested.insert(stmt);
    }
    parent->stmtsNested.merge(this->stmtsNested);
    parent->varUse.merge(this->varUse);
    parent->varMod.merge(this->varMod);
    parent->callStmts.insert(parent->callStmts.end(), this->callStmts.begin(), this->callStmts.end());
    for (std::pair<std::string, Entity*> pair : whileIfCallMap) {
        parent->whileIfCallMap.insert(pair);
    }
}

void WhileStack::extractModify(Entity* left, Entity* right) {
    ModifyRelationship* relationship = new ModifyRelationship(left, right);
    this->context->client->storeRelationship(relationship);
}

void WhileStack::extractUses(Entity* left, Entity* right) {
    UsesRelationship* relationship = new UsesRelationship(left, right);
    this->context->client->storeRelationship(relationship);
}

void WhileStack::extractNext(Entity* entity) {
    for (Entity* stmt : this->context->previousStmt) {
        Entity* prev = stmt;
        Entity* next = entity;
        NextRelationship* nextRel = new NextRelationship(prev, next);
        this->context->client->storeRelationship(nextRel);
    }
    this->context->previousStmt.clear();
    this->context->previousStmt.push_back(entity);
}

void WhileStack::extractFollows(std::vector<Entity*> stmts) {
    for (size_t i = 0; i < stmts.size() - 1; i++) {
        Entity* firstEntity = stmts.at(i);
        Entity* secondEntity = stmts.at(i + 1);
        FollowsRelationship* followsRel = new FollowsRelationship(firstEntity, secondEntity);
        this->context->client->storeRelationship(followsRel);
    }
}

void WhileStack::extractFollowsT(std::vector<Entity*> stmts) {
    for (int i = 0; i < stmts.size(); i++) {
        Entity* firstEntity = stmts.at(i);
        for (int j = i + 1; j < stmts.size(); j++) {
            Entity* secondEntity = stmts.at(j);
            FollowsTRelationship* followsTRel = new FollowsTRelationship(firstEntity, secondEntity);
            this->context->client->storeRelationship(followsTRel);
        }
    }
}

void WhileStack::extractParent(std::vector<Entity*> stmts) {
    Entity* firstEntity = this->parent;
    for (int i = 0; i < stmts.size(); i++) {
        Entity* secondEntity = stmts.at(i);
        ParentRelationship* parentRel = new ParentRelationship(firstEntity, secondEntity);
        ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
        this->context->client->storeRelationship(parentRel);
        this->context->client->storeRelationship(parentTRel);
    }
}

void WhileStack::extractParentT(std::unordered_set<Entity*, SimpleHash> stmtsNested) {
    Entity* firstEntity = this->parent;
    for (Entity* stmt : stmtsNested) {
        Entity* secondEntity = stmt;
        ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
        this->context->client->storeRelationship(parentTRel);
    }
}

void WhileStack::extractUses(std::unordered_set<Entity*, SimpleHash> varUse) {
    Entity* firstEntity = this->parent;
    for (Entity* var : varUse) {
        Entity* secondEntity = var;
        UsesRelationship* usesRel = new UsesRelationship(firstEntity, secondEntity);
        this->context->client->storeRelationship(usesRel);
    }
}

void WhileStack::extractModify(std::unordered_set<Entity*, SimpleHash> varMod) {
    Entity* firstEntity = this->parent;
    for (Entity* var : varMod) {
        Entity* secondEntity = var;
        ModifyRelationship* modifyRel = new ModifyRelationship(firstEntity, secondEntity);
        this->context->client->storeRelationship(modifyRel);
    }
}
