#ifndef SPA_CLAUSECREATOR_H
#define SPA_CLAUSECREATOR_H

#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/SuchThat.h"

// Factory Class for creating Clauses for evaluation

class ClauseCreator {
    Clause createClause(SuchThat rel);
};

#endif //SPA_CLAUSECREATOR_H
