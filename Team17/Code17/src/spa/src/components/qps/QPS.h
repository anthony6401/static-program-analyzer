#ifndef SPA_QPS_H
#define SPA_QPS_H

#include <string>
#include <list>
#include <vector>
#include <components/qps/query_preprocessor/query_tokenizer/Tokenizer.h>
#include <components/qps/query_preprocessor/query_tokenizer/TokenObject.h>
#include <components/qps/query_evaluator/Evaluator.h>

class QPS {
    void tokenizeAndParseQuery(std::string query);
    void obtainQueryResult(std::string query, std::list<std::string> &results);
};

#endif //SPA_QPS_H
