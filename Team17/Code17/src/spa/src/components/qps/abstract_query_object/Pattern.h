#ifndef SPA_PATTERN_H
#define SPA_PATTERN_H

#include "string"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

using namespace qps;

// Only assign pattern
class Pattern {
private:
    std::string name;
    TokenObject left;
    TokenObject right;

public:
    Pattern();
    Pattern(std::string name, TokenObject left, TokenObject right);
    static std::string getName();
    static TokenObject getLeft();
    static TokenObject getRight();
    bool operator==(const Pattern& other) const {
        return name == other.name
            && left == other.left
            && right == other.right;
    }
};

#endif //SPA_PATTERN_H
