#include "QueryObject.h"


std::vector<SuchThat> QueryObject::getRelationships() {
    return relationships;
}

Declaration QueryObject::getDeclarations() {
    return declarations;
};
std::vector<Pattern> QueryObject::getPattern() {
    return patterns;
};
Select QueryObject::getSelect() {
    return select;
};

std::unordered_map<std::string, TokenType> QueryObject::getSynonymToDesignEntityMap() {
    return synonymToDesignEntityMap;
}