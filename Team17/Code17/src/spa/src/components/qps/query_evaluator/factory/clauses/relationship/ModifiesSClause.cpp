#include "ModifiesSClause.h"

ModifiesSClause::ModifiesSClause(TokenObject left, TokenObject right, Select synonym,
                                 std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                                 QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                 synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {};

RawResult ModifiesSClause::evaluateClause() {
//    TokenType leftType = left.getTokenType();
//    TokenType rightType = right.getTokenType();
//    if (leftType == TokenType::SYNONYM && rightType == TokenType::SYNONYM) {
//        ModifiesSClause::evaluateSynonymSynonym();
//    }
    std::unordered_set<std::string> result = {"x", "y", "z"};
    return {};
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
    // API CALL
    return {};
}

RawResult ModifiesSClause::evaluateIntegerNameQuotes() {
    // API CALL
    return {};
}

