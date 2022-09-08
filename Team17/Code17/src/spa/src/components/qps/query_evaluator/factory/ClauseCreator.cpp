#include "ClauseCreator.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/ModifiesSClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/ModifiesPClause.h"
#include <memory>

/**
 * Creates a Select Clause object
 */
std::shared_ptr<Clause> ClauseCreator::createClause(Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap, QPSClient qpsClient) {
    return std::make_shared<SelectClause>(synonym, synonymToDesignEntityMap, qpsClient);
}

std::shared_ptr<Clause> ClauseCreator::createClause(SuchThat relationship, Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap, QPSClient qpsClient) {
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
            // return std::make_shared<UsesSClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
        }

        if (isProcRelationship(left, synonymToDesignEntityMap)) {
            // return std::make_shared<UsesPClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
        }
    }

    // FOLLOWS

    // PARENT

    // To be amended
    return nullptr;
}

bool ClauseCreator::isStmtRelationship(TokenObject left,
                                       std::unordered_map<std::string, TokenType> synonymToDesignEntityMap) {
    TokenType leftTokenType = left.getTokenType();
    TokenType leftDesignEntityType = synonymToDesignEntityMap[left.getValue()];
    bool isLeftStmtEntity = (leftTokenType == TokenType::SYNONYM) &&
            leftDesignEntityType == TokenType::STMT ||
            leftDesignEntityType == TokenType::READ ||
            leftDesignEntityType == TokenType::PRINT ||
            leftDesignEntityType == TokenType::CALL ||
            leftDesignEntityType == TokenType::WHILE ||
            leftDesignEntityType == TokenType::IF ||
            leftDesignEntityType == TokenType::ASSIGN;

    return (leftTokenType == TokenType::INTEGER) || isLeftStmtEntity;
}

bool ClauseCreator::isProcRelationship(TokenObject left,
                                       std::unordered_map<std::string, TokenType> synonymToDesignEntityMap) {
    TokenType leftTokenType = left.getTokenType();
    TokenType leftDesignEntityType = synonymToDesignEntityMap[left.getValue()];
    bool isLeftStmtEntity = (leftTokenType == TokenType::SYNONYM) &&
                            leftDesignEntityType == TokenType::PROCEDURE;

    return (leftTokenType == TokenType::NAME_WITH_QUOTATION) || isLeftStmtEntity;
}