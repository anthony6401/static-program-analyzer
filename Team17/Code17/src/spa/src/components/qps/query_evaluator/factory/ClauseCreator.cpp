#include "ClauseCreator.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/ModifiesSClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/ModifiesPClause.h"
#include <memory>

std::shared_ptr<Clause> ClauseCreator::createClause(Select synonym, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) {
    return std::make_shared<SelectClause>(synonym, synonymToDesignEntityMap, qpsClient);
}

// To be amended for evaluating pattern clauses
std::shared_ptr<Clause> ClauseCreator::createClause(Pattern pattern, Select synonym, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) {
    return nullptr;
}

std::shared_ptr<Clause> ClauseCreator::createClause(SuchThat relationship, Select synonym, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) {
    TokenType relationshipType = relationship.getRelationshipType();
    TokenObject left = relationship.getLeft();
    TokenObject right = relationship.getRight();

    if (relationshipType == TokenType::MODIFIES) {
        if (isStmtRelationship(left, synonymToDesignEntityMap)) {
            return std::make_shared<ModifiesSClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
        }

        if (isProcRelationship(left, synonymToDesignEntityMap)) {
            return std::make_shared<ModifiesPClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
        }

        // Unrecognised MODIFIES relationship clause
    } else if (relationshipType == TokenType::USES) {
        if (isStmtRelationship(left, synonymToDesignEntityMap)) {
            return std::make_shared<ModifiesSClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
        }

        if (isProcRelationship(left, synonymToDesignEntityMap)) {
            return std::make_shared<ModifiesSClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
        }
    } else {
        return nullptr;
    }

    // FOLLOWS

    // PARENT

    // To be amended
    return nullptr;
}

bool ClauseCreator::isStmtRelationship(TokenObject left,
                                       std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap) {
    TokenType leftTokenType = left.getTokenType();
    DesignEntity leftDesignEntityType = synonymToDesignEntityMap[left.getValue()];
    bool isLeftStmtEntity = (leftTokenType == TokenType::SYNONYM) &&
            leftDesignEntityType == DesignEntity::STMT ||
            leftDesignEntityType == DesignEntity::READ ||
            leftDesignEntityType == DesignEntity::PRINT ||
            leftDesignEntityType == DesignEntity::CALL ||
            leftDesignEntityType == DesignEntity::WHILE ||
            leftDesignEntityType == DesignEntity::IF ||
            leftDesignEntityType == DesignEntity::ASSIGN;

    return (leftTokenType == TokenType::INTEGER) || isLeftStmtEntity;
}

bool ClauseCreator::isProcRelationship(TokenObject left,
                                       std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap) {
    TokenType leftTokenType = left.getTokenType();
    DesignEntity leftDesignEntityType = synonymToDesignEntityMap[left.getValue()];
    bool isLeftProcEntity = (leftTokenType == TokenType::SYNONYM) &&
                            leftDesignEntityType == DesignEntity::PROCEDURE;

    return (leftTokenType == TokenType::NAME_WITH_QUOTATION) || isLeftProcEntity;
}