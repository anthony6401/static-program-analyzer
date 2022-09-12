#include "UsesSClause.h"

UsesSClause::UsesSClause(TokenObject left, TokenObject right, Select synonym,
                         std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
                         : left(left), right(right), synonym(synonym), synonymToDesignEntityMap(synonymToDesignEntityMap)
                         , qpsClient(qpsClient) {};


RawResult UsesSClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::SYNONYM && rightType == TokenType::SYNONYM) {
        return UsesSClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::WILDCARD) {
        return UsesSClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::NAME_WITH_QUOTATION) {
        return UsesSClause::evaluateSynonymNameQuotes();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::SYNONYM) {
        return UsesSClause::evaluateIntegerSynonym();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return UsesSClause::evaluateIntegerWildcard();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::NAME_WITH_QUOTATION) {
        return UsesSClause::evaluateIntegerNameQuotes();
    } else {
        return {};
    }
}

size_t UsesSClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::SYNONYM) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::SYNONYM) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

std::set<std::string> UsesSClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::SYNONYM) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::SYNONYM) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

RawResult UsesSClause::evaluateSynonymSynonym() {
    DesignEntity stmtType = synonymToDesignEntityMap[left.getValue()];
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    std::unordered_map<std::string, std::unordered_set<std::string>> result;
    // API CALL
    return {};
}

RawResult UsesSClause::evaluateSynonymWildcard() {
    DesignEntity stmtType = synonymToDesignEntityMap[left.getValue()];
    // API CALL
    return {};
}

RawResult UsesSClause::evaluateSynonymNameQuotes() {
    DesignEntity stmtType = synonymToDesignEntityMap[left.getValue()];
    // API CALL
    return {};
}

RawResult UsesSClause::evaluateIntegerSynonym() {
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    // API CALL
    return {};
}

RawResult UsesSClause::evaluateIntegerWildcard() {
    // API CALL
    return {};
}

RawResult UsesSClause::evaluateIntegerNameQuotes() {
    // API CALL
    return {};
}


TokenType UsesSClause::getRelationshipType() {
    return TokenType::USES;
}
