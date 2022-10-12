#include "UsesPClause.h"
#include "iostream"
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

UsesPClause::UsesPClause(TokenObject left, TokenObject right,
                         std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) :
        left(left), right(right),
        synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {};

ResultTable UsesPClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return UsesPClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return UsesPClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::NAME_WITH_QUOTATION) {
        return UsesPClause::evaluateSynonymNameQuotes();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::NAME) {
        return UsesPClause::evaluateNameQuotesSynonym();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::WILDCARD) {
        return UsesPClause::evaluateNameQuotesWildcard();
    } else {
        return UsesPClause::evaluateNameQuotesNameQuotes();
    }
}

size_t UsesPClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

std::set<std::string> UsesPClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

RelationshipType UsesPClause::getRelationshipType() {
    return RelationshipType::USES;
}

ResultTable UsesPClause::evaluateSynonymSynonym() {
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    DesignEntity stmtType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), stmtType, rightType);
    std::vector<std::pair<std::string, std::string>> processedMap = ClauseUtils::processMapToVectorPair(results);
    return {leftValue, rightValue, processedMap};
}

ResultTable UsesPClause::evaluateSynonymWildcard() {
    DesignEntity stmtType = synonymToDesignEntityMap[left.getValue()];
    DesignEntity rightType = DesignEntity::VARIABLE;
    std::string leftValue = left.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), stmtType, rightType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

ResultTable UsesPClause::evaluateSynonymNameQuotes() {
    DesignEntity stmtType = synonymToDesignEntityMap[left.getValue()];
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(getRelationshipType(), stmtType, right);
    return {leftValue, results};
}

ResultTable UsesPClause::evaluateNameQuotesSynonym() {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, rightType);
    return {rightValue, results};
}

ResultTable UsesPClause::evaluateNameQuotesWildcard() {
    DesignEntity rightType = DesignEntity::VARIABLE;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, rightType);
    bool result = !results.empty();
    return {result}; //true
}

ResultTable UsesPClause::evaluateNameQuotesNameQuotes() {
    bool result = qpsClient.getRelationship(getRelationshipType(), left, right);
    return {result};
}


