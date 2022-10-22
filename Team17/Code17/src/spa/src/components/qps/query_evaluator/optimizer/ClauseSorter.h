#ifndef SPA_CLAUSESORTER_H
#define SPA_CLAUSESORTER_H

#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include <memory>
#include <algorithm>


class ClauseSorter {
public:
    bool operator()(const std::shared_ptr<Clause> clause1, const std::shared_ptr<Clause> clause2) {
        if (clause1->getNumberOfSynonyms() < clause2->getNumberOfSynonyms()) {
            return true;
        }

        if (clause1->getNumberOfSynonyms() > clause2->getNumberOfSynonyms()) {
            return false;
        }

        // If number of synonyms are the same, prioritise clause with lesser results
        return clause1->getPriority() < clause2->getPriority();
    }
};

#endif //SPA_CLAUSESORTER_H
