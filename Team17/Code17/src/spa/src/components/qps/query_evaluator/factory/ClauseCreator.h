#ifndef SPA_CLAUSECREATOR_H
#define SPA_CLAUSECREATOR_H

#include <unordered_map>
#include <memory>
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/query_evaluator/factory/clauses/select/SelectClause.h"
#include "components/qps/abstract_query_object/Pattern.h"
#include "components/qps/abstract_query_object/Select.h"

// Factory Class for creating Clauses for evaluation

class ClauseCreator {
public:
    ClauseCreator();
    static std::shared_ptr<Clause> createClause(SuchThat relationship, Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap, QPSClient qpsClient);
    static std::shared_ptr<Clause> createClause(Pattern pattern, Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap, QPSClient qpsClient);
    static std::shared_ptr<Clause> createClause(Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap, QPSClient qpsClient);
    static bool isStmtRelationship(TokenObject left, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap);
    static bool isProcRelationship(TokenObject left, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap);
};

#endif //SPA_CLAUSECREATOR_H
