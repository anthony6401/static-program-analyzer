#include <string>
#include <list>
#include <vector>
#include <components/qps/query_preprocessor/query_tokenizer/Tokenizer.h>
#include <components/qps/query_preprocessor/query_tokenizer/TokenObject.h>
#include <components/qps/query_evaluator/Evaluator.h>
#include "QPS.h"


void QPS::tokenizeAndParseQuery(std::string query) {
    Tokenizer tokenizer = *new Tokenizer();
    std::vector<TokenObject> tokenList = tokenizer.tokenize(query);
    // Parse query and check semantics
    // returns Query object
}

void QPS::obtainQueryResult(std::string query, std::list<std::string> &results) {
    tokenizeAndParseQuery(query);
}

