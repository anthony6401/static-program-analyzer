#include "string"
#include "unordered_map"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/Pattern.h"
#include "components/qps/abstract_query_object/With.h"
#include "models/Entity/DesignEntity.h"
#include <vector>

#ifndef INC_22S1_CP_SPA_TEAM_17_VALIDATOR_H
#define INC_22S1_CP_SPA_TEAM_17_VALIDATOR_H

using namespace qps;

class Validator {
private:
	QueryObject parsedQuery;
	std::vector<DesignEntity> validDesignEntitiesForUsesAndModifies = {
		DesignEntity::STMT, DesignEntity::READ, DesignEntity::PRINT, DesignEntity::CALL,
		DesignEntity::WHILE, DesignEntity::IF, DesignEntity::ASSIGN, DesignEntity::PROCEDURE
	};

	std::vector<DesignEntity> statementDesignEntities = {
		DesignEntity::STMT, DesignEntity::READ, DesignEntity::PRINT, DesignEntity::CALL,
		DesignEntity::WHILE, DesignEntity::IF, DesignEntity::ASSIGN
	};

	std::unordered_map<std::string, std::vector<DesignEntity>>  attrNameToValidDesignEntity = {
		{std::string("procName"), std::vector<DesignEntity>{DesignEntity::CALL, DesignEntity::PROCEDURE }},
		{std::string("varName"), std::vector<DesignEntity>{DesignEntity::READ, DesignEntity::PRINT, DesignEntity::VARIABLE}},
		{std::string("value"), std::vector<DesignEntity>{DesignEntity::CONSTANT}},
		{std::string("stmt#"), statementDesignEntities}
	};

	bool isSemanticallyValid();
	bool selectClauseIsSemanticallyCorrect();
	bool suchThatClauseIsSemanticallyCorrect();
	bool patternClauseIsSemanticallyCorrect();
	bool withClauseIsSemanticallyCorrect();
	bool isDeclaredSynonym(std::string synonym);
	bool isValidUsesAndModifies(SuchThat &relationship);
	bool isValidFollowsParentNext(SuchThat &relationship);
	bool isValidCalls(SuchThat &relationship);
	bool isValidParameter(std::string synonymName, DesignEntity validDesignEntity);
	bool isStatement(std::string synonym);
	bool isValidDesignEntity(std::string synonym, DesignEntity designEntityToMatch);
	bool isValidUsesAndModifiesLeftParameter(std::string synonym);
	bool isValidAttrNameToAttrSynonym(std::string attrName, DesignEntity attrSynonymDesignEntity);
	bool isValidAttrRef(std::vector<TokenObject> &ref);
	bool isValidPatternSynonym(TokenType patternType, std::string patternSynonym);

public:
	Validator(QueryObject parsedQuery);
	QueryObject validate();

};

#endif //INC_22S1_CP_SPA_TEAM_17_VALIDATOR_H
