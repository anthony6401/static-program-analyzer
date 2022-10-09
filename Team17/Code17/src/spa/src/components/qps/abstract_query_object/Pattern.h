#ifndef SPA_PATTERN_H
#define SPA_PATTERN_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

namespace qps {

    class Pattern {
    private:
        TokenType patternType;
        std::string synonym;
        TokenObject left;
        TokenObject right;

    public:
        Pattern();
        Pattern(std::string synonym, TokenObject left, TokenObject right);
        Pattern(TokenType patternType, std::string synonym, TokenObject left, TokenObject right);
        TokenType getPatternType();
        std::string getSynonym();
        TokenObject getLeft();
        TokenObject getRight();
        bool operator==(const Pattern& other) const {
            return synonym == other.synonym
                && left == other.left
                && right == other.right;
        }
    };
}

#endif //SPA_PATTERN_H