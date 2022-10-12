#include "UsesSClause.h"

#include <utility>
#include "iostream"
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

UsesSClause::UsesSClause(TokenObject left, TokenObject right,
                         std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
                         : left(std::move(left)), right(std::move(right)), synonymToDesignEntityMap(std::move(synonymToDesignEntityMap))
                         , qpsClient(qpsClient) {};


ResultTable UsesSClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return UsesSClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return UsesSClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::NAME_WITH_QUOTATION) {
        return UsesSClause::evaluateSynonymNameQuotes();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::NAME) {
        return UsesSClause::evaluateIntegerSynonym();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return UsesSClause::evaluateIntegerWildcard();
    } else {
        return UsesSClause::evaluateIntegerNameQuotes();
    }
}

size_t UsesSClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

std::set<std::string> UsesSClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

RelationshipType UsesSClause::getRelationshipType() {
    return RelationshipType::USES;
}


ResultTable UsesSClause::evaluateSynonymSynonym() {
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    DesignEntity stmtType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), stmtType, rightType);
    std::vector<std::pair<std::string, std::string>> processedMap = ClauseUtils::processMapToVectorPair(results);
    return {leftValue, rightValue, processedMap};
}

ResultTable UsesSClause::evaluateSynonymWildcard() {
    std::string leftValue = left.getValue();
    DesignEntity stmtType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = DesignEntity::VARIABLE;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), stmtType, rightType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

ResultTable UsesSClause::evaluateSynonymNameQuotes() {
    std::string leftValue = left.getValue();
    DesignEntity stmtType = synonymToDesignEntityMap[leftValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(getRelationshipType(), stmtType, right);
    return {leftValue, results};
}

ResultTable UsesSClause::evaluateIntegerSynonym() {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, rightType);
    return {rightValue, results};
}

ResultTable UsesSClause::evaluateIntegerWildcard() {
    DesignEntity rightType = DesignEntity::VARIABLE;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, rightType);
    bool result = !results.empty();
    return {result};
}

ResultTable UsesSClause::evaluateIntegerNameQuotes() {
    bool result = qpsClient.getRelationship(getRelationshipType(), left, right);
    return {result};
}
