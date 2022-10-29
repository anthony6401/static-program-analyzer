#include "CallsClause.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

CallsClause::CallsClause(TokenObject left, TokenObject right,
                                 std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                                 QPSClient qpsClient) : Calls(std::move(left), std::move(right), RelationshipType::CALLS, priority, std::move(synonymToDesignEntityMap),
                                                               qpsClient) {};