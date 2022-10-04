#include "ProcedureStack.h"
#include <stdexcept>
#include "Extractor.h"

#include <iostream>

ProcedureStack::ProcedureStack(SimpleToken parent, Extractor* context) : parent(parent) {
    this->context = context;
}

void ProcedureStack::close(int statementNumber) {
    extractFollows(context->currentStack->follows);
    extractParent(context->currentStack->follows);
    extractParentT(context->currentStack->parentT);
    extractUses(context->currentStack->uses);
    extractModify(context->currentStack->modifies);

    context->procedures.insert(std::pair<std::string, ProcedureStack*>(parent.value, this));
}

bool ProcedureStack::isIf() {
    return false;
}

void ProcedureStack::extractFollows(std::vector<SimpleToken> follows) {
    for (int i = 0; i < follows.size() - 1; i++) {
        SimpleToken first = follows.at(i);
        SimpleToken second = follows.at(i + 1);
        Entity* firstEntity = generateEntity(first);
        Entity* secondEntity = generateEntity(second);
        FollowsRelationship* followsRel = new FollowsRelationship(firstEntity, secondEntity);
        //std::cout << typeid(followsRel).name() << " | " + (followsRel->getLeftEntity()->getValue()) + " | " + (followsRel->getRightEntity()->getValue()) + "\n";
        context->client->storeRelationship(followsRel);
    }
    for (int i = 0; i < follows.size(); i++) {
        for (int j = i + 1; j < follows.size(); j++) {
            SimpleToken first = follows.at(i);
            SimpleToken second = follows.at(j);
            Entity* firstEntity = generateEntity(first);
            Entity* secondEntity = generateEntity(second);
            FollowsTRelationship* followsTRel = new FollowsTRelationship(firstEntity, secondEntity);
            //std::cout << typeid(followsTRel).name() << " | " + (followsTRel->getLeftEntity()->getValue()) + " | " + (followsTRel->getRightEntity()->getValue()) + "\n";
            context->client->storeRelationship(followsTRel);
        }
    }
}

void ProcedureStack::extractParent(std::vector<SimpleToken> follows) {
    for (int i = 0; i < follows.size(); i++) {
        SimpleToken second = follows.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(second);
        ParentRelationship* parentRel = new ParentRelationship(firstEntity, secondEntity);
        //std::cout << typeid(parentRel).name() << " | " + (parentRel->getLeftEntity()->getValue()) + " | " + (parentRel->getRightEntity()->getValue()) + "\n";
        context->client->storeRelationship(parentRel);
    }
}

void ProcedureStack::extractParentT(std::vector<SimpleToken> parentT) {
    for (int i = 0; i < parentT.size(); i++) {
        SimpleToken second = parentT.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(second);
        ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
        //std::cout << typeid(parentTRel).name() << " | " + (parentTRel->getLeftEntity()->getValue()) + " | " + (parentTRel->getRightEntity()->getValue()) + "\n";
        context->client->storeRelationship(parentTRel);
    }
}

void ProcedureStack::extractUses(std::vector<SimpleToken> uses) {
    for (int i = 0; i < uses.size(); i++) {
        SimpleToken second = uses.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(SimpleToken(SpTokenType::TVARIABLE, second.value, 0));
        UsesRelationship* usesRel = new UsesRelationship(firstEntity, secondEntity);
        //std::cout << typeid(usesRel).name() << " | " + (usesRel->getLeftEntity()->getValue()) + " | " + (usesRel->getRightEntity()->getValue()) + "\n";
        context->client->storeRelationship(usesRel);
    }
}

void ProcedureStack::extractModify(std::vector<SimpleToken> modifies) {
    for (int i = 0; i < modifies.size(); i++) {
        SimpleToken second = modifies.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(SimpleToken(SpTokenType::TVARIABLE, second.value, 0));
        ModifyRelationship* modifyRel = new ModifyRelationship(firstEntity, secondEntity);
        //std::cout << typeid(modifyRel).name() << " | " + (modifyRel->getLeftEntity()->getValue()) + " | " + (modifyRel->getRightEntity()->getValue()) + "\n";
        context->client->storeRelationship(modifyRel);
    }
}

Entity* ProcedureStack::generateEntity(SimpleToken token) {
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
