#include "IfStack.h"
#include <stdexcept>

#include <iostream>

IfStack::IfStack(SimpleToken parent, Extractor* context) : parent(parent) {
    this->expectElse = true;
    this->context = context;
}

void IfStack::close(int statementNumber) {
    if (expectElse) {
        ifFollows = follows;
        follows.clear();
        this->expectElse = false;
    } else {
        extractFollows(ifFollows);
        extractFollows(follows);
        extractParent(ifFollows);
        extractParent(follows);
        extractParentT(context->currentStack->parentT);
        extractUses(context->currentStack->uses);
        extractModify(context->currentStack->modifies);

        mergeStack_if(context->parentStack.top(), context->currentStack, ifFollows);

        context->currentStack = context->parentStack.top();
        context->parentStack.pop();
    }
}

void IfStack::mergeStack_if(StmtStack* parentStack, StmtStack* childStack, std::vector<SimpleToken> ifFollows) {
    parentStack->parentT.insert(parentStack->parentT.end(), ifFollows.begin(), ifFollows.end());
    parentStack->parentT.insert(parentStack->parentT.end(), childStack->follows.begin(), childStack->follows.end());
    parentStack->uses.insert(parentStack->uses.end(), childStack->uses.begin(), childStack->uses.end());
    parentStack->modifies.insert(parentStack->modifies.end(), childStack->modifies.begin(), childStack->modifies.end());
}

bool IfStack::isIf() {
    return expectElse;
}

void IfStack::extractFollows(std::vector<SimpleToken> follows) {
    for (int i = 0; i < follows.size() - 1; i++) {
        SimpleToken first = follows.at(i);
        SimpleToken second = follows.at(i + 1);
        Entity* firstEntity = generateEntity(first);
        Entity* secondEntity = generateEntity(second);
        FollowsRelationship* followsRel = new FollowsRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(followsRel);
    }
    for (int i = 0; i < follows.size(); i++) {
        for (int j = i + 1; j < follows.size(); j++) {
            SimpleToken first = follows.at(i);
            SimpleToken second = follows.at(j);
            Entity* firstEntity = generateEntity(first);
            Entity* secondEntity = generateEntity(second);
            FollowsTRelationship* followsTRel = new FollowsTRelationship(firstEntity, secondEntity);
            context->client->storeRelationship(followsTRel);
        }
    }
}

void IfStack::extractParent(std::vector<SimpleToken> follows) {
    for (int i = 0; i < follows.size(); i++) {
        SimpleToken second = follows.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(second);
        ParentRelationship* parentRel = new ParentRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(parentRel);
    }
}

void IfStack::extractParentT(std::vector<SimpleToken> parentT) {
    for (int i = 0; i < parentT.size(); i++) {
        SimpleToken second = parentT.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(second);
        ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(parentTRel);
    }
}

void IfStack::extractUses(std::vector<SimpleToken> uses) {
    for (int i = 0; i < uses.size(); i++) {
        SimpleToken second = uses.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(SimpleToken(SpTokenType::TVARIABLE, second.value, 0));
        UsesRelationship* usesRel = new UsesRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(usesRel);
    }
}

void IfStack::extractModify(std::vector<SimpleToken> modifies) {
    for (int i = 0; i < modifies.size(); i++) {
        SimpleToken second = modifies.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(SimpleToken(SpTokenType::TVARIABLE, second.value, 0));
        ModifyRelationship* modifyRel = new ModifyRelationship(firstEntity, secondEntity);
        context->client->storeRelationship(modifyRel);
    }
}

Entity* IfStack::generateEntity(SimpleToken token) {
    if (token.type == SpTokenType::TREAD) {
        return new ReadEntity(std::to_string(token.statementNumber));
    }
    if (token.type == SpTokenType::TPRINT) {
        return new PrintEntity(std::to_string(token.statementNumber));
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
        return new CallEntity(std::to_string(token.statementNumber));
    }
    return new Entity(std::to_string(token.statementNumber)); // Should not happen
}
