#include "ClausesDivider.h"
#include "iostream"

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

void ClauseDivider::divideCommonSynonymGroupsBySelect(std::shared_ptr<Clause> &selectClause) {
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

void ClauseDivider::checkPreviousGroupsHandler(int previousIndex) {
    bool isConnected;
    for (int j = previousIndex - 1; j >= 0; --j) {
        isConnected = connectedSynonymsGroups.at(j).isConnected(connectedSynonymsGroups.at(previousIndex));
        if (isConnected) {
            connectedSynonymsGroups.at(j).mergeGroupedClause(connectedSynonymsGroups.at(previousIndex));
            connectedSynonymsGroups.erase(connectedSynonymsGroups.begin() + previousIndex);
            break;
        }
    }
}


void ClauseDivider::updateConnectedSynonymGroups() {
    for (int i = connectedSynonymsGroups.size() - 1; i > 0; --i) {
        checkPreviousGroupsHandler(i);
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
