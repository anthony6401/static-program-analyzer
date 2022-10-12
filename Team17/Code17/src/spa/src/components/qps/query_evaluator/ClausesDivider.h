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
public:
    ClauseDivider();
    void addClauseToDivider(std::shared_ptr<Clause> &clause);
    GroupedClause getNoSynonymsPresent();
    std::vector<GroupedClause> getSelectSynonymPresentGroups();
    std::vector<GroupedClause> getSelectSynonymNotPresentGroups();
    void updateConnectedSynonymGroups();
    void divideCommonSynonymGroupsBySelect(std::shared_ptr<Clause> &selectClause);
    void addHasSynonymsClauseToDivider(std::shared_ptr<Clause> &clause);
    void checkPreviousGroupsHandler(int previousIndex);

};


#endif //SPA_CLAUSESDIVIDER_H
