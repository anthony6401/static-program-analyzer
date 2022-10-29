#include "FollowsTClause.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

FollowsTClause::FollowsTClause(TokenObject left, TokenObject right,
                             std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                             QPSClient qpsClient) : Follows(std::move(left), std::move(right),RelationshipType::FOLLOWS_T, priority, std::move(synonymToDesignEntityMap),
                                                            qpsClient) {}
