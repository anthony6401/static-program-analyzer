#include "GroupedClause.h"
#include "memory"
#include <algorithm>
#include "optimizer/ClauseSorter.h"

GroupedClause::GroupedClause() : synonyms({}), clauses({}) {}

std::vector<std::shared_ptr<Clause>> GroupedClause::getClauses() {
    return clauses;
}

std::set<std::string> GroupedClause::getAllSynonyms() {
    return synonyms;
}

size_t GroupedClause::getNumberOfSynonyms() const {
     return synonyms.size();
}

size_t GroupedClause::getPriority() const {
    return priority;
}

ResultTable GroupedClause::evaluateGroupedClause() {

    std::sort(clauses.begin(), clauses.end(), ClauseSorter());

    ResultTable evaluatedGroupResult;
    for (const auto& c : clauses) {
        ResultTable evaluatedClause = c -> evaluateClause();
        if (evaluatedClause.getIsFalseResult()) {
            return evaluatedClause;
        } else {
            evaluatedGroupResult.combineResult(evaluatedClause);
        }
    }
    return evaluatedGroupResult;
}

void GroupedClause::mergeGroupedClause(GroupedClause &group) {
    auto synonymsOfMergingGroup = group.getAllSynonyms();
    synonyms.insert(synonymsOfMergingGroup.begin(), synonymsOfMergingGroup.end());

    auto clausesOfMergingGroup = group.getClauses();
    clauses.insert(clauses.end(), clausesOfMergingGroup.begin(), clausesOfMergingGroup.end());

    priority += group.getPriority();
}

bool GroupedClause::hasCommonSynonym(std::set<std::string> synonymsOfClause) {
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
    priority += clause->getPriority();
}

bool GroupedClause::isEmpty() {
    return clauses.empty();
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
