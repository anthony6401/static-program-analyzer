#include "GroupedClause.h"
#include "memory"

GroupedClause::GroupedClause() : synonyms({}), clauses({}) {}

std::vector<std::shared_ptr<Clause>> GroupedClause::getClauses() {
    return clauses;
}

std::set<std::string> GroupedClause::getAllSynonyms() {
    return synonyms;
}

bool GroupedClause::hasCommonSynonymWithClause(std::shared_ptr<Clause> &clause) {
    std::set<std::string> synonymsOfClause = clause -> getAllSynonyms();
    auto synonymsIterator = synonyms.begin();
    auto clauseSynonymsIterator = synonymsOfClause.begin();
    while (synonymsIterator != synonyms.end() && clauseSynonymsIterator != synonymsOfClause.end()) {
        if (*synonymsIterator < *clauseSynonymsIterator) {
            synonymsIterator++;
        } else if (*clauseSynonymsIterator < *synonymsIterator) {
            clauseSynonymsIterator++;
        } else {
            return true;
        }
    }
    return false;
}

void GroupedClause::addClauseToGroup(std::shared_ptr<Clause> &clause) {
    std::set<std::string> synonymsOfClause = clause -> getAllSynonyms();
    for (const std::string& synonym : synonymsOfClause) {
        synonyms.insert(synonym);
    }

    clauses.emplace_back(clause);
}

bool GroupedClause::isEmpty() {
    return clauses.empty();
}

ResultTable GroupedClause::evaluateGroupedClause() {
    ResultTable evaluatedGroupRawResult;
    for (const auto& c : clauses) {
        ResultTable evaluatedClause = c -> evaluateClause();
        if (evaluatedClause.getIsFalseResult()) {
            return evaluatedClause;
        }
        evaluatedGroupRawResult.combineResult(evaluatedClause);
    }
    return evaluatedGroupRawResult;
}

void GroupedClause::mergeGroupedClause(GroupedClause &group) {
    auto synonymsOfMergingGroup = group.getAllSynonyms();
    auto clausesOfMergingGroup = group.getClauses();
    synonyms.insert(synonymsOfMergingGroup.begin(), synonymsOfMergingGroup.end());
    clauses.insert(clauses.end(), clausesOfMergingGroup.begin(), clausesOfMergingGroup.end());
}


bool GroupedClause::isConnected(GroupedClause &group) {
    auto synonymsOfMergingGroup = group.getAllSynonyms();
    auto synonymsIterator = synonyms.begin();
    auto mergingGroupSynonymsIterator = synonymsOfMergingGroup.begin();
    while (synonymsIterator != synonyms.end() && mergingGroupSynonymsIterator != synonymsOfMergingGroup.end()) {
        if (*synonymsIterator < *mergingGroupSynonymsIterator) {
            synonymsIterator++;
        } else if (*mergingGroupSynonymsIterator < *synonymsIterator) {
            mergingGroupSynonymsIterator++;
        } else {
            return true;
        }
    }
    return false;
}
