#include "ClauseCreator.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/ModifiesSClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/ModifiesPClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/FollowsClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/FollowsTClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/ParentClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/ParentTClause.h"
#include "components/qps/query_evaluator/factory/clauses/patterns/AssignPatternClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/UsesSClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/UsesPClause.h"
#include <memory>
#include "iostream"
#include "components/qps/query_evaluator/factory/clauses/relationship/CallsClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/CallsTClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/NextClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/NextTClause.h"

std::shared_ptr<Clause> ClauseCreator::createClause(Select synonym, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) {
    return std::make_shared<SelectClause>(synonym, synonymToDesignEntityMap, qpsClient);
}

std::shared_ptr<Clause> ClauseCreator::createClause(qps::Pattern pattern, Select synonym, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) {
    TokenObject left = pattern.getLeft();
    TokenObject right = pattern.getRight();
    std::string assignSynonym = pattern.getSynonym();
    return std::make_shared<AssignPatternClause>(assignSynonym, left, right, qpsClient, synonym);
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

    } else if (relationshipType == TokenType::USES) {
        if (isProcRelationship(left, synonymToDesignEntityMap)) {
            return std::make_shared<UsesPClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
        }

        if (isStmtRelationship(left, synonymToDesignEntityMap)) {
            return std::make_shared<UsesSClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
        }
    } else if (relationshipType == TokenType::FOLLOWS) {
        return std::make_shared<FollowsClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::FOLLOWS_T) {
        return std::make_shared<FollowsTClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::PARENT) {
        return std::make_shared<ParentClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::PARENT_T) {
        return std::make_shared<ParentTClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::CALLS){
        return std::make_shared<CallsClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::CALLS_T) {
        return std::make_shared<CallsTClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::NEXT) {
        return std::make_shared<NextClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::NEXT_T) {
        return std::make_shared<NextTClause>(left, right, synonym, synonymToDesignEntityMap, qpsClient);
    } else {
        return nullptr;
    };
    return nullptr;
}

bool ClauseCreator::isStmtRelationship(TokenObject left,
                                       std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap) {
    TokenType leftTokenType = left.getTokenType();
    DesignEntity leftDesignEntityType = synonymToDesignEntityMap[left.getValue()];
    bool isLeftStmtEntity = (leftTokenType == TokenType::NAME) &&
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
    bool isLeftProcEntity = (leftTokenType == TokenType::NAME) &&
                            leftDesignEntityType == DesignEntity::PROCEDURE;

    return (leftTokenType == TokenType::NAME_WITH_QUOTATION) || isLeftProcEntity;
}