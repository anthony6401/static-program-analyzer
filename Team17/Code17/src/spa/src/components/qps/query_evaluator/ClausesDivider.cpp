#include "ClausesDivider.h"
#include "iostream"

ClauseDivider::ClauseDivider() : noSynonymsPresent({}), commonSynonymsGroups({}), selectSynonymPresentGroups({}), selectSynonymNotPresentGroups({}) {}

void ClauseDivider::addClauseToDivider(std::shared_ptr<Clause> clause) {
    if (clause -> getNumberOfSynonyms() == 0) {
        noSynonymsPresent.addClauseToGroup(clause);
    } else { // 1 or 2 synonyms
        for (auto &gc : commonSynonymsGroups) {
            if (gc.hasCommonSynonymWithClause(clause)) {
                gc.addClauseToGroup(clause);
                return;
            }
        }

        // Create new group if it has no common synonym with existing groups
        GroupedClause clauseGroup;
        clauseGroup.addClauseToGroup(clause);
        commonSynonymsGroups.emplace_back(clauseGroup);
    }
}
GroupedClause ClauseDivider::getNoSynonymsPresent() {
    return noSynonymsPresent;
}

std::vector<GroupedClause> ClauseDivider::getSelectSynonymPresentGroups() {
    return selectSynonymPresentGroups;
}

std::vector<GroupedClause> ClauseDivider::getSelectSynonymNotPresentGroups() {
    return selectSynonymNotPresentGroups;
}


void ClauseDivider::divideCommonSynonymGroupsBySelect(std::shared_ptr<Clause> selectClause) {
    for (auto gc : commonSynonymsGroups) {
        if (gc.hasCommonSynonymWithClause(selectClause)) {
            selectSynonymPresentGroups.emplace_back(gc);
        } else {
            selectSynonymNotPresentGroups.emplace_back(gc);
        }
    }
}