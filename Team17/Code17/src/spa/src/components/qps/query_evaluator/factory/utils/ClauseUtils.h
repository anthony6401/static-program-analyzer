#ifndef SPA_CLAUSEUTILS_H
#define SPA_CLAUSEUTILS_H

#include <unordered_map>
#include <unordered_set>
#include "components/qps/query_evaluator/factory/interface/Clause.h"

namespace ClauseUtils {
    std::vector<std::pair<std::string, std::string>> processMapToVectorPair(std::unordered_map<std::string, std::unordered_set<std::string>> results);
    std::unordered_set<std::string> processMapToSetFromFirst(std::unordered_map<std::string, std::unordered_set<std::string>> results);
    std::unordered_set<std::string> processMapToSetFromSecond(std::unordered_map<std::string, std::unordered_set<std::string>> results);
    std::unordered_set<std::string> processMapToSetByMapIntersection(std::unordered_map<std::string, std::unordered_set<std::string>> results);
};

#endif //SPA_CLAUSEUTILS_H
