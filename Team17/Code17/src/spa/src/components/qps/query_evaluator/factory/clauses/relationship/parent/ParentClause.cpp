#include "ParentClause.h"

ParentClause::ParentClause(TokenObject left, TokenObject right,
                           std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                           QPSClient qpsClient) : Parent(std::move(left), std::move(right), RelationshipType::PARENT, priority, std::move(synonymToDesignEntityMap),
                                                         qpsClient) {}