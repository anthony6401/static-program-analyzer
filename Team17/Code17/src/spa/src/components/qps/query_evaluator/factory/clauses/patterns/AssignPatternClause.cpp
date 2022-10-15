#include "AssignPatternClause.h"
#include <utility>

AssignPatternClause::AssignPatternClause(std::string assignSynonym, TokenObject left, TokenObject right,
                                         QPSClient qpsClient)
                                         : assignSynonym(std::move(assignSynonym)), left(std::move(left)), right(std::move(right)), qpsClient(qpsClient) {}

ResultTable AssignPatternClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    if (leftType == TokenType::NAME) {
        return AssignPatternClause::evaluateFirstAsSynonym();
    } else if (leftType == TokenType::WILDCARD) {
        return AssignPatternClause::evaluateFirstAsWildcard();
    } else {
        return AssignPatternClause::evaluateFirstAsNameQuotes();
    }
}

size_t AssignPatternClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms + 1;
}

std::set<std::string> AssignPatternClause::getAllSynonyms() {
    std::set<std::string> synonyms = {assignSynonym};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    return synonyms;
}

ResultTable AssignPatternClause::evaluateFirstAsSynonym() {
    std::vector<std::pair<std::string, std::string>> results = qpsClient.getPatternPair(DesignEntity::ASSIGN, right);
    std::string leftValue = left.getValue();
    return {assignSynonym, leftValue, results};
}


ResultTable AssignPatternClause::evaluateFirstAsWildcard() {
    std::vector<std::pair<std::string, std::string>> results = qpsClient.getPatternPair(DesignEntity::ASSIGN, right);
    std::unordered_set<std::string> extractedAssignments;
    for (const auto& pair : results) {
        extractedAssignments.insert(pair.first);
    }
    return {assignSynonym,  extractedAssignments};
}

ResultTable AssignPatternClause::evaluateFirstAsNameQuotes() {
    std::unordered_set<std::string> results = qpsClient.getPattern(DesignEntity::ASSIGN, left, right);
    return {assignSynonym,  results};
}

