#include "Validator.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/abstract_query_object/Declaration.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/Pattern.h"
#include <unordered_map>
#include <stdexcept>
#include <memory>

using namespace qps;

Validator::Validator(QueryObject parsedQuery) {
	this->parsedQuery = parsedQuery;
};

bool Validator::isSemanticallyValid() {
	// If query has SyntaxError, do not proceed with checking for SemanticError
	if (!this->parsedQuery.isSyntacticallyCorrect()) {
		return true;
	}

	std::unordered_map<std::string, DesignEntity> declaredSynonyms = this->parsedQuery.getSynonymToDesignEntityMap();
	Select selectClause = this->parsedQuery.getSelect();
	std::vector<SuchThat> suchThatClause = this->parsedQuery.getRelationships();
	std::vector<Pattern> patternClause = this->parsedQuery.getPattern();

	return true;
};
