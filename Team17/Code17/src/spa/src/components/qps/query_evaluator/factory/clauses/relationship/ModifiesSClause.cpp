#include "ModifiesSClause.h"
#include "iostream"

ModifiesSClause::ModifiesSClause(TokenObject left, TokenObject right, Select synonym,
                                 std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                                 QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                 synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {};

RawResult ModifiesSClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return ModifiesSClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return ModifiesSClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::NAME_WITH_QUOTATION) {
        return ModifiesSClause::evaluateSynonymNameQuotes();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::NAME) {
        return ModifiesSClause::evaluateIntegerSynonym();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return ModifiesSClause::evaluateIntegerWildcard();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::NAME_WITH_QUOTATION) {
        return ModifiesSClause::evaluateIntegerNameQuotes();
    } else {
        return {};
    }
}

std::set<std::string> ModifiesSClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

size_t ModifiesSClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

RelationshipType ModifiesSClause::getRelationshipType() {
    return RelationshipType::MODIFIES;
}

std::vector<std::pair<std::string, std::string>> processMap(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::vector<std::pair<std::string, std::string>> processedResult;
    for (auto entry : results) {
        std::string firstSynonym = entry.first;
        std::unordered_set<std::string> secondSynonymList = entry.second;
        for (auto secondSynonym : secondSynonymList) {
            std::pair<std::string, std::string> newPair = {firstSynonym, secondSynonym};
            processedResult.emplace_back(newPair);
        }
    }
    return processedResult;
}

RawResult ModifiesSClause::evaluateSynonymSynonym() {
    DesignEntity stmtType = synonymToDesignEntityMap[left.getValue()];
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), stmtType, rightType);
    return {"a", "v", {{"1", "x"}, {"2", "y"}}};
}

RawResult ModifiesSClause::evaluateSynonymWildcard() {
    std::cout << "----- ModifiesS: Synonym Wildcard -------" << std::endl;
    DesignEntity stmtType = synonymToDesignEntityMap[left.getValue()];
    // API CALL
    return {"a", {"1", "3"}};
}

RawResult ModifiesSClause::evaluateSynonymNameQuotes() {
    DesignEntity stmtType = synonymToDesignEntityMap[left.getValue()];
    // API CALL
    return {};
}

RawResult ModifiesSClause::evaluateIntegerSynonym() {
    std::cout << "----- ModifiesS: Integer Synonym -------" << std::endl;
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    // API CALL
    return {"v", {"x"}};
}

RawResult ModifiesSClause::evaluateIntegerWildcard() {
    // Returns boolean
    std::cout << "----- ModifiesS: Integer Wildcard -------" << std::endl;
    return {false};
}

RawResult ModifiesSClause::evaluateIntegerNameQuotes() {
    // Returns boolean
    std::cout << "----- ModifiesS: Integer Name Quotes -------" << std::endl;
    // API CALL
    return {false};
}

