#include "WhileStack.h"
#include <stdexcept>

#include <iostream>

WhileStack::WhileStack(SimpleToken parent, Extractor* context) : parent(parent), StmtStack(parent, context) {
    this->context = context;
}

void WhileStack::close(int statementNumber) {
    extractFollows(context->currentStack->stmts);
    extractFollowsT(context->currentStack->stmts);
    extractParent(context->currentStack->stmts);
    extractParentT(context->currentStack->stmtsNested);
    extractUses(context->currentStack->varUse);
    extractModify(context->currentStack->varMod);
    extractNext(context->currentStack->stmts);

    mergeStack();

    context->currentStack = context->parentStack.top();
    context->parentStack.pop();
}

void WhileStack::mergeStack() {
    StmtStack* parent = context->parentStack.top();
    parent->stmtsNested.insert(parent->stmtsNested.end(), this->stmts.begin(), this->stmts.end());
    parent->varUse.insert(parent->varUse.end(), this->varUse.begin(), this->varUse.end());
    parent->varMod.insert(parent->varMod.end(), this->varMod.begin(), this->varMod.end());
}

void WhileStack::extractFollows(std::vector<SimpleToken> stmts) {
    for (size_t i = 0; i < stmts.size() - 1; i++) {
        SimpleToken first = stmts.at(i);
        SimpleToken second = stmts.at(i + 1);
        Entity* firstEntity = generateEntity(first);
        Entity* secondEntity = generateEntity(second);
        FollowsRelationship* followsRel = new FollowsRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(followsRel);
    }
}

void WhileStack::extractFollowsT(std::vector<SimpleToken> stmts) {
    for (int i = 0; i < stmts.size(); i++) {
        for (int j = i + 1; j < stmts.size(); j++) {
            SimpleToken first = stmts.at(i);
            SimpleToken second = stmts.at(j);
            Entity* firstEntity = generateEntity(first);
            Entity* secondEntity = generateEntity(second);
            FollowsTRelationship* followsTRel = new FollowsTRelationship(firstEntity, secondEntity);
            context->client->storeRelationship(followsTRel);
        }
    }
}

void WhileStack::extractParent(std::vector<SimpleToken> stmts) {
    for (int i = 0; i < stmts.size(); i++) {
        SimpleToken second = stmts.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(second);
        ParentRelationship* parentRel = new ParentRelationship(firstEntity, secondEntity);
        ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(parentRel);
        context->client->storeRelationship(parentTRel);
    }
}

void WhileStack::extractParentT(std::vector<SimpleToken> stmtsNested) {
    for (int i = 0; i < stmtsNested.size(); i++) {
        SimpleToken second = stmtsNested.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(second);
        ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(parentTRel);
    }
}

void WhileStack::extractUses(std::vector<SimpleToken> varUse) {
    for (int i = 0; i < varUse.size(); i++) {
        SimpleToken second = varUse.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(SimpleToken(SpTokenType::TVARIABLE, second.value, 0));
        UsesRelationship* usesRel = new UsesRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(usesRel);
    }
}

void WhileStack::extractModify(std::vector<SimpleToken> varMod) {
    for (int i = 0; i < varMod.size(); i++) {
        SimpleToken second = varMod.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(SimpleToken(SpTokenType::TVARIABLE, second.value, 0));
        ModifyRelationship* modifyRel = new ModifyRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(modifyRel);
    }
}

void WhileStack::extractNext(std::vector<SimpleToken> stmts) {
    SimpleToken whileStmt = parent;
    SimpleToken firstStmt = stmts.at(0);
    Entity* whileStmtEnt = generateEntity(whileStmt);
    Entity* firstStmtEnt = generateEntity(firstStmt);
    NextRelationship* initialNextRel = new NextRelationship(whileStmtEnt, firstStmtEnt);
    context->client->storeRelationship(initialNextRel);

    for (size_t i = 0; i < stmts.size() - 1; i++) {
        if (stmts.at(i).type != SpTokenType::TIF) {
            SimpleToken first = stmts.at(i);
            SimpleToken second = stmts.at(i + 1);
            Entity* firstEntity = generateEntity(first);
            Entity* secondEntity = generateEntity(second);
            NextRelationship* nextRel = new NextRelationship(firstEntity, secondEntity);
            context->client->storeRelationship(nextRel);
        }
    }

    SimpleToken lastStmt = stmts.at(stmts.size() - 1);
    Entity* lastStmtEnt = generateEntity(lastStmt);
    NextRelationship* lastNextRel = new NextRelationship(lastStmtEnt, whileStmtEnt);
    context->client->storeRelationship(lastNextRel);
}

Entity* WhileStack::generateEntity(SimpleToken token) {
    if (token.type == SpTokenType::TREAD) {
        return new ReadEntity(std::to_string(token.statementNumber), token.value);
    }
    if (token.type == SpTokenType::TPRINT) {
        return new PrintEntity(std::to_string(token.statementNumber), token.value);
    }
    if (token.type == SpTokenType::TASSIGN) {
        return new AssignEntity(std::to_string(token.statementNumber));
    }
    if (token.type == SpTokenType::TWHILE) {
        return new WhileEntity(std::to_string(token.statementNumber));
    }
    if (token.type == SpTokenType::TIF) {
        return new IfEntity(std::to_string(token.statementNumber));
    }
    if (token.type == SpTokenType::TVARIABLE) {
        return new VariableEntity(token.value);
    }
    if (token.type == SpTokenType::TCONSTANT) {
        return new ConstantEntity(token.value);
    }
    if (token.type == SpTokenType::TPROCEDURE) {
        return new ProcedureEntity(token.value);
    }
    if (token.type == SpTokenType::TCALL) {
        return new CallEntity(std::to_string(token.statementNumber), token.value);
    }
    return new Entity(std::to_string(token.statementNumber)); // Should not happen
}
