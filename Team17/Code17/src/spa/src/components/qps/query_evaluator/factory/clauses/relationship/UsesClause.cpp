#include "UsesClause.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

UsesClause::UsesClause(TokenObject left, TokenObject right,
                         std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
        : left(std::move(left)), right(std::move(right)), synonymToDesignEntityMap(std::move(synonymToDesignEntityMap))
        , qpsClient(qpsClient) {};


ResultTable UsesClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return UsesClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return UsesClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::NAME_WITH_QUOTATION) {
        return UsesClause::evaluateSynonymNameQuotes();
    } else if ((leftType == TokenType::INTEGER || leftType == TokenType::NAME_WITH_QUOTATION) && rightType == TokenType::NAME) {
        return UsesClause::evaluateSecondAsSynonym();
    } else if ((leftType == TokenType::INTEGER || leftType == TokenType::NAME_WITH_QUOTATION) && rightType == TokenType::WILDCARD) {
        return UsesClause::evaluateSecondAsWildcard();
    } else {
        return UsesClause::evaluateWithoutSynonymOrWildCard();
    }
}

size_t UsesClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

std::set<std::string> UsesClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}


ResultTable UsesClause::evaluateSynonymSynonym() {
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::USES, leftType, rightType);
    std::vector<std::pair<std::string, std::string>> processedMap = ClauseUtils::processMapToVectorPair(results);
    return {leftValue, rightValue, processedMap};
}

ResultTable UsesClause::evaluateSynonymWildcard() {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = DesignEntity::VARIABLE;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::USES, leftType, rightType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

ResultTable UsesClause::evaluateSynonymNameQuotes() {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(RelationshipType::USES, leftType, right);
    return {leftValue, results};
}

ResultTable UsesClause::evaluateSecondAsSynonym() {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::USES, left, rightType);
    return {rightValue, results};
}

ResultTable UsesClause::evaluateSecondAsWildcard() {
    DesignEntity rightType = DesignEntity::VARIABLE;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::USES, left, rightType);
    bool result = !results.empty();
    return {result};
}

ResultTable UsesClause::evaluateWithoutSynonymOrWildCard() {
    bool result = qpsClient.getRelationship(RelationshipType::USES, left, right);
    return {result};
}