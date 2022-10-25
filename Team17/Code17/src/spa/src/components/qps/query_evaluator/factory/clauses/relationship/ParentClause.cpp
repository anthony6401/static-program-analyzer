#include "ParentClause.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

ParentClause::ParentClause(TokenObject left, TokenObject right,
                           std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                           QPSClient qpsClient) : Parent(std::move(left), std::move(right), RelationshipType::PARENT, priority, std::move(synonymToDesignEntityMap),
                                                         qpsClient) {}