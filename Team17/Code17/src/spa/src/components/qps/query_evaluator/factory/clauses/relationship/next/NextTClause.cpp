#include "NextTClause.h"
#include <utility>

NextTClause::NextTClause(TokenObject left, TokenObject right,
                       std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                       QPSClient qpsClient) : Next(std::move(left), std::move(right), RelationshipType::NEXT_T, priority, std::move(synonymToDesignEntityMap),
                                                   qpsClient) {}

