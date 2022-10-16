#include "WhileStack.h"
#include <stdexcept>

WhileStack::WhileStack(SimpleToken parent, Extractor* context) : parent(parent), StmtStack(parent, context) {
    this->context = context;
}

void WhileStack::close(int statementNumber) {
    for (SimpleToken stmt : this->context->previousStmt) {
        Entity* prev = generateEntity(stmt);
        Entity* next = generateEntity(this->parent);
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

    context->currentStack = context->parentStack.top();
    context->parentStack.pop();
}

void WhileStack::extractNext(SimpleToken stmtToken) {
    for (SimpleToken stmt : this->context->previousStmt) {
        Entity* prev = generateEntity(stmt);
        Entity* next = generateEntity(stmtToken);
        NextRelationship* nextRel = new NextRelationship(prev, next);
        this->context->client->storeRelationship(nextRel);
    }
    this->context->previousStmt.clear();
    this->context->previousStmt.push_back(stmtToken);
}

void WhileStack::mergeStack() {
    for (SimpleToken callStmt : this->callStmts) {
        this->whileIfCallMap.insert(std::pair<std::string, SimpleToken>(callStmt.value, this->parent));
    }

    StmtStack* parent = context->parentStack.top();
    parent->stmtsNested.merge(this->stmtsNested);
    parent->varUse.merge(this->varUse);
    parent->varMod.merge(this->varMod);
    parent->callStmts.insert(parent->callStmts.end(), this->callStmts.begin(), this->callStmts.end());
    for (std::pair<std::string, SimpleToken> pair : whileIfCallMap) {
        parent->whileIfCallMap.insert(pair);
    }

    for (SimpleToken stmt : this->stmts) {
        parent->stmtsNested.insert(stmt);
    }
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

void WhileStack::extractParentT(std::unordered_set<SimpleToken, SimpleHash> stmtsNested) {
    Entity* firstEntity = generateEntity(this->parent);
    for (SimpleToken stmt : stmtsNested) {
        SimpleToken second = stmt;
        Entity* secondEntity = generateEntity(second);
        ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(parentTRel);
    }
}

void WhileStack::extractUses(std::unordered_set<SimpleToken, SimpleHash> varUse) {
    Entity* firstEntity = generateEntity(this->parent);
    for (SimpleToken var : varUse) {
        SimpleToken second = var;
        Entity* secondEntity = generateEntity(SimpleToken(SpTokenType::TVARIABLE, second.value, 0));
        UsesRelationship* usesRel = new UsesRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(usesRel);
    }
}

void WhileStack::extractModify(std::unordered_set<SimpleToken, SimpleHash> varMod) {
    Entity* firstEntity = generateEntity(this->parent);
    for (SimpleToken var : varMod) {
        SimpleToken second = var;
        Entity* secondEntity = generateEntity(SimpleToken(SpTokenType::TVARIABLE, second.value, 0));
        ModifyRelationship* modifyRel = new ModifyRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(modifyRel);
    }
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

