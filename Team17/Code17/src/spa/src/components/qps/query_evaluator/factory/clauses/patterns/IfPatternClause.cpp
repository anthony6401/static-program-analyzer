#include "IfPatternClause.h"

IfPatternClause::IfPatternClause(std::string ifSynonym, TokenObject firstArgument, QPSClient qpsClient)
        : ifSynonym(ifSynonym), firstArgument(firstArgument), qpsClient(qpsClient) {}

ResultTable IfPatternClause::evaluateClause() {
    TokenType firstArgumentType = firstArgument.getTokenType();
    if (firstArgumentType == TokenType::NAME || firstArgumentType == TokenType::WILDCARD) {

    } else {

    }

}

size_t IfPatternClause::getNumberOfSynonyms() {

}
std::set<std::string> IfPatternClause::getAllSynonyms() {

}

ResultTable IfPatternClause::evaluateFirstArgAsSynonym() {

}

ResultTable IfPatternClause::evaluateFirstArgAsNameQuotes() {

}


ResultTable IfPatternClause::evaluateFirstArgAsWildcard() {

}

