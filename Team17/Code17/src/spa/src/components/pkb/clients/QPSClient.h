#pragma once
#include "models/Entity/DesignEntity.h"


#include "../pkb.h"

#include <string>
#include <unordered_set>

class QPSClient {

public:

	QPSClient(PKB *knowledge);

	//For getting entity
	std::unordered_set<std::string> getAllEntity(DesignEntity returnType);

	//For Uses Relationship
	/*bool getUses(int lineNumber, std::string var);
	std::vector<std::string> getUsesByVar(TokenType returnType, std::string var);
	std::vector<std::string> getUsesbyStmt(int lineNumber);
	std::vector<std::string> getAllModify(TokenType returnType);*/

private:
	PKB* pkb;
};