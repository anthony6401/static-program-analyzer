#pragma once
#include "../../qps/query_preprocessor/query_tokenizer/TokenType.h"

#include "../pkb.h"

#include <string>
#include  <vector>

class QPSClient {

public:

	QPSClient(PKB *knowledge);

	//For getting entity
	std::vector<std::string> getAllEntity(qps::TokenType returnType);

	//For Uses Relationship
	/*bool getUses(int lineNumber, std::string var);
	std::vector<std::string> getUsesByVar(TokenType returnType, std::string var);
	std::vector<std::string> getUsesbyStmt(int lineNumber);
	std::vector<std::string> getAllModify(TokenType returnType);*/

private:
	PKB* pkb;
};