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

size_t SelectBooleanClause::getPriority() {
    return 0;
}
