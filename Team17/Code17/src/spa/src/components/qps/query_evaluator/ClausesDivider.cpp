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


// BUGGY
std::pair<GroupedClause, std::vector<GroupedClause>> ClauseDivider::divideClausesBySynonyms(std::vector<std::shared_ptr<Clause>> clausesToEvaluate) {
    GroupedClause noSynonymsPresent;
    std::vector<GroupedClause> commonSynonymsGroups;

    std::cout << "Clauses to evaluate count: " << clausesToEvaluate.size() << std::endl;

    for (auto clause : clausesToEvaluate) {
        if (clause->getNumberOfSynonyms() == 0) {
            // Without synonyms, to return boolean
            noSynonymsPresent.addClauseToGroup(clause);
        } else {
            // With synonyms, check for common synonyms within existing groups
            if (commonSynonymsGroups.empty()) { // vector<GroupedClause>
                GroupedClause firstGroup;
                firstGroup.addClauseToGroup(clause);
                 for (auto s : firstGroup.getAllSynonyms()) {
                     std::cout << "Group 1:" << s << std::endl;
                 }
                commonSynonymsGroups.emplace_back(firstGroup);
            } else {
                for (GroupedClause gc : commonSynonymsGroups) {
                    if (gc.hasCommonSynonymWithClause(clause)) {
                        std::cout << "Add clause to existing group" << std::endl;
                        gc.addClauseToGroup(clause);
                        break;
                    } else {
                        // Create a new group
                        std::cout << "create new group" << std::endl;
                        GroupedClause newGroup;
                        newGroup.addClauseToGroup(clause);
                        commonSynonymsGroups.emplace_back(newGroup);
                    }
                }
            }
        }
    }
    return {noSynonymsPresent, commonSynonymsGroups};
}
