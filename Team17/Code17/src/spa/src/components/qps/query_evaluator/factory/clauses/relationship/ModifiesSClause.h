#ifndef SPA_MODIFIESSCLAUSE_H
#define SPA_MODIFIESSCLAUSE_H
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

// Parameters: stmtRef, entRef
class ModifiesSClause {
private:
    // Gives Type eg. WILDCARD or NAME_WITH_QUOTES, and value
    TokenObject left;
    TokenObject right;
};

#endif //SPA_MODIFIESSCLAUSE_H
