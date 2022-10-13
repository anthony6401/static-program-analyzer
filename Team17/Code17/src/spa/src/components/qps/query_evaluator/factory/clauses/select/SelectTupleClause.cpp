#include "SelectTupleClause.h"

#include <utility>
#include "components/pkb/pkb.h"
#include "components/pkb/clients/QPSClient.h"
#include "iostream"

SelectTupleClause::SelectTupleClause(std::vector<TokenObject> tuple, std::unordered_set<std::string> &synonymsInTable, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
        : tuple(std::move(tuple)), synonymsInTable(synonymsInTable), synonymToDesignEntityMap(std::move(synonymToDesignEntityMap)), qpsClient(qpsClient) {}

ResultTable SelectTupleClause::evaluateClause() {
    ResultTable resultTable;
    for (auto & i : tuple) {
        ResultTable intermediate;
        TokenType tupleObjectType = i.getTokenType();
        std::string tupleObjectValue = i.getValue();
        DesignEntity returnType = synonymToDesignEntityMap[tupleObjectValue];

        if (tupleObjectType == TokenType::NAME || tupleObjectType == TokenType::ATTRIBUTE_SYNONYM) {
            bool isSynonymInTable = synonymsInTable.find(tupleObjectValue) != synonymsInTable.end();
            if (isSynonymInTable) {
                continue;
            } else {
                intermediate = SelectTupleClause::evaluateSynonymOrAttributeInTuple(tupleObjectValue, returnType);
            }
        }

        resultTable.combineResult(intermediate);
    }

    return resultTable;
}


ResultTable SelectTupleClause::evaluateSynonymOrAttributeInTuple(std::string synonym, DesignEntity returnType) {
    std::unordered_set<std::string> results = qpsClient.getAllEntity(returnType);
    return {synonym, results};
}

size_t SelectTupleClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    for (auto tupleObject : tuple) {
        TokenType tupleObjectType = tupleObject.getTokenType();
        std::string tupleObjectValue = tupleObject.getValue();
        if (tupleObjectType == TokenType::NAME) {
            numberOfSynonyms++;
        }

        if (tupleObjectType == TokenType::ATTRIBUTE_SYNONYM) {
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

        if (tupleObjectType == TokenType::ATTRIBUTE_SYNONYM) {
            synonyms.emplace(tupleObjectValue);
        }
    }
    return synonyms;
}