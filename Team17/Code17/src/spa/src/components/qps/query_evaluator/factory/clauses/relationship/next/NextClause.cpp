#include "NextClause.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

NextClause::NextClause(TokenObject left, TokenObject right,
                               std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                               QPSClient qpsClient) : Next(std::move(left), std::move(right), RelationshipType::NEXT, priority, std::move(synonymToDesignEntityMap),
                                                              qpsClient) {}
