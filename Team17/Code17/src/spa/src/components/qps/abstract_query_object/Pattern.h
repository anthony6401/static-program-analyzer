#ifndef SPA_PATTERN_H
#define SPA_PATTERN_H

#include "string"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

using namespace qps;

// Only assign pattern
class Pattern {
private:
    std::string synonym;
    TokenObject left;
    TokenObject right;

public:
    Pattern();
    Pattern(std::string synonym, TokenObject left, TokenObject right);
    std::string getSynonym();
    TokenObject getLeft();
    TokenObject getRight();
    bool operator==(const Pattern& other) const {
        return synonym == other.synonym
            && left == other.left
            && right == other.right;
    }
};

#endif //SPA_PATTERN_H
