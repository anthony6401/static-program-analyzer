#include <string>
#include <list>
#include <vector>
#include <components/qps/query_preprocessor/query_tokenizer/Tokenizer.h>
#include <components/qps/query_preprocessor/query_tokenizer/TokenObject.h>
#include <components/qps/query_preprocessor/query_parser/Parser.h>
#include <components/qps/query_evaluator/Evaluator.h>
#include "QPS.h"
#include "components/qps/abstract_query_object/QueryObject.h"


QueryObject QPS::tokenizeAndParseQuery(std::string query) {
    Tokenizer tokenizer = *new Tokenizer();
    std::vector<TokenObject> tokenList = tokenizer.tokenize(query);
    // Parse query and check semantics
    Parser parser = Parser(tokenList);
    QueryObject parsedQuery = parser.parse();
    return parsedQuery;
}

void QPS::processQueryResult(std::string query, std::list<std::string> &results) {
    QueryObject parsedQuery = tokenizeAndParseQuery(query);
    Evaluator::evaluateQuery(parsedQuery, results);
}

