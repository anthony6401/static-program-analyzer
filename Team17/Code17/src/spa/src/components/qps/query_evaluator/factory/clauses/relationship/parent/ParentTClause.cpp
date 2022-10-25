#include "ParentTClause.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

ParentTClause::ParentTClause(TokenObject left, TokenObject right,
                               std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                               QPSClient qpsClient) : Parent(std::move(left), std::move(right), RelationshipType::PARENT_T, priority, std::move(synonymToDesignEntityMap),
                                                             qpsClient) {}

