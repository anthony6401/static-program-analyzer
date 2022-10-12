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
    if (!commonSynonymsGroups.empty()) {
        updateConnectedSynonymGroups();
    }
    for (auto &gc : commonSynonymsGroups) {
        if (gc.hasCommonSynonymWithClause(selectClause)) {
            selectSynonymPresentGroups.emplace_back(gc);
        } else {
            selectSynonymNotPresentGroups.emplace_back(gc);
        }
    }
}

void ClauseDivider::updateConnectedSynonymGroups() {
    for (int i = commonSynonymsGroups.size() - 1; i > 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            if (commonSynonymsGroups.at(j).isConnected(commonSynonymsGroups.at(i))) {
                commonSynonymsGroups.at(j).mergeGroupedClause(commonSynonymsGroups.at(i));
                commonSynonymsGroups.erase(commonSynonymsGroups.begin() + i);
                break;
            }
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
