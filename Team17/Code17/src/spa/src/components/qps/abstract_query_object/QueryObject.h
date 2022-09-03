#include <vector>
#include <unordered_map>
#include "SuchThat.h"
#include "Declaration.h"
#include "Pattern.h"
#include "Select.h"

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

// At most one such that clause and at most one pattern clause in sequence for now
class QueryObject {
private:
    std::vector<SuchThat> relationships;
    Declaration declarations;
    std::vector<Pattern> patterns;
    Select select;
    std::unordered_map<std::string, TokenType> synonymToDesignEntityMap;


public:
    QueryObject();
    QueryObject(std::vector<SuchThat> relationships,
                Declaration declarations, std::vector<Pattern> patterns, Select select,
                std::unordered_map<std::string, TokenType> synonymToDesignEntityMap);
    std::vector<SuchThat> getRelationships();
    Declaration getDeclarations();
    std::vector<Pattern> getPattern();
    Select getSelect();
    std::unordered_map<std::string, TokenType> getSynonymToDesignEntityMap();
};

#endif //SPA_QUERY_H
