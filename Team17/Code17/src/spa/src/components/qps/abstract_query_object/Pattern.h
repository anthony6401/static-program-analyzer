#ifndef SPA_PATTERN_H
#define SPA_PATTERN_H

#include "string"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

// Only assign pattern
class Pattern {
private:
    std::string name;
    TokenObject left;
    TokenObject right;

public:
    Pattern();
    static std::string getName();
    static TokenObject getLeft();
    static TokenObject getRight();
};

#endif //SPA_PATTERN_H
