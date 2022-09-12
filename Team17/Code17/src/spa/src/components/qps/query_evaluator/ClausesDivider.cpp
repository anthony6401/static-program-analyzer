#include "ClausesDivider.h"

ClauseDivider::ClauseDivider() {}

std::pair<GroupedClause, std::vector<GroupedClause>> ClauseDivider::divideClausesBySynonyms(std::vector<std::shared_ptr<Clause>> clausesToEvaluate) {
    GroupedClause noSynonymsPresent;
    std::vector<GroupedClause> commonSynonymsGroups;
    // Maximum of 2 clauses for milestone 1 ->
    for (auto clause : clausesToEvaluate) {
        if (clause->getNumberOfSynonyms() == 0) {
            // Without synonyms, to return boolean
            noSynonymsPresent.addClauseToGroup(clause);
        } else {
            // With synonyms, check for common synonyms within existing groups
            if (commonSynonymsGroups.empty()) { // vector<GroupedClause>
                GroupedClause firstGroup;
                firstGroup.addClauseToGroup(clause);
                commonSynonymsGroups.emplace_back(firstGroup);
            }

            for (GroupedClause gc : commonSynonymsGroups) {
                if (gc.hasCommonSynonymWithClause(clause)) {
                    gc.addClauseToGroup(clause);
                } else {
                    // Create a new group
                    GroupedClause newGroup;
                    newGroup.addClauseToGroup(clause);
                    commonSynonymsGroups.emplace_back(newGroup);
                }
            }
        }
    }
    return {noSynonymsPresent, commonSynonymsGroups};
}

std::pair<std::vector<GroupedClause>, std::vector<GroupedClause>> ClauseDivider::divideCommonSynonymGroupsBySelect(
        std::shared_ptr<Clause> selectClause, std::vector<GroupedClause> commonSynonymsGroups) {
    std::vector<GroupedClause> selectSynonymPresentGroups;
    std::vector<GroupedClause> selectSynonymNotPresentGroups;
    for (GroupedClause gc : commonSynonymsGroups) {
        if (gc.hasCommonSynonymWithClause(selectClause)) {
            selectSynonymPresentGroups.emplace_back(gc);
        } else {
            selectSynonymNotPresentGroups.emplace_back(gc);
        }
    }

    return {selectSynonymPresentGroups, selectSynonymNotPresentGroups};
}

