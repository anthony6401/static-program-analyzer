#include "QueryObject.h"


std::vector<SuchThat> QueryObject::getRelationships() {
    return relationships;
}

std::unordered_map<std::string, TokenType> QueryObject::getDeclarations() {
    return declarations;
};
std::vector<Pattern> QueryObject::getPattern() {
    return patterns;
};
Select QueryObject::getSelect() {
    return select;
};