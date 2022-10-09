#include "IfPatternClause.h"

IfPatternClause::IfPatternClause(std::string ifSynonym, TokenObject firstArgument, QPSClient qpsClient)
        : ifSynonym(ifSynonym), firstArgument(firstArgument), qpsClient(qpsClient) {}

ResultTable IfPatternClause::evaluateClause() {
    TokenType firstArgumentType = firstArgument.getTokenType();
    if (firstArgumentType == TokenType::NAME) {
        return IfPatternClause::evaluateFirstArgAsSynonym();
    } else if (firstArgumentType == TokenType::WILDCARD) {
        return IfPatternClause::evaluateFirstArgAsWildcard();
    } else {
        return IfPatternClause::evaluateFirstArgAsNameQuotes();
    }
}

size_t IfPatternClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (firstArgument.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms + 1;
}
std::set<std::string> IfPatternClause::getAllSynonyms() {
    std::set<std::string> synonyms = {ifSynonym};
    if (firstArgument.getTokenType() == TokenType::NAME) {
        synonyms.emplace(firstArgument.getValue());
    }
    return synonyms;
}

ResultTable IfPatternClause::evaluateFirstArgAsSynonym() {
    std::string firstArgumentValue = firstArgument.getValue();
    std::vector<std::pair<std::string, std::string>> results = qpsClient.getContainerPatternPair(DesignEntity::IF);
    return {ifSynonym, firstArgumentValue, results};
}

ResultTable IfPatternClause::evaluateFirstArgAsNameQuotes() {
    std::unordered_set<std::string> results = qpsClient.getContainerPattern(DesignEntity::IF, firstArgument);
    return {ifSynonym, results};
}


ResultTable IfPatternClause::evaluateFirstArgAsWildcard() {
    std::vector<std::pair<std::string, std::string>> results = qpsClient.getContainerPatternPair(DesignEntity::IF);
    std::unordered_set<std::string> extractedIfs;
    for (auto pair : results) {
        extractedIfs.insert(pair.first);
    }
    return {ifSynonym, extractedIfs};
}

