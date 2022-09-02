#include "QueryObject.h"
#include<unordered_map>

using namespace qps;

/*
* Initializes empty query
*/
QueryObject::QueryObject() {
	this->isSyntacticallyCorrect = false;
};

/*
* Initializes query object with the values for clauses
*/
QueryObject::QueryObject(std::vector<Declaration> declarations, Select select,
	std::vector<SuchThat> relationship, std::vector<Pattern> pattern, std::unordered_map<std::string, TokenType> synonymToDesignEntity) {
	
	this->declarations = declarations;
	this->relationship = relationship;
	this->select = select;
	this->pattern = pattern;
	this->hasNoSyntaxError = true;
	this->synonymToDesignEntity = synonymToDesignEntity;
};


bool QueryObject::isSyntacticallyCorrect() {
	return this->hasNoSyntaxError;
};

std::unordered_map<std::string, TokenType> QueryObject::getSynonymToDesignEntity() {
	return this->synonymToDesignEntity;
};
