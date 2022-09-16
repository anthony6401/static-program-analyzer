#include "AssignPatternClause.h"
#include "iostream"

AssignPatternClause::AssignPatternClause(std::string assignSynonym, TokenObject left, TokenObject right,
                                         QPSClient qpsClient, Select synonym)
                                         : assignSynonym(assignSynonym), left(left), right(right), qpsClient(qpsClient), synonym(synonym) {}

RawResult AssignPatternClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::EXPRESSION) {
        return AssignPatternClause::evaluateSynonymExpression();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return AssignPatternClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::NAME_WITH_QUOTATION) {
        return AssignPatternClause::evaluateSynonymNameQuotes();
    } else if (leftType == TokenType::NAME && rightType == TokenType::SUBEXPRESSION) {
        return AssignPatternClause::evaluateSynonymSubExpression();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return AssignPatternClause::evaluateWildcardWildcard();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::EXPRESSION) {
        return AssignPatternClause::evaluateWildcardExpression();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME_WITH_QUOTATION) {
        return AssignPatternClause::evaluateWildcardNameQuotes();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::SUBEXPRESSION) {
        return AssignPatternClause::evaluateWildcardSubExpression();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::WILDCARD) {
        return AssignPatternClause::evaluateNameQuotesWildcard();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::EXPRESSION) {
        return AssignPatternClause::evaluateNameQuotesExpression();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::NAME_WITH_QUOTATION) {
        return AssignPatternClause::evaluateNameQuotesNameQuotes();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::SUBEXPRESSION) {
        return AssignPatternClause::evaluateNameQuotesSubExpression();
    } else {
        return {};
    }
}

size_t AssignPatternClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms + 1;
}

std::set<std::string> AssignPatternClause::getAllSynonyms() {
    std::set<std::string> synonyms = {assignSynonym};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    return synonyms;
}



RawResult AssignPatternClause::evaluateSynonymWildcard() {
    std::vector<std::pair<std::string, std::string>> results = qpsClient.getPatternPair(DesignEntity::ASSIGN, right);
    std::string leftValue = left.getValue();
    return {assignSynonym, leftValue, results};
}

RawResult AssignPatternClause::evaluateSynonymExpression() {
    std::vector<std::pair<std::string, std::string>> results = qpsClient.getPatternPair(DesignEntity::ASSIGN, right);
    std::string leftValue = left.getValue();
    return {assignSynonym, leftValue, results};
}

RawResult AssignPatternClause::evaluateSynonymNameQuotes() {
    std::vector<std::pair<std::string, std::string>> results = qpsClient.getPatternPair(DesignEntity::ASSIGN, right);
    std::string leftValue = left.getValue();
    return {assignSynonym, leftValue, results};
}

RawResult AssignPatternClause::evaluateSynonymSubExpression() {
    std::vector<std::pair<std::string, std::string>> results = qpsClient.getPatternPair(DesignEntity::ASSIGN, right);
    std::string leftValue = left.getValue();
    return {assignSynonym, leftValue, results};
}

RawResult AssignPatternClause::evaluateWildcardWildcard() {
    std::vector<std::pair<std::string, std::string>> results = qpsClient.getPatternPair(DesignEntity::ASSIGN, right);
    std::unordered_set<std::string> extractedAssignments; // {"1", "2", "3"....}
    for (auto pair : results) {
        extractedAssignments.insert(pair.first);
    }
    return {assignSynonym,  extractedAssignments};
}

RawResult AssignPatternClause::evaluateWildcardExpression() {
    std::vector<std::pair<std::string, std::string>> results = qpsClient.getPatternPair(DesignEntity::ASSIGN, right);
    std::unordered_set<std::string> extractedAssignments; // {"1", "2", "3"....}
    for (auto pair : results) {
        extractedAssignments.insert(pair.first);
    }
    return {assignSynonym,  extractedAssignments};
}

RawResult AssignPatternClause::evaluateWildcardNameQuotes() {
    std::vector<std::pair<std::string, std::string>> results = qpsClient.getPatternPair(DesignEntity::ASSIGN, right);
    std::unordered_set<std::string> extractedAssignments; // {"1", "2", "3"....}
    for (auto pair : results) {
        extractedAssignments.insert(pair.first);
    }
    return {assignSynonym,  extractedAssignments};
}

RawResult AssignPatternClause::evaluateWildcardSubExpression() {
    std::vector<std::pair<std::string, std::string>> results = qpsClient.getPatternPair(DesignEntity::ASSIGN, right);
    std::unordered_set<std::string> extractedAssignments; // {"1", "2", "3"....}
    for (auto pair : results) {
        extractedAssignments.insert(pair.first);
    }
    return {assignSynonym,  extractedAssignments};
}

RawResult AssignPatternClause::evaluateNameQuotesWildcard() {
    std::unordered_set<std::string> results = qpsClient.getPattern(DesignEntity::ASSIGN, left, right);
    return {assignSynonym,  results};
}

RawResult AssignPatternClause::evaluateNameQuotesExpression() {
    std::unordered_set<std::string> results = qpsClient.getPattern(DesignEntity::ASSIGN, left, right);
    return {assignSynonym,  results};
}

RawResult AssignPatternClause::evaluateNameQuotesNameQuotes() {
    std::unordered_set<std::string> results = qpsClient.getPattern(DesignEntity::ASSIGN, left, right);
    return {assignSynonym,  results};
}

RawResult AssignPatternClause::evaluateNameQuotesSubExpression() {
    std::unordered_set<std::string> results = qpsClient.getPattern(DesignEntity::ASSIGN, left, right);
    return {assignSynonym,  results};
}