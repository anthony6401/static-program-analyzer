#ifndef SPA_CLAUSEUTILS_H
#define SPA_CLAUSEUTILS_H

#include <unordered_map>
#include <list>
#include <unordered_set>
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"

namespace ClauseUtils {
    std::vector<std::pair<std::string, std::string>> processMapToVectorPair(std::unordered_map<std::string, std::unordered_set<std::string>> results);
    std::unordered_set<std::string> processMapToSetFromFirst(std::unordered_map<std::string, std::unordered_set<std::string>> results);
};

#endif //SPA_CLAUSEUTILS_H
