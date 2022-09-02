#ifndef SPA_MODIFIESSCLAUSE_H
#define SPA_MODIFIESSCLAUSE_H
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"

// Parameters: stmtRef, entRef

class ModifiesSClause : public Clause {
private:
    // Gives Type eg. WILDCARD or NAME_WITH_QUOTES, and value
    TokenObject left;
    TokenObject right;

public:
    std::vector<std::string> evaluateClause() override;
};

#endif //SPA_MODIFIESSCLAUSE_H
