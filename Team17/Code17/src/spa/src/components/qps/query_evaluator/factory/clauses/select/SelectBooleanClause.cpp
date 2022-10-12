#include "SelectBooleanClause.h"

SelectBooleanClause::SelectBooleanClause() = default;

ResultTable SelectBooleanClause::evaluateClause() {
    ResultTable resultTable;
    return resultTable;
}

size_t SelectBooleanClause::getNumberOfSynonyms() {
    return 0;
}

std::set<std::string> SelectBooleanClause::getAllSynonyms() {
    return {};
}
