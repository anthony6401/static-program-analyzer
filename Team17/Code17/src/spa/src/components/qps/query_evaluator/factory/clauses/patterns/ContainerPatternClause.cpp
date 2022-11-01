#include "ContainerPatternClause.h"

ContainerPatternClause::ContainerPatternClause(std::string synonym, DesignEntity designEntityType, TokenObject firstArgument, QPSClient qpsClient)
        : synonym(std::move(synonym)), designEntityType(designEntityType), firstArgument(std::move(firstArgument)), qpsClient(qpsClient) {}

ResultTable ContainerPatternClause::evaluateClause() {
    TokenType firstArgumentType = firstArgument.getTokenType();
    if (firstArgumentType == TokenType::NAME) {
        return ContainerPatternClause::evaluateFirstArgAsSynonym(designEntityType);
    } else if (firstArgumentType == TokenType::WILDCARD) {
        return ContainerPatternClause::evaluateFirstArgAsWildcard(designEntityType);
    } else {
        return ContainerPatternClause::evaluateFirstArgAsNameQuotes(designEntityType);
    }
}

size_t ContainerPatternClause::getPriority() {
    return priority;
}

size_t ContainerPatternClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (firstArgument.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms + 1;
}
std::set<std::string> ContainerPatternClause::getAllSynonyms() {
    std::set<std::string> synonyms = {synonym};
    if (firstArgument.getTokenType() == TokenType::NAME) {
        synonyms.emplace(firstArgument.getValue());
    }
    return synonyms;
}

ResultTable ContainerPatternClause::evaluateFirstArgAsSynonym(DesignEntity designEntityType) {
    std::string firstArgumentValue = firstArgument.getValue();
    std::vector<std::pair<std::string, std::string>> results = qpsClient.getContainerPatternPair(designEntityType);
    return {synonym, firstArgumentValue, results};
}

ResultTable ContainerPatternClause::evaluateFirstArgAsNameQuotes(DesignEntity designEntityType) {
    std::unordered_set<std::string> results = qpsClient.getContainerPattern(designEntityType, firstArgument);
    return {synonym, results};
}


ResultTable ContainerPatternClause::evaluateFirstArgAsWildcard(DesignEntity designEntityType) {
    std::unordered_set<std::string> results = qpsClient.getPatternContainerWildcard(designEntityType);
    return {synonym, results};
}

