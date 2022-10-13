#include "IfStack.h"
#include <stdexcept>

#include <iostream>

IfStack::IfStack(SimpleToken parent, Extractor* context) : parent(parent), StmtStack(parent, context) {
    this->expectElse = true;
    this->context = context;
}

void IfStack::close(int statementNumber) {
    if (expectElse) {
        ifStmts = stmts;
        stmts.clear();
        this->expectElse = false;

        addEndPoints(ifStmts);
    } else {
        addEndPoints(stmts);
        mergeEndPoints();

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

        context->endPoints = this->endPoints;

        context->currentStack = context->parentStack.top();
        context->parentStack.pop();
    }
}

void IfStack::addEndPoints(std::vector<SimpleToken> stmts) {
    if (stmts.back().type != SpTokenType::TIF) {
        //std::cout << std::to_string(this->parent.statementNumber) + " is adding endPoint " + std::to_string(stmts.back().statementNumber) + "\n";
        endPoints.push_back(stmts.back());
    }
}

void IfStack::mergeEndPoints() {
    StmtStack* parent = context->parentStack.top();
    //std::cout << "About to merge endPoints\n";
    if (parent->parent.type == SpTokenType::TIF || parent->parent.type == SpTokenType::TWHILE) {
        //std::cout << "Merging endPoints now\n";
        parent->endPoints.insert(parent->endPoints.end(), this->endPoints.begin(), this->endPoints.end());
    }
}

void IfStack::mergeStack() {
    StmtStack* parent = context->parentStack.top();
    parent->stmtsNested.insert(parent->stmtsNested.end(), this->ifStmts.begin(), this->ifStmts.end());
    parent->stmtsNested.insert(parent->stmtsNested.end(), this->stmts.begin(), this->stmts.end());
    parent->stmtsNested.insert(parent->stmtsNested.end(), this->stmtsNested.begin(), this->stmtsNested.end());
    parent->varUse.insert(parent->varUse.end(), this->varUse.begin(), this->varUse.end());
    parent->varMod.insert(parent->varMod.end(), this->varMod.begin(), this->varMod.end());
}

void IfStack::extractFollows(std::vector<SimpleToken> stmts) {
    for (int i = 0; i < stmts.size() - 1; i++) {
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

void IfStack::extractParent(std::vector<SimpleToken> stmts) {
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

void IfStack::extractParentT(std::vector<SimpleToken> stmtsNested) {
    for (int i = 0; i < stmtsNested.size(); i++) {
        SimpleToken second = stmtsNested.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(second);
        ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(parentTRel);
    }
}

void IfStack::extractUses(std::vector<SimpleToken> varUse) {
    for (int i = 0; i < varUse.size(); i++) {
        SimpleToken second = varUse.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(SimpleToken(SpTokenType::TVARIABLE, second.value, 0));
        UsesRelationship* usesRel = new UsesRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(usesRel);
    }
}

void IfStack::extractModify(std::vector<SimpleToken> varMod) {
    for (int i = 0; i < varMod.size(); i++) {
        SimpleToken second = varMod.at(i);
        Entity* firstEntity = generateEntity(this->parent);
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
