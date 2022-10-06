#include "SelectTupleClause.h"
#include "components/pkb/pkb.h"
#include "components/pkb/clients/QPSClient.h"
#include "iostream"

SelectTupleClause::SelectTupleClause(std::vector<TokenObject> tuple, std::unordered_set<std::string> &synonymsInTable, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
        : tuple(tuple), synonymsInTable(synonymsInTable), synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

ResultTable SelectTupleClause::evaluateClause() {
    ResultTable resultTable;
    // TokenObjects can be synonyms of attributes
    for (auto tupleObject : tuple) {
        ResultTable intermediate;
        TokenType tupleObjectType = tupleObject.getTokenType();
        std::string tupleObjectValue = tupleObject.getValue();
        if (tupleObjectType == TokenType::NAME) {
            // If select synonym is found -> just select from table
            if (synonymsInTable.find(tupleObjectValue) != synonymsInTable.end()) {
                continue;
            } else {
                intermediate = SelectTupleClause::evaluateSynonymInTuple(tupleObjectValue);
            }
        } else if (tupleObjectType == TokenType::ATTRIBUTE) {

        }
        resultTable.combineResult(intermediate);
    }

    resultTable.setIsTupleResult();
    return resultTable;
}

ResultTable SelectTupleClause::evaluateSynonymInTuple(std::string synonym) {
    DesignEntity returnType = synonymToDesignEntityMap[synonym];
    std::unordered_set<std::string> results = qpsClient.getAllEntity(returnType);
    return {synonym, results};
}

ResultTable SelectTupleClause::evaluateAttributeInTuple() {
    return {};
}

size_t SelectTupleClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    for (auto tupleObject : tuple) {
        TokenType tupleObjectType = tupleObject.getTokenType();
        std::string tupleObjectValue = tupleObject.getValue();
        if (tupleObjectType == TokenType::NAME) {
            numberOfSynonyms++;
        }

        if (tupleObjectType == TokenType::ATTRIBUTE) {
            numberOfSynonyms++;
        }
    }
    return numberOfSynonyms;
}

std::set<std::string> SelectTupleClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    for (auto tupleObject : tuple) {
        TokenType tupleObjectType = tupleObject.getTokenType();
        std::string tupleObjectValue = tupleObject.getValue();
        if (tupleObjectType == TokenType::NAME) {
            synonyms.emplace(tupleObjectValue);
        }

        if (tupleObjectType == TokenType::ATTRIBUTE) {
            synonyms.emplace(tupleObjectValue);
        }
    }
    return synonyms;
}