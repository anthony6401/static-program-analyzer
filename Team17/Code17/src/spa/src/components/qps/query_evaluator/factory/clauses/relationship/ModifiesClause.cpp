#include "ModifiesClause.h"
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

ModifiesClause::ModifiesClause(TokenObject left, TokenObject right,
                       std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
        : left(std::move(left)), right(std::move(right)), synonymToDesignEntityMap(std::move(synonymToDesignEntityMap))
        , qpsClient(qpsClient) {};


ResultTable ModifiesClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return ModifiesClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return ModifiesClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::NAME_WITH_QUOTATION) {
        return ModifiesClause::evaluateSynonymNameQuotes();
    } else if ((leftType == TokenType::INTEGER || leftType == TokenType::NAME_WITH_QUOTATION) && rightType == TokenType::NAME) {
        return ModifiesClause::evaluateSecondAsSynonym();
    } else if ((leftType == TokenType::INTEGER || leftType == TokenType::NAME_WITH_QUOTATION) && rightType == TokenType::WILDCARD) {
        return ModifiesClause::evaluateSecondAsWildcard();
    } else {
        return ModifiesClause::evaluateWithoutSynonymOrWildCard();
    }
}

size_t ModifiesClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

std::set<std::string> ModifiesClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}


ResultTable ModifiesClause::evaluateSynonymSynonym() {
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::MODIFIES, leftType, rightType);
    std::vector<std::pair<std::string, std::string>> processedMap = ClauseUtils::processMapToVectorPair(results);
    return {leftValue, rightValue, processedMap};
}

ResultTable ModifiesClause::evaluateSynonymWildcard() {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = DesignEntity::VARIABLE;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::MODIFIES, leftType, rightType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

ResultTable ModifiesClause::evaluateSynonymNameQuotes() {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(RelationshipType::MODIFIES, leftType, right);
    return {leftValue, results};
}

ResultTable ModifiesClause::evaluateSecondAsSynonym() {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::MODIFIES, left, rightType);
    return {rightValue, results};
}

ResultTable ModifiesClause::evaluateSecondAsWildcard() {
    DesignEntity rightType = DesignEntity::VARIABLE;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::MODIFIES, left, rightType);
    bool result = !results.empty();
    return {result};
}

ResultTable ModifiesClause::evaluateWithoutSynonymOrWildCard() {
    bool result = qpsClient.getRelationship(RelationshipType::MODIFIES, left, right);
    return {result};
}