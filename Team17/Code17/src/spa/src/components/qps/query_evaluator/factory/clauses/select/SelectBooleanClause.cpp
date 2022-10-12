#include "SelectBooleanClause.h"

SelectBooleanClause::SelectBooleanClause() {}

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
