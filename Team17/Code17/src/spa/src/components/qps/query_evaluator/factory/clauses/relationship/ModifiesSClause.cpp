#include "ModifiesSClause.h"

ModifiesSClause::ModifiesSClause(TokenObject left, TokenObject right, Select synonym,
                                 std::unordered_map<std::string, TokenType> synonymToDesignEntityMap,
                                 QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                 synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {};

RawResult ModifiesSClause::evaluateClause() {
//    TokenType leftType = left.getTokenType();
//    TokenType rightType = right.getTokenType();
//    if (leftType == TokenType::SYNONYM && rightType == TokenType::SYNONYM) {
//        ModifiesSClause::evaluateSynonymSynonym();
//    }
    std::unordered_set<std::string> result = {"x", "y", "z"};
    return {result};
}

TokenType ModifiesSClause::getRelationshipType() {
    return TokenType::MODIFIES;
}

RawResult ModifiesSClause::evaluateSynonymSynonym() {
    TokenType stmtType = synonymToDesignEntityMap[left.getValue()];
    // std::unordered_set<std::string> result = qpsClient.getAllRelationships(getRelationshipType(), stmtType);
    return {};
}


