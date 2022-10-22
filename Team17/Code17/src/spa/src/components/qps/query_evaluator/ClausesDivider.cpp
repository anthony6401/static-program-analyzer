#include "ClausesDivider.h"
#include <algorithm>


ClauseDivider::ClauseDivider() : noSynonymsPresent({}), connectedSynonymsGroups({}), selectSynonymPresentGroups({}), selectSynonymNotPresentGroups({}) {}

GroupedClause ClauseDivider::getNoSynonymsPresent() {
    return noSynonymsPresent;
}

std::vector<GroupedClause> ClauseDivider::getSelectSynonymPresentGroups() {
    return selectSynonymPresentGroups;
}

std::vector<GroupedClause> ClauseDivider::getSelectSynonymNotPresentGroups() {
    return selectSynonymNotPresentGroups;
}

void ClauseDivider::divideConnectedSynonymGroupsBySelect(std::shared_ptr<Clause> &selectClause) {
    if (!connectedSynonymsGroups.empty()) {
        updateConnectedSynonymGroups();
    }
    for (auto &gc : connectedSynonymsGroups) {
        if (gc.hasCommonSynonymWithClause(selectClause)) {
            selectSynonymPresentGroups.emplace_back(gc);
        } else {
            selectSynonymNotPresentGroups.emplace_back(gc);
        }
    }
}

void ClauseDivider::checkPreviousGroupsHandler(int lastIndex) {
    bool isConnected;
    auto lastGroup = connectedSynonymsGroups.at(lastIndex);
    for (int previousIndex = lastIndex - 1; previousIndex >= 0; previousIndex--) {
        isConnected = connectedSynonymsGroups.at(previousIndex).isConnected(lastGroup);
        if (isConnected) {
            connectedSynonymsGroups.at(previousIndex).mergeGroupedClause(lastGroup);
            connectedSynonymsGroups.erase(connectedSynonymsGroups.begin() + lastIndex);
            break;
        }
    }
}

void ClauseDivider::updateConnectedSynonymGroups() {
    for (int lastIndex = connectedSynonymsGroups.size() - 1; lastIndex > 0; lastIndex--) {
        checkPreviousGroupsHandler(lastIndex);
    }
}


void ClauseDivider::addHasSynonymsClauseToDivider(std::shared_ptr<Clause> &clause) {
    for (auto &gc : connectedSynonymsGroups) {
        if (gc.hasCommonSynonymWithClause(clause)) {
            gc.addClauseToGroup(clause);
            return;
        }
    }

    GroupedClause clauseGroup;
    clauseGroup.addClauseToGroup(clause);
    connectedSynonymsGroups.emplace_back(clauseGroup);
}

void ClauseDivider::addClauseToDivider(std::shared_ptr<Clause> &clause) {
    if (clause -> getNumberOfSynonyms() == 0) {
        noSynonymsPresent.addClauseToGroup(clause);
    } else {
        addHasSynonymsClauseToDivider(clause);
    }
}
