#include "QueryObject.h"

//QueryObject::QueryObject(std::vector<SuchThat> relationships, std::vector<Pattern> patterns,
//                         Select select, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap) {
//    this->relationships = relationships;
//    this->patterns = patterns;
//    this->select = select;
//    this->synonymToDesignEntityMap = synonymToDesignEntityMap;
//}

QueryObject::QueryObject() {
    relationships = std::vector<SuchThat>();
    patterns = std::vector<Pattern>();
    select = Select();
    synonymToDesignEntityMap = {};
}

std::vector<SuchThat> QueryObject::getRelationships() {
    return relationships;
}

std::vector<Pattern> QueryObject::getPattern() {
    return patterns;
};
Select QueryObject::getSelect() {
    return select;
};

std::unordered_map<std::string, TokenType> QueryObject::getSynonymToDesignEntityMap() {
    return synonymToDesignEntityMap;
}