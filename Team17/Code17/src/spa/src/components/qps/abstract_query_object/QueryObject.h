#include <vector>
#include <unordered_map>
#include "SuchThat.h"
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
    bool hasNoSemanticError = true; // Assumed true till QueryObject is passed into the Validator
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    int numOfDeclaredSynonyms = 0;


public:
    QueryObject();
    QueryObject(Select select, std::vector<SuchThat> relationship, std::vector<qps::Pattern> pattern, std::unordered_map<std::string, DesignEntity> synonymToDesignEntity, int numOfDeclaredSynonyms);
    bool isSyntacticallyCorrect();
    bool isSemanticallyValid();
    std::vector<SuchThat> getRelationships();
    std::vector<qps::Pattern> getPattern();
    Select getSelect();
    std::unordered_map<std::string, DesignEntity> getSynonymToDesignEntityMap();
    int getNumOfDeclaredSynonyms();
    void setSemanticallyInvalid();
    bool operator==(const QueryObject& other) const {
        return relationships == other.relationships
            && patterns == other.patterns
            && select == other.select
            && hasNoSyntaxError == other.hasNoSyntaxError
            && hasNoSemanticError == other.hasNoSemanticError
            && synonymToDesignEntityMap == other.synonymToDesignEntityMap
            && numOfDeclaredSynonyms == other.numOfDeclaredSynonyms;
    }

};

#endif //SPA_QUERY_H