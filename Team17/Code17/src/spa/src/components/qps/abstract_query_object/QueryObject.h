#include <vector>
#include <unordered_map>
#include "SuchThat.h"
#include "Declaration.h"
#include "Pattern.h"
#include "Select.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

// At most one such that clause and at most one pattern clause in sequence for now
class QueryObject {
private:
    std::vector<SuchThat> relationships;
    std::vector<Pattern> patterns;
    Select select;
    bool hasNoSyntaxError = false;
    std::unordered_map<std::string, TokenType> synonymToDesignEntityMap;


public:
    QueryObject();
    QueryObject(Select select, std::vector<SuchThat> relationship, std::vector<Pattern> pattern, std::unordered_map<std::string, TokenType> synonymToDesignEntity);
    bool isSyntacticallyCorrect();
    std::vector<SuchThat> getRelationships();
    std::vector<Pattern> getPattern();
    Select getSelect();
    std::unordered_map<std::string, TokenType> getSynonymToDesignEntityMap();
    bool operator==(const QueryObject& other) const {
        return relationships == other.relationships
            && patterns == other.patterns
            && select == other.select
            && hasNoSyntaxError == other.hasNoSyntaxError
            && synonymToDesignEntityMap == other.synonymToDesignEntityMap;
    }

};

#endif //SPA_QUERY_H