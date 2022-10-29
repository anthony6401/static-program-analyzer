#include "CallsTClause.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

CallsTClause::CallsTClause(TokenObject left, TokenObject right,
                         std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                         QPSClient qpsClient) : Calls(std::move(left), std::move(right), RelationshipType::CALLS_T, priority, std::move(synonymToDesignEntityMap),
                                                      qpsClient) {};