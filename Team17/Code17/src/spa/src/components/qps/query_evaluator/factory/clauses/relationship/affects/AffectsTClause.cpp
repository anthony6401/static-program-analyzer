#include "AffectsTClause.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

AffectsTClause::AffectsTClause(TokenObject left, TokenObject right,
                             std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                             QPSClient qpsClient) : Affects(std::move(left), std::move(right), RelationshipType::AFFECTS_T, priority, std::move(synonymToDesignEntityMap),
                                                            qpsClient) {}