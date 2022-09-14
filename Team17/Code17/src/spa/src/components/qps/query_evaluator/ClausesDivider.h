#ifndef SPA_CLAUSESDIVIDER_H
#define SPA_CLAUSESDIVIDER_H
#include "vector"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/factory/ClauseCreator.h"
#include "components/pkb/clients/QPSClient.h"
#include "GroupedClause.h"
#include <memory>

// Separates clauses into groups:
// 1) Without synonyms to return boolean
// 2) Common synonyms
// 3) Checks for select synonym present inside common synonyms list

class ClauseDivider {
public:
    ClauseDivider();
    static std::pair<GroupedClause, std::vector<GroupedClause>> divideClausesBySynonyms(std::vector<std::shared_ptr<Clause>> clausesToEvaluate);
    static std::pair<std::vector<GroupedClause>, std::vector<GroupedClause>> divideCommonSynonymGroupsBySelect(std::shared_ptr<Clause> selectClause, std::vector<GroupedClause> commonSynonymsGroups);

};

#endif //SPA_CLAUSESDIVIDER_H
