#ifndef SPA_QPS_H
#define SPA_QPS_H

#include <string>
#include <list>
#include <vector>
#include <components/qps/query_preprocessor/query_tokenizer/Tokenizer.h>
#include <components/qps/query_preprocessor/query_tokenizer/TokenObject.h>
#include <components/qps/query_evaluator/Evaluator.h>
#include "components/qps/abstract_query_object/QueryObject.h"

class QPS {
public:
    static QueryObject tokenizeAndParseQuery(std::string query);
    static void processQueryResult(std::string query, std::list<std::string> &results, QPSClient qpsClient);
};

#endif //SPA_QPS_H
