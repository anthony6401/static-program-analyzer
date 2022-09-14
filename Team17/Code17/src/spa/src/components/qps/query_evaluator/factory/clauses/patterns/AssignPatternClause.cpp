#include "AssignPatternClause.h"
#include "iostream"

AssignPatternClause::AssignPatternClause(std::string assignSynonym, TokenObject left, TokenObject right,
                                         QPSClient qpsClient, Select synonym)
                                         : assignSynonym(assignSynonym), left(left), right(right), qpsClient(qpsClient), synonym(synonym) {}

RawResult AssignPatternClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::EXPRESSION) {
        std::cout << "----- in evaluate clause method for assign name expr -------" << std::endl;
        return AssignPatternClause::evaluateSynonymExpression();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        std::cout << "----- in evaluate clause method for assign name wildcard -------" << std::endl;
        return AssignPatternClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::NAME_WITH_QUOTATION) {
        std::cout << "----- in evaluate clause method for assign name name quote -------" << std::endl;
        return AssignPatternClause::evaluateSynonymNameQuotes();
    } else if (leftType == TokenType::NAME && rightType == TokenType::SUBEXPRESSION) {
        std::cout << "----- in evaluate clause method for assign name subexpr -------" << std::endl;
        return AssignPatternClause::evaluateSynonymSubExpression();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        std::cout << "----- in evaluate clause method for assign wildcard wildcard -------" << std::endl;
        return AssignPatternClause::evaluateWildcardWildcard();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::EXPRESSION) {
        std::cout << "----- in evaluate clause method for assign wildcard expr -------" << std::endl;
        return AssignPatternClause::evaluateWildcardExpression();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME_WITH_QUOTATION) {
        std::cout << "----- in evaluate clause method for assign wildcard name quote -------" << std::endl;
        return AssignPatternClause::evaluateWildcardNameQuotes();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::SUBEXPRESSION) {
        std::cout << "----- in evaluate clause method for assign wildcard subexpr -------" << std::endl;
        return AssignPatternClause::evaluateWildcardSubExpression();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::WILDCARD) {
        std::cout << "----- in evaluate clause method for assign name quote wildcard -------" << std::endl;
        return AssignPatternClause::evaluateNameQuotesWildcard();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::EXPRESSION) {
        std::cout << "----- in evaluate clause method for assign name quote expr -------" << std::endl;
        return AssignPatternClause::evaluateNameQuotesExpression();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::NAME_WITH_QUOTATION) {
        std::cout << "----- in evaluate clause method for assign name quote name quote -------" << std::endl;
        return AssignPatternClause::evaluateNameQuotesNameQuotes();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::SUBEXPRESSION) {
        std::cout << "----- in evaluate clause method for assign name quote subexpr -------" << std::endl;
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
    for (auto c : synonyms) {
        std::cout << "pattern syn " << c << std::endl;
    }
    return synonyms;
}

RawResult AssignPatternClause::evaluateSynonymWildcard() {
    std::cout << "----- Assign: synonym wild card -------" << std::endl;
    return {"a", "v", {{"1", "x"}, {"2", "y"}}};
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
    std::cout << "----- Assign: wild card wild card -------" << std::endl;
    return {"a", {"10", "11", "12", "13"}};
}

RawResult AssignPatternClause::evaluateWildcardExpression() {
    return {};
}

RawResult AssignPatternClause::evaluateWildcardNameQuotes() {
    std::cout << "----- Assign: wild card name quotes -------" << std::endl;
    return {"a", {}};
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
    std::cout << "----- Assign: Name quote name quote -------" << std::endl;
    return {"a", {}};
}

RawResult AssignPatternClause::evaluateNameQuotesSubExpression() {
    return {};
}