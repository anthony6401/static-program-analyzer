#include "SelectClause.h"

SelectClause::SelectClause(qps::TokenType entityReturnType) {
    this -> entityReturnType = entityReturnType;
}

//std::vector<std::string> SelectClause::evaluateClause() {
//    std::vector<std::string> evaluatedResults;
//    // Retrieve results from PKB
//    // pkb -> get......
//    return evaluatedResults;
//}