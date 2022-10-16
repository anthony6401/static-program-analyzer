#include "ProcedureStack.h"
#include <stdexcept>
#include "Extractor.h"

ProcedureStack::ProcedureStack(SimpleToken parent, Extractor* context) : parent(parent), StmtStack(parent, context) {
    this->context = context;
}

void ProcedureStack::close(int statementNumber) {
    this->context->previousStmt.clear();

    extractFollows(context->currentStack->stmts);
    extractFollowsT(context->currentStack->stmts);
    extractUses(context->currentStack->varUse);
    extractModify(context->currentStack->varMod);

    context->procedures.insert(std::pair<std::string, ProcedureStack*>(parent.value, this));
    context->whileIfCallMap.insert(this->whileIfCallMap.begin(), this->whileIfCallMap.end());
}

void ProcedureStack::mergeStack() {}

void ProcedureStack::extractNext(SimpleToken stmtToken) {
    for (SimpleToken stmt : this->context->previousStmt) {
        Entity* prev = generateEntity(stmt);
        Entity* next = generateEntity(stmtToken);
        NextRelationship* nextRel = new NextRelationship(prev, next);
        this->context->client->storeRelationship(nextRel);
    }
    this->context->previousStmt.clear();
    this->context->previousStmt.push_back(stmtToken);
}

void ProcedureStack::extractFollows(std::vector<SimpleToken> stmts) {
    for (size_t i = 0; i < stmts.size() - 1; i++) {
        SimpleToken first = stmts.at(i);
        SimpleToken second = stmts.at(i + 1);
        Entity* firstEntity = generateEntity(first);
        Entity* secondEntity = generateEntity(second);
        FollowsRelationship* followsRel = new FollowsRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(followsRel);
    }
}

void ProcedureStack::extractFollowsT(std::vector<SimpleToken> stmts) {
    for (int i = 0; i < stmts.size(); i++) {
        SimpleToken first = stmts.at(i);
        Entity* firstEntity = generateEntity(first);
        for (int j = i + 1; j < stmts.size(); j++) {
            SimpleToken second = stmts.at(j);
            Entity* secondEntity = generateEntity(second);
            FollowsTRelationship* followsTRel = new FollowsTRelationship(firstEntity, secondEntity);
            context->client->storeRelationship(followsTRel);
        }
    }
}

void ProcedureStack::extractUses(std::unordered_set<SimpleToken, SimpleHash> varUse) {
    Entity* firstEntity = generateEntity(this->parent);
    for (SimpleToken var : varUse) {
        SimpleToken second = var;
        Entity* secondEntity = generateEntity(SimpleToken(SpTokenType::TVARIABLE, second.value, 0));
        UsesRelationship* usesRel = new UsesRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(usesRel);
    }
}

void ProcedureStack::extractModify(std::unordered_set<SimpleToken, SimpleHash> varMod) {
    Entity* firstEntity = generateEntity(this->parent);
    for (SimpleToken var : varMod) {
        SimpleToken second = var;
        Entity* secondEntity = generateEntity(SimpleToken(SpTokenType::TVARIABLE, second.value, 0));
        ModifyRelationship* modifyRel = new ModifyRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(modifyRel);
    }
}

Entity* ProcedureStack::generateEntity(SimpleToken token) {
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
