#include <vector>
#include <unordered_map>
#include "SuchThat.h"
#include "Declaration.h"
#include "Pattern.h"
#include "Select.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

using namespace qps;

// At most one such that clause and at most one pattern clause in sequence
class QueryObject {
private:
    std::vector<SuchThat> relationship;
    std::vector<Declaration> declarations;
    std::vector<Pattern> pattern;
    Select select;
    bool hasNoSyntaxError;
    std::unordered_map<std::string, TokenType> synonymToDesignEntity;

public:
    QueryObject();
    QueryObject(std::vector<Declaration> declarations, Select select, std::vector<SuchThat> relationship, std::vector<Pattern> pattern, std::unordered_map<std::string, TokenType> synonymToDesignEntity);
    bool isSyntacticallyCorrect();
    std::unordered_map<std::string, TokenType> getSynonymToDesignEntity();
    bool operator==(const QueryObject& other) const {
        return relationship == other.relationship
            && declarations == other.declarations
            && pattern == other.pattern
            && select == other.select
            && hasNoSyntaxError == other.hasNoSyntaxError
            && synonymToDesignEntity == other.synonymToDesignEntity;
    }
};

#endif //SPA_QUERY_H