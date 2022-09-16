#include <string>
#include <list>
#include <vector>
#include "iostream"
#include <components/qps/query_preprocessor/query_tokenizer/Tokenizer.h>
#include <components/qps/query_preprocessor/query_tokenizer/TokenObject.h>
#include <components/qps/query_preprocessor/query_parser/Parser.h>
#include <components/qps/query_evaluator/Evaluator.h>
#include "QPS.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_preprocessor/query_validator/Validator.h"


QueryObject QPS::tokenizeAndParseQuery(std::string query) {
    Tokenizer tokenizer = *new Tokenizer();
    std::vector<TokenObject> tokenList = tokenizer.tokenize(query);
    // Parse query and check semantics
    Parser parser = Parser(tokenList);
    QueryObject parsedQuery = parser.parse();
    return parsedQuery;
}

void QPS::processQueryResult(std::string query, std::list<std::string> &results, QPSClient qpsClient) {
    try {
        QueryObject parsedQuery = tokenizeAndParseQuery(query);
        Validator validator = Validator(parsedQuery);
        validator.validate();
        Evaluator::evaluateQuery(parsedQuery, results, qpsClient);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        results.emplace_back("SyntaxError");
    }
}

