#include "ClausesDivider.h"
#include "iostream"

ClauseDivider::ClauseDivider() : noSynonymsPresent({}), commonSynonymsGroups({}) {}

void ClauseDivider::addClauseToDivider(std::shared_ptr<Clause> clause) {
    if (clause -> getNumberOfSynonyms() == 0) {
        noSynonymsPresent.addClauseToGroup(clause);
    } else {
        for (auto &clause_group : commonSynonymsGroups) {
            if (clause_group.hasCommonSynonymWithClause(clause)) {
                clause_group.addClauseToGroup(clause);
                return;
            }
        }

        // Create new group if it has no common synonym with existing groups
        GroupedClause newGroup;
        newGroup.addClauseToGroup(clause);
        commonSynonymsGroups.emplace_back(newGroup);
    }
}

GroupedClause ClauseDivider::getNoSynonymsPresent() {
    return noSynonymsPresent;
}

std::vector<GroupedClause> ClauseDivider::getCommonSynonymsPresent() {
    return commonSynonymsGroups;
}

std::pair<std::vector<GroupedClause>, std::vector<GroupedClause>> ClauseDivider::divideCommonSynonymGroupsBySelect(std::shared_ptr<Clause> selectClause) {
    std::vector<GroupedClause> selectSynonymPresentGroups;
    std::vector<GroupedClause> selectSynonymNotPresentGroups;

    for (auto gc : commonSynonymsGroups) {
        if (gc.hasCommonSynonymWithClause(selectClause)) {
            selectSynonymPresentGroups.emplace_back(gc);
        } else {
            selectSynonymNotPresentGroups.emplace_back(gc);
        }
    }

    return {selectSynonymPresentGroups, selectSynonymNotPresentGroups};
}
