#ifndef SPA_CLAUSESDIVIDER_H
#define SPA_CLAUSESDIVIDER_H
#include "vector"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/factory/ClauseCreator.h"
#include "components/pkb/clients/QPSClient.h"
#include <memory>


// Separates clauses into groups:
// 1) Without synonyms to return boolean
// 2) Common synonyms
// 3) Checks for select synonym present

class ClauseDivider {
private:
    std::vector<std::shared_ptr<Clause>> noSynonymsPresent;
    std::vector<std::vector<std::shared_ptr<Clause>>> commonSynonymsGroups;
    std::vector<std::vector<std::shared_ptr<Clause>>> selectSynonymPresentGroups;
    std::vector<std::vector<std::shared_ptr<Clause>>> selectSynonymNotPresentGroups;

public:
    ClauseDivider(std::vector<std::shared_ptr<Clause>> clausesToEvaluate);
    void splitNoAndCommonSynonyms(std::vector<std::shared_ptr<Clause>> clausesToEvaluate);
};

#endif //SPA_CLAUSESDIVIDER_H
