#include <vector>
#include <unordered_map>
#include "SuchThat.h"
#include "Declaration.h"
#include "Pattern.h"
#include "Select.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "models/Entity/DesignEntity.h"

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

// At most one such that clause and at most one pattern clause in sequence for now
class QueryObject {
private:
    std::vector<SuchThat> relationships;
    std::vector<qps::Pattern> patterns;
    Select select;
    bool hasNoSyntaxError = false;
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;


public:
    QueryObject();
    QueryObject(Select select, std::vector<SuchThat> relationship, std::vector<qps::Pattern> pattern, std::unordered_map<std::string, DesignEntity> synonymToDesignEntity);
    bool isSyntacticallyCorrect();
    std::vector<SuchThat> getRelationships();
    std::vector<qps::Pattern> getPattern();
    Select getSelect();
    std::unordered_map<std::string, DesignEntity> getSynonymToDesignEntityMap();
    bool operator==(const QueryObject& other) const {
        return relationships == other.relationships
            && patterns == other.patterns
            && select == other.select
            && hasNoSyntaxError == other.hasNoSyntaxError
            && synonymToDesignEntityMap == other.synonymToDesignEntityMap;
    }

};

#endif //SPA_QUERY_H