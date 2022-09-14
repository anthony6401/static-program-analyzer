#include "QueryObject.h"
#include <unordered_map>

/*
* Initializes empty query
*/
QueryObject::QueryObject() : relationships(std::vector<SuchThat>()),
patterns(std::vector<Pattern>()), select(Select()), synonymToDesignEntityMap(std::unordered_map<std::string, DesignEntity>()) {
	this->hasNoSyntaxError = false;
	this->hasNoSemanticError = true;
}

/*
* Initializes query object with the values for clauses
*/
QueryObject::QueryObject(Select select, std::vector<SuchThat> relationship, 
	std::vector<Pattern> pattern, std::unordered_map<std::string, DesignEntity> synonymToDesignEntity, int numOfDeclaredSynonyms) {

	this->relationships = relationship;
	this->select = select;
	this->patterns = pattern;
	this->hasNoSyntaxError = true;
	this->hasNoSemanticError = true;
	this->synonymToDesignEntityMap = synonymToDesignEntity;
	this->numOfDeclaredSynonyms = numOfDeclaredSynonyms;
}


bool QueryObject::isSyntacticallyCorrect() {
	return this->hasNoSyntaxError;
}

bool QueryObject::isSemanticallyValid() {
	return this->hasNoSemanticError;
}

std::vector<SuchThat> QueryObject::getRelationships() {
	return this->relationships;
}

std::vector<Pattern> QueryObject::getPattern() {
	return this->patterns;
};
Select QueryObject::getSelect() {
	return this->select;
};

std::unordered_map<std::string, DesignEntity> QueryObject::getSynonymToDesignEntityMap() {
	return this->synonymToDesignEntityMap;
}

void QueryObject::setSemanticallyInvalid() {
	this->hasNoSemanticError = false;
}
