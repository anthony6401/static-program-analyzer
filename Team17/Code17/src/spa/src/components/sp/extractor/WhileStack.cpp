#include "WhileStack.h"
#include <stdexcept>

WhileStack::WhileStack(SimpleToken parent, Extractor* context) : parent(parent) {
    this->context = context;
}

void WhileStack::close(int statementNumber) {
    extractFollows(context->currentStack->follows);
    extractParent(context->currentStack->follows, statementNumber);
    extractUses(context->currentStack->uses);
    extractModify(context->currentStack->modifies);

    //extractParent(stack.value, follows, statementNumber)
    //mergeStack(parent, cirrent)
    //modifies
    //uses

    context->currentStack = context->parentStack.top();
    context->parentStack.pop();
}

bool WhileStack::isIf() {
    return false;
}

void WhileStack::extractFollows(std::vector<SimpleToken> follows) {
    for (int i = 0; i < follows.size() - 1; i++) {
        SimpleToken first = follows.at(i);
        SimpleToken second = follows.at(i + 1);
        Entity* firstEntity = generateEntity(first);
        Entity* secondEntity = generateEntity(second);
        FollowsRelationship* follows = new FollowsRelationship(firstEntity, firstEntity);
        context->client->storeRelationship(follows);
    }
    for (int i = 0; i < follows.size(); i++) {
        for (int j = i + 1; j < follows.size(); j++) {
            SimpleToken first = follows.at(i);
            SimpleToken second = follows.at(j);
            Entity* firstEntity = generateEntity(first);
            Entity* secondEntity = generateEntity(second);
            FollowsTRelationship* followsT = new FollowsTRelationship(firstEntity, firstEntity);
            context->client->storeRelationship(followsT);
        }
    }
}

void WhileStack::extractParent(std::vector<SimpleToken> follows, int statementNumber) {
    int index = 0;
    for (int i = follows.at(0).statementNumber; i < statementNumber; i++) {
        if (std::find(follows.begin(), follows.end(), i) != follows.end()) {
            SimpleToken second = follows.at(index);
            Entity* firstEntity = generateEntity(this->parent);
            Entity* secondEntity = generateEntity(second);
            ParentRelationship* parent = new ParentRelationship(firstEntity, firstEntity);
            context->client->storeRelationship(parent);
        }
        else {
            SimpleToken second = follows.at(index);
            Entity* firstEntity = generateEntity(this->parent);
            Entity* secondEntity = generateEntity(second);
            ParentTRelationship* parentT = new ParentTRelationship(firstEntity, firstEntity);
            context->client->storeRelationship(parentT);
        }
        index++;
    }
}

void WhileStack::extractUses(std::vector<SimpleToken> follows) {

}

void WhileStack::extractModify(std::vector<SimpleToken> follows) {

}

Entity* WhileStack::generateEntity(SimpleToken token) {
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

