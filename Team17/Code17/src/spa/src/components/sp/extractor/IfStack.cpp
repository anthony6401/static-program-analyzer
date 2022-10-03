#include "IfStack.h"
#include <stdexcept>

IfStack::IfStack(SimpleToken parent, Extractor* context) : parent(parent) {
    this->expectElse = true;
    this->context = context;
}

void IfStack::close(int statementNumber) {
    if (expectElse) {
        ifFollows = follows;
        follows.clear();
    } else {
        extractFollows(follows);
        extractFollows(ifFollows);
        extractParent(context->currentStack->follows, statementNumber);
        extractUses(context->currentStack->uses);
        extractModify(context->currentStack->modifies);

        mergeStack(context->parentStack.top(), context->currentStack);

        context->currentStack = context->parentStack.top();
        context->parentStack.pop();
    }
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
        FollowsRelationship* followsRel = new FollowsRelationship(firstEntity, firstEntity);
        context->client->storeRelationship(followsRel);
    }
    for (int i = 0; i < follows.size(); i++) {
        for (int j = i + 1; j < follows.size(); j++) {
            SimpleToken first = follows.at(i);
            SimpleToken second = follows.at(j);
            Entity* firstEntity = generateEntity(first);
            Entity* secondEntity = generateEntity(second);
            FollowsTRelationship* followsTRel = new FollowsTRelationship(firstEntity, firstEntity);
            context->client->storeRelationship(followsTRel);
        }
    }
}

void IfStack::extractParent(std::vector<SimpleToken> follows, int statementNumber) {
    for (int i = 0; i < follows.size(); i++) {
        SimpleToken second = follows.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(second);
        ParentRelationship* parentRel = new ParentRelationship(firstEntity, firstEntity);
        context->client->storeRelationship(parentRel);
    }
    // parentT?
}

void IfStack::extractUses(std::vector<SimpleToken> uses) {
    for (int i = 0; i < uses.size(); i++) {
        SimpleToken second = uses.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(second);
        UsesRelationship* usesRel = new UsesRelationship(firstEntity, firstEntity);
        context->client->storeRelationship(usesRel);
    }
}

void IfStack::extractModify(std::vector<SimpleToken> modifies) {
    for (int i = 0; i < modifies.size(); i++) {
        SimpleToken second = modifies.at(i);
        Entity* firstEntity = generateEntity(this->parent);
        Entity* secondEntity = generateEntity(second);
        ModifyRelationship* modifyRel = new ModifyRelationship(firstEntity, firstEntity);
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
