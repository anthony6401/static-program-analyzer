#ifndef SPA_CLAUSEGROUPSORTER_H
#define SPA_CLAUSEGROUPSORTER_H

#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/query_evaluator/GroupedClause.h"
#include <memory>


class ClauseGroupSorter {
public:
    bool operator()(const GroupedClause& clauseGroup1, const GroupedClause& clauseGroup2) {
        if (clauseGroup1.getNumberOfSynonyms() < clauseGroup2.getNumberOfSynonyms()) {
            return true;
        }

        if (clauseGroup1.getNumberOfSynonyms() > clauseGroup2.getNumberOfSynonyms()) {
            return false;
        }

       return clauseGroup1.getPriority() < clauseGroup2.getPriority();
    }
};

#endif //SPA_CLAUSEGROUPSORTER_H
