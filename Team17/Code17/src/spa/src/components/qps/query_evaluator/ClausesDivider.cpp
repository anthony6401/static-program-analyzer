#include "ClausesDivider.h"
#include "iostream"

ClauseDivider::ClauseDivider() : noSynonymsPresent({}), commonSynonymsGroups({}), selectSynonymPresentGroups({}), selectSynonymNotPresentGroups({}) {}

GroupedClause ClauseDivider::getNoSynonymsPresent() {
    return noSynonymsPresent;
}

std::vector<GroupedClause> ClauseDivider::getSelectSynonymPresentGroups() {
    return selectSynonymPresentGroups;
}

std::vector<GroupedClause> ClauseDivider::getSelectSynonymNotPresentGroups() {
    return selectSynonymNotPresentGroups;
}

void ClauseDivider::divideCommonSynonymGroupsBySelect(std::shared_ptr<Clause> &selectClause) {
    for (auto &gc : commonSynonymsGroups) {
        if (gc.hasCommonSynonymWithClause(selectClause)) {
            selectSynonymPresentGroups.emplace_back(gc);
        } else {
            selectSynonymNotPresentGroups.emplace_back(gc);
        }
    }
}

void ClauseDivider::addClauseToDivider(std::shared_ptr<Clause> &clause) {
    if (clause -> getNumberOfSynonyms() == 0) {
        noSynonymsPresent.addClauseToGroup(clause);
    } else {
        for (auto &gc : commonSynonymsGroups) {
            if (gc.hasCommonSynonymWithClause(clause)) {
                gc.addClauseToGroup(clause);
                return;
            }
        }

        GroupedClause clauseGroup;
        clauseGroup.addClauseToGroup(clause);
        commonSynonymsGroups.emplace_back(clauseGroup);
    }
}
