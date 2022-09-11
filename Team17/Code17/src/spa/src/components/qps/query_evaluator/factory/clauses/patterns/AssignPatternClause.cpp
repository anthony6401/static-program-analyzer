#include "AssignPatternClause.h"

AssignPatternClause::AssignPatternClause(std::string assignSynonym, TokenObject left, TokenObject right,
                                         QPSClient qpsClient, Select synonym)
                                         : assignSynonym(assignSynonym), left(left), right(right), qpsClient(qpsClient), synonym(synonym) {}

RawResult AssignPatternClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::SYNONYM && rightType == TokenType::EXPRESSION) {
        return AssignPatternClause::evaluateSynonymExpression();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::WILDCARD) {
        return AssignPatternClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::NAME_WITH_QUOTATION) {
        return AssignPatternClause::evaluateSynonymNameQuotes();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::SUBEXPRESSION) {
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

RawResult AssignPatternClause::evaluateSynonymWildcard() {
    return {};
}

RawResult AssignPatternClause::evaluateSynonymExpression() {
    return {};
}

RawResult AssignPatternClause::evaluateSynonymNameQuotes() {
    return {};
}

RawResult AssignPatternClause::evaluateSynonymSubExpression() {
    return {};
}

RawResult AssignPatternClause::evaluateWildcardWildcard() {
    return {};
}

RawResult AssignPatternClause::evaluateWildcardExpression() {
    return {};
}

RawResult AssignPatternClause::evaluateWildcardNameQuotes() {
    return {};
}

RawResult AssignPatternClause::evaluateWildcardSubExpression() {
    return {};
}

RawResult AssignPatternClause::evaluateNameQuotesWildcard() {
    return {};
}

RawResult AssignPatternClause::evaluateNameQuotesExpression() {
    return {};
}

RawResult AssignPatternClause::evaluateNameQuotesNameQuotes() {
    return {};
}

RawResult AssignPatternClause::evaluateNameQuotesSubExpression() {
    return {};
}