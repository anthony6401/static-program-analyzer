#include "GroupedClause.h"

GroupedClause::GroupedClause() : synonyms({}), clauses({}) {}

void GroupedClause::addClauseToGroup(std::shared_ptr<Clause>) {

}

bool GroupedClause::hasCommonSynonymWithClause(std::shared_ptr<Clause> clause) {
    return true;
}