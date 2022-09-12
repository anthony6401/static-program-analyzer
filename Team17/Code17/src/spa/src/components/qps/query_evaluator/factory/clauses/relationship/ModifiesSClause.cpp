#include "ModifiesSClause.h"
#include "iostream"

ModifiesSClause::ModifiesSClause(TokenObject left, TokenObject right, Select synonym,
                                 std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                                 QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                 synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {};

RawResult ModifiesSClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::SYNONYM && rightType == TokenType::SYNONYM) {
        return ModifiesSClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::WILDCARD) {
        return ModifiesSClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::NAME_WITH_QUOTATION) {
        return ModifiesSClause::evaluateSynonymNameQuotes();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::SYNONYM) {
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
    if (left.getTokenType() == TokenType::SYNONYM) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::SYNONYM) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

size_t ModifiesSClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::SYNONYM) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::SYNONYM) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

TokenType ModifiesSClause::getRelationshipType() {
    return TokenType::MODIFIES;
}

RawResult ModifiesSClause::evaluateSynonymSynonym() {
    DesignEntity stmtType = synonymToDesignEntityMap[left.getValue()];
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    // API CALL
    return {};
}

RawResult ModifiesSClause::evaluateSynonymWildcard() {
    DesignEntity stmtType = synonymToDesignEntityMap[left.getValue()];
    // API CALL
    return {};
}

RawResult ModifiesSClause::evaluateSynonymNameQuotes() {
    DesignEntity stmtType = synonymToDesignEntityMap[left.getValue()];
    // API CALL
    return {};
}

RawResult ModifiesSClause::evaluateIntegerSynonym() {
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    // API CALL
    return {};
}

RawResult ModifiesSClause::evaluateIntegerWildcard() {
    std::cout << "In Integer WildCard" << std::endl;
    return {};
}

RawResult ModifiesSClause::evaluateIntegerNameQuotes() {
    std::cout << "In Integer Name Quotes" << std::endl;
    // API CALL
    return {};
}

