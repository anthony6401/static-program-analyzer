#include "IfStack.h"
#include <stdexcept>

IfStack::IfStack(SimpleToken parent, Extractor* context) : parent(parent), StmtStack(parent, context) {
    this->expectElse = true;
    this->context = context;
}

void IfStack::close(int statementNumber) {
    if (expectElse) {
        for (SimpleToken stmt : this->context->previousStmt) {
            this->endPoints.push_back(stmt);
        }
        this->context->previousStmt.clear();
        this->context->previousStmt.push_back(this->parent);

        ifStmts = stmts;
        stmts.clear();
        this->expectElse = false;
    } else {
        for (SimpleToken stmt : this->endPoints) {
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

        context->currentStack = context->parentStack.top();
        context->parentStack.pop();
    }
}

void IfStack::extractNext(SimpleToken stmtToken) {
    for (SimpleToken stmt : this->context->previousStmt) {
        Entity* prev = generateEntity(stmt);
        Entity* next = generateEntity(stmtToken);
        NextRelationship* nextRel = new NextRelationship(prev, next);
        this->context->client->storeRelationship(nextRel);
    }
    this->context->previousStmt.clear();
    this->context->previousStmt.push_back(stmtToken);
}

void IfStack::mergeStack() {
    for (SimpleToken callStmt : this->callStmts) {
        this->whileIfCallMap.insert(std::pair<std::string, SimpleToken>(callStmt.value, this->parent));
    }

    StmtStack* parent = context->parentStack.top();
    for (SimpleToken stmt : this->ifStmts) {
        parent->stmtsNested.insert(stmt);
    }
    for (SimpleToken stmt : this->stmts) {
        parent->stmtsNested.insert(stmt);
    }

    parent->stmtsNested.merge(this->stmtsNested);
    parent->varUse.merge(this->varUse);
    parent->varMod.merge(this->varMod);
    parent->callStmts.insert(parent->callStmts.end(), this->callStmts.begin(), this->callStmts.end());
    parent->whileIfCallMap = this->whileIfCallMap;


}

void IfStack::extractFollows(std::vector<SimpleToken> stmts) {
    for (size_t i = 0; i < stmts.size() - 1; i++) {
        SimpleToken first = stmts.at(i);
        SimpleToken second = stmts.at(i + 1);
        Entity* firstEntity = generateEntity(first);
        Entity* secondEntity = generateEntity(second);
        FollowsRelationship* followsRel = new FollowsRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(followsRel);
    }
}

void IfStack::extractFollowsT(std::vector<SimpleToken> stmts) {
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

void IfStack::extractParent(std::vector<SimpleToken> stmts) {
    Entity* firstEntity = generateEntity(this->parent);
    for (int i = 0; i < stmts.size(); i++) {
        SimpleToken second = stmts.at(i);
        Entity* secondEntity = generateEntity(second);
        ParentRelationship* parentRel = new ParentRelationship(firstEntity, secondEntity);
        ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(parentRel);
        context->client->storeRelationship(parentTRel);
    }
}

void IfStack::extractParentT(std::unordered_set<SimpleToken, SimpleHash> stmtsNested) {
    Entity* firstEntity = generateEntity(this->parent);
    for (SimpleToken stmt : stmtsNested) {
        SimpleToken second = stmt;
        Entity* secondEntity = generateEntity(second);
        ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(parentTRel);
    }
}

void IfStack::extractUses(std::unordered_set<SimpleToken, SimpleHash> varUse) {
    Entity* firstEntity = generateEntity(this->parent);
    for (SimpleToken var : varUse) {
        SimpleToken second = var;
        Entity* secondEntity = generateEntity(SimpleToken(SpTokenType::TVARIABLE, second.value, 0));
        UsesRelationship* usesRel = new UsesRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(usesRel);
    }
}

void IfStack::extractModify(std::unordered_set<SimpleToken, SimpleHash> varMod) {
    Entity* firstEntity = generateEntity(this->parent);
    for (SimpleToken var : varMod) {
        SimpleToken second = var;
        Entity* secondEntity = generateEntity(SimpleToken(SpTokenType::TVARIABLE, second.value, 0));
        ModifyRelationship* modifyRel = new ModifyRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(modifyRel);
    }
}

Entity* IfStack::generateEntity(SimpleToken token) {
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

