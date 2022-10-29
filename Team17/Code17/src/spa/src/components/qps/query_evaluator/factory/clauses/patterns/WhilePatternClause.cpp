#include "WhilePatternClause.h"
#include <utility>

WhilePatternClause::WhilePatternClause(std::string whileSynonym, TokenObject firstArgument, QPSClient qpsClient)
        : whileSynonym(std::move(whileSynonym)), firstArgument(std::move(firstArgument)), qpsClient(qpsClient) {}

ResultTable WhilePatternClause::evaluateClause() {
    TokenType firstArgumentType = firstArgument.getTokenType();
    if (firstArgumentType == TokenType::NAME) {
        return WhilePatternClause::evaluateFirstArgAsSynonym();
    } else if (firstArgumentType == TokenType::WILDCARD) {
        return WhilePatternClause::evaluateFirstArgAsWildcard();
    } else {
        return WhilePatternClause::evaluateFirstArgAsNameQuotes();
    }
}

size_t WhilePatternClause::getPriority() {
    return priority;
}

size_t WhilePatternClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (firstArgument.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms + 1;
}
std::set<std::string> WhilePatternClause::getAllSynonyms() {
    std::set<std::string> synonyms = {whileSynonym};
    if (firstArgument.getTokenType() == TokenType::NAME) {
        synonyms.emplace(firstArgument.getValue());
    }
    return synonyms;
}

ResultTable WhilePatternClause::evaluateFirstArgAsSynonym() {
    std::string firstArgumentValue = firstArgument.getValue();
    std::vector<std::pair<std::string, std::string>> results = qpsClient.getContainerPatternPair(DesignEntity::WHILE);
    return {whileSynonym, firstArgumentValue, results};
}

ResultTable WhilePatternClause::evaluateFirstArgAsNameQuotes() {
    std::unordered_set<std::string> results = qpsClient.getContainerPattern(DesignEntity::WHILE, firstArgument);
    return {whileSynonym, results};
}


ResultTable WhilePatternClause::evaluateFirstArgAsWildcard() {
    std::vector<std::pair<std::string, std::string>> results = qpsClient.getContainerPatternPair(DesignEntity::WHILE);
    std::unordered_set<std::string> extractedWhile;
    for (const auto& pair : results) {
        extractedWhile.insert(pair.first);
    }
    return {whileSynonym, extractedWhile};
}


