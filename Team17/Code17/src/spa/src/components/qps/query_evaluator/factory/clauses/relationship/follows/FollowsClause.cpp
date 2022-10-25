#include "FollowsClause.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

FollowsClause::FollowsClause(TokenObject left, TokenObject right,
                             std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                             QPSClient qpsClient) : Follows(std::move(left), std::move(right),RelationshipType::FOLLOWS, priority, std::move(synonymToDesignEntityMap),
                                                            qpsClient) {}

