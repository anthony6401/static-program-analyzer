#include "ProcedureStack.h"
#include <stdexcept>
#include "Extractor.h"

ProcedureStack::ProcedureStack(Entity* parent, Extractor* context) : parent(parent), StmtStack(parent, context) {
    this->context = context;
}

void ProcedureStack::close(int statementNumber) {
    this->context->previousStmt.clear();
    extractFollows(context->currentStack->stmts);
    extractFollowsT(context->currentStack->stmts);
    extractUses(context->currentStack->varUse);
    extractModify(context->currentStack->varMod);
    this->context->procedures.insert(std::pair<std::string, ProcedureStack*>(parent->getValue(), this));
    this->context->whileIfCallMap.insert(this->whileIfCallMap.begin(), this->whileIfCallMap.end());
}

void ProcedureStack::mergeStack() {}

void ProcedureStack::extractModify(Entity* left, Entity* right) {
    ModifyRelationship* relationship = new ModifyRelationship(left, right);
    this->context->client->storeRelationship(relationship);
}

void ProcedureStack::extractUses(Entity* left, Entity* right) {
    UsesRelationship* relationship = new UsesRelationship(left, right);
    this->context->client->storeRelationship(relationship);
}

void ProcedureStack::extractNext(Entity* entity) {
    for (Entity* stmt : this->context->previousStmt) {
        NextRelationship* nextRel = new NextRelationship(stmt, entity);
        this->context->client->storeRelationship(nextRel);
    }
    this->context->previousStmt.clear();
    this->context->previousStmt.push_back(entity);
}

void ProcedureStack::extractFollows(std::vector<Entity*> stmts) {
    for (size_t i = 0; i < stmts.size() - 1; i++) {
        Entity* firstEntity = stmts.at(i);
        Entity* secondEntity = stmts.at(i + 1);
        FollowsRelationship* followsRel = new FollowsRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(followsRel);
    }
}

void ProcedureStack::extractFollowsT(std::vector<Entity*> stmts) {
    for (int i = 0; i < stmts.size(); i++) {
        Entity* firstEntity = stmts.at(i);
        for (int j = i + 1; j < stmts.size(); j++) {
            Entity* secondEntity = stmts.at(j);
            FollowsTRelationship* followsTRel = new FollowsTRelationship(firstEntity, secondEntity);
            this->context->client->storeRelationship(followsTRel);
        }
    }
}

void ProcedureStack::extractUses(std::unordered_set<Entity*, SimpleHash> varUse) {
    Entity* firstEntity = this->parent;
    for (Entity* var : varUse) {
        Entity* secondEntity = var;
        UsesRelationship* usesRel = new UsesRelationship(firstEntity, secondEntity);
        this->context->client->storeRelationship(usesRel);
    }
}

void ProcedureStack::extractModify(std::unordered_set<Entity*, SimpleHash> varMod) {
    Entity* firstEntity = this->parent;
    for (Entity* var : varMod) {
        Entity* secondEntity = var;
        ModifyRelationship* modifyRel = new ModifyRelationship(firstEntity, secondEntity);
        this->context->client->storeRelationship(modifyRel);
    }
}
