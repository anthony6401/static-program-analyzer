#include "AffectsClause.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

AffectsClause::AffectsClause(TokenObject left, TokenObject right,
                             std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                             QPSClient qpsClient) : left(std::move(left)), right(std::move(right)),
                                                    synonymToDesignEntityMap(std::move(synonymToDesignEntityMap)), qpsClient(qpsClient) {}

ResultTable AffectsClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return AffectsClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return AffectsClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::INTEGER) {
        return AffectsClause::evaluateSynonymInteger();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::NAME) {
        return AffectsClause::evaluateIntegerSynonym();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return AffectsClause::evaluateIntegerWildcard();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::INTEGER) {
        return AffectsClause::evaluateIntegerInteger();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME) {
        return AffectsClause::evaluateWildcardSynonym();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return AffectsClause::evaluateWildcardWildcard();
    } else {
        return AffectsClause::evaluateWildcardInteger();
    }
}

size_t AffectsClause::getPriority() {
    return priority;
}

std::set<std::string> AffectsClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

size_t AffectsClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

ResultTable AffectsClause::evaluateSynonymSynonym() {
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::AFFECTS, leftType, rightType);

    if (leftValue == rightValue) {
        std::unordered_set<std::string> leftAndRightEqualResults = ClauseUtils::processMapToSetFromFirst(results);
        return {leftValue, leftAndRightEqualResults};
    }

    std::vector<std::pair<std::string, std::string>> processedMap = ClauseUtils::processMapToVectorPair(results);
    return {leftValue, rightValue, processedMap};
}

ResultTable AffectsClause::evaluateSynonymWildcard() {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = DesignEntity::STMT;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::AFFECTS, leftType, rightType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

ResultTable AffectsClause::evaluateSynonymInteger() {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(RelationshipType::AFFECTS, leftType, right);
    return {leftValue, results};
}

ResultTable AffectsClause::evaluateIntegerSynonym() {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::AFFECTS, left, rightType);
    return {rightValue, results};
}

ResultTable AffectsClause::evaluateIntegerWildcard() {
    DesignEntity rightType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::AFFECTS, left, rightType);
    bool result = !results.empty();
    return {result};
}

ResultTable AffectsClause::evaluateIntegerInteger() {
    bool result = qpsClient.getRelationship(RelationshipType::AFFECTS, left, right);
    return {result};
}

ResultTable AffectsClause::evaluateWildcardSynonym() {
    DesignEntity leftType = DesignEntity::STMT;
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::AFFECTS, leftType, rightType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromSecond(results);
    return {rightValue, processedMap};
}

ResultTable AffectsClause::evaluateWildcardWildcard() {
    DesignEntity stmtType = DesignEntity::STMT;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::AFFECTS, stmtType, stmtType);
    bool result = !results.empty();
    return {result};
}

ResultTable AffectsClause::evaluateWildcardInteger() {
    DesignEntity leftType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(RelationshipType::AFFECTS, leftType, right);
    bool result = !results.empty();
    return {result};
}


