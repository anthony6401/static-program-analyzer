#include "string"
#include "unordered_map"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/abstract_query_object/Declaration.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/Pattern.h"
#include "models/Entity/DesignEntity.h"
#include <vector>

#ifndef INC_22S1_CP_SPA_TEAM_17_VALIDATOR_H
#define INC_22S1_CP_SPA_TEAM_17_VALIDATOR_H

using namespace qps;

class Validator {
private:
	QueryObject parsedQuery;
	bool selectClauseIsSemanticallyCorrect();
	bool suchThatClauseIsSemanticallyCorrect();
	bool patternClauseIsSemanticallyCorrect();
	bool isDeclaredSynonym(std::string synonym);
	bool isValidUsesAndModifies(SuchThat relationship);
	bool isValidFollowsAndParent(SuchThat relationship);
	bool isStatement(std::string synonym);
	bool isVariable(std::string synonym);
	bool isAssign(std::string synonym);
	bool isValidUsesAndModifiesLeftParameter(std::string synonym);

public:
	Validator(QueryObject parsedQuery);
	bool isSemanticallyValid();

};

#endif //INC_22S1_CP_SPA_TEAM_17_VALIDATOR_H
