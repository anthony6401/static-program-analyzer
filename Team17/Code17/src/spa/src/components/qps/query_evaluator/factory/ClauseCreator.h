#ifndef SPA_CLAUSECREATOR_H
#define SPA_CLAUSECREATOR_H

#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/query_evaluator/factory/clauses/select/SelectClause.h"
#include "components/qps/abstract_query_object/Pattern.h"

// Factory Class for creating Clauses for evaluation

class ClauseCreator {
public:
    Clause createClause(SuchThat relationship); //return type
    Clause createClause(Pattern pattern);
    Clause createClause(TokenType returnType);
};

#endif //SPA_CLAUSECREATOR_H
