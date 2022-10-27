#include "IfStack.h"
#include <stdexcept>

IfStack::IfStack(Entity* parent, Extractor* context) : parent(parent), StmtStack(parent, context) {
    this->expectElse = true;
    this->context = context;
}

void IfStack::close(int statementNumber) {
    if (expectElse) {
        for (Entity* stmt : this->context->previousStmt) {
            this->endPoints.push_back(stmt);
        }
        this->context->previousStmt.clear();
        this->context->previousStmt.push_back(this->parent);
        ifStmts = stmts;
        stmts.clear();
        this->expectElse = false;
    } else {
        for (Entity* stmt : this->endPoints) {
            this->context->previousStmt.push_back(stmt);
        }
        this->endPoints.clear();
        extractFollows(ifStmts);
        extractFollows(stmts);
        extractFollowsT(ifStmts);
        extractFollowsT(stmts);
        extractParent(ifStmts);
        extractParent(stmts);
        extractParentT(context->currentStack->stmtsNested);
        extractUses(context->currentStack->varUse);
        extractModify(context->currentStack->varMod);
        mergeStack();
        this->context->currentStack = context->parentStack.top();
        this->context->parentStack.pop();
    }
}

void IfStack::mergeStack() {
    for (Entity* callStmt : this->callStmts) {
        this->whileIfCallMap.insert(std::pair<std::string, Entity*>(callStmt->getValue(), this->parent));
    }
    StmtStack* parent = context->parentStack.top();
    for (Entity* stmt : this->ifStmts) {
        parent->stmtsNested.insert(stmt);
    }
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

void IfStack::extractModify(Entity* left, Entity* right) {
    ModifyRelationship* relationship = new ModifyRelationship(left, right);
    this->context->client->storeRelationship(relationship);
}

void IfStack::extractUses(Entity* left, Entity* right) {
    UsesRelationship* relationship = new UsesRelationship(left, right);
    this->context->client->storeRelationship(relationship);
}

void IfStack::extractNext(Entity* entity) {
    for (Entity* stmt : this->context->previousStmt) {
        Entity* prev = stmt;
        Entity* next = entity;
        NextRelationship* nextRel = new NextRelationship(prev, next);
        this->context->client->storeRelationship(nextRel);
    }
    this->context->previousStmt.clear();
    this->context->previousStmt.push_back(entity);
}

void IfStack::extractFollows(std::vector<Entity*> stmts) {
    for (size_t i = 0; i < stmts.size() - 1; i++) {
        Entity* firstEntity = stmts.at(i);
        Entity* secondEntity = stmts.at(i + 1);
        FollowsRelationship* followsRel = new FollowsRelationship(firstEntity, secondEntity);
        this->context->client->storeRelationship(followsRel);
    }
}

void IfStack::extractFollowsT(std::vector<Entity*> stmts) {
    for (int i = 0; i < stmts.size(); i++) {
        Entity* firstEntity = stmts.at(i);
        for (int j = i + 1; j < stmts.size(); j++) {
            Entity* secondEntity = stmts.at(j);
            FollowsTRelationship* followsTRel = new FollowsTRelationship(firstEntity, secondEntity);
            this->context->client->storeRelationship(followsTRel);
        }
    }
}

void IfStack::extractParent(std::vector<Entity*> stmts) {
    Entity* firstEntity = this->parent;
    for (int i = 0; i < stmts.size(); i++) {
        Entity* secondEntity = stmts.at(i);
        ParentRelationship* parentRel = new ParentRelationship(firstEntity, secondEntity);
        ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
        this->context->client->storeRelationship(parentRel);
        this->context->client->storeRelationship(parentTRel);
    }
}

void IfStack::extractParentT(std::unordered_set<Entity*, SimpleHash> stmtsNested) {
    Entity* firstEntity = this->parent;
    for (Entity* stmt : stmtsNested) {
        Entity* secondEntity = stmt;
        ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
        this->context->client->storeRelationship(parentTRel);
    }
}

void IfStack::extractUses(std::unordered_set<Entity*, SimpleHash> varUse) {
    Entity* firstEntity = this->parent;
    for (Entity* var : varUse) {
        Entity* secondEntity = var;
        UsesRelationship* usesRel = new UsesRelationship(firstEntity, secondEntity);
        this->context->client->storeRelationship(usesRel);
    }
}

void IfStack::extractModify(std::unordered_set<Entity*, SimpleHash> varMod) {
    Entity* firstEntity = this->parent;
    for (Entity* var : varMod) {
        Entity* secondEntity = var;
        ModifyRelationship* modifyRel = new ModifyRelationship(firstEntity, secondEntity);
        this->context->client->storeRelationship(modifyRel);
    }
}
