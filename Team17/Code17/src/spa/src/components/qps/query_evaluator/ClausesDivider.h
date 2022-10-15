#ifndef SPA_CLAUSESDIVIDER_H
#define SPA_CLAUSESDIVIDER_H
#include "vector"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/factory/ClauseCreator.h"
#include "components/pkb/clients/QPSClient.h"
#include "GroupedClause.h"
#include <memory>

class ClauseDivider {
private:
    GroupedClause noSynonymsPresent;
    std::vector<GroupedClause> connectedSynonymsGroups;
    std::vector<GroupedClause> selectSynonymPresentGroups;
    std::vector<GroupedClause> selectSynonymNotPresentGroups;
    void updateConnectedSynonymGroups();
    void checkPreviousGroupsHandler(int previousIndex);
    void addHasSynonymsClauseToDivider(std::shared_ptr<Clause> &clause);

public:
    ClauseDivider();
    void addClauseToDivider(std::shared_ptr<Clause> &clause);
    GroupedClause getNoSynonymsPresent();
    std::vector<GroupedClause> getSelectSynonymPresentGroups();
    std::vector<GroupedClause> getSelectSynonymNotPresentGroups();
    void divideConnectedSynonymGroupsBySelect(std::shared_ptr<Clause> &selectClause);
};


#endif //SPA_CLAUSESDIVIDER_H
