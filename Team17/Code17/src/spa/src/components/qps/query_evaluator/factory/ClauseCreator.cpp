#include "ClauseCreator.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/FollowsClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/FollowsTClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/ParentClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/ParentTClause.h"
#include "components/qps/query_evaluator/factory/clauses/patterns/AssignPatternClause.h"
#include <memory>
#include "iostream"
#include "components/qps/query_evaluator/factory/clauses/relationship/CallsClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/CallsTClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/NextClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/NextTClause.h"
#include "components/qps/query_evaluator/factory/clauses/select/SelectBooleanClause.h"
#include "components/qps/query_evaluator/factory/clauses/select/SelectSynonymClause.h"
#include "components/qps/query_evaluator/factory/clauses/select/SelectTupleClause.h"
#include "components/qps/query_evaluator/factory/clauses/select/SelectAttributeClause.h"
#include "components/qps/abstract_query_object/With.h"
#include "components/qps/query_evaluator/factory/clauses/with/WithClause.h"
#include "components/qps/query_evaluator/factory/clauses/patterns/IfPatternClause.h"
#include "components/qps/query_evaluator/factory/clauses/patterns/WhilePatternClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/UsesClause.h"
#include "components/qps/query_evaluator/factory/clauses/relationship/ModifiesClause.h"


std::shared_ptr<Clause> ClauseCreator::createClause(With with,
                                                    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                                                    QPSClient qpsClient) {

    std::vector<TokenObject> left = with.getLeft();
    std::vector<TokenObject> right = with.getRight();

    return std::make_shared<WithClause>(left, right, synonymToDesignEntityMap, qpsClient);
}

std::shared_ptr<Clause> ClauseCreator::createClause(Select select, std::unordered_set<std::string> &synonymsInTable, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) {
    TokenType selectReturnType = select.getReturnType();
    std::vector<TokenObject> selectReturnValues = select.getReturnValues();
    if (selectReturnType == TokenType::SYNONYM) {
        // NAME
        return std::make_shared<SelectSynonymClause>(selectReturnValues.front(), synonymsInTable, synonymToDesignEntityMap, qpsClient);
    } else if (selectReturnType == TokenType::BOOLEAN) {
        return std::make_shared<SelectBooleanClause>();
    } else if (selectReturnType == TokenType::TUPLE) {
        // NAME, ATTRIBUTE_SYNONYM, ATTRIBUTE_NAME
        return std::make_shared<SelectTupleClause>(selectReturnValues, synonymsInTable, synonymToDesignEntityMap, qpsClient);
    } else if (selectReturnType == TokenType::ATTRIBUTE) {
        // ATTRIBUTE_SYNONYM, ATTRIBUTE_NAME
        std::string attributeName = selectReturnValues.back().getValue();
        return std::make_shared<SelectAttributeClause>(selectReturnValues.front(), attributeName, synonymsInTable, synonymToDesignEntityMap, qpsClient);
    } else {
        return nullptr;
    }
}

std::shared_ptr<Clause> ClauseCreator::createClause(qps::Pattern pattern, const std::unordered_map<std::string, DesignEntity>& synonymToDesignEntityMap, QPSClient qpsClient) {
    TokenObject firstArgument = pattern.getLeft();
    TokenObject secondArgument = pattern.getRight();
    std::string patternSynonym = pattern.getSynonym();
    TokenType patternType = pattern.getPatternType();

    if (patternType == TokenType::IF) {
        return std::make_shared<IfPatternClause>(patternSynonym, firstArgument, qpsClient);
    } else if (patternType == TokenType::WHILE) {
        return std::make_shared<WhilePatternClause>(patternSynonym, firstArgument, qpsClient);
    } else {
        return std::make_shared<AssignPatternClause>(patternSynonym, firstArgument, secondArgument, qpsClient);
    }
}

std::shared_ptr<Clause> ClauseCreator::createClause(SuchThat relationship, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) {
    TokenType relationshipType = relationship.getRelationshipType();
    TokenObject left = relationship.getLeft();
    TokenObject right = relationship.getRight();
    if (relationshipType == TokenType::MODIFIES) {
       return std::make_shared<ModifiesClause>(left, right, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::USES) {
        return std::make_shared<UsesClause>(left, right, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::FOLLOWS) {
        return std::make_shared<FollowsClause>(left, right, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::FOLLOWS_T) {
        return std::make_shared<FollowsTClause>(left, right, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::PARENT) {
        return std::make_shared<ParentClause>(left, right, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::PARENT_T) {
        return std::make_shared<ParentTClause>(left, right, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::CALLS){
        return std::make_shared<CallsClause>(left, right, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::CALLS_T) {
        return std::make_shared<CallsTClause>(left, right, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::NEXT) {
        return std::make_shared<NextClause>(left, right, synonymToDesignEntityMap, qpsClient);
    } else if (relationshipType == TokenType::NEXT_T) {
        return std::make_shared<NextTClause>(left, right, synonymToDesignEntityMap, qpsClient);
    } else {
        return nullptr;
    }
}