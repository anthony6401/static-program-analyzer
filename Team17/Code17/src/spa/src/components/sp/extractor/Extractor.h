#pragma once

#include "../SimpleToken.h"

#include "../../../models/Entity/Entity.h"
#include "../../../models/Entity/ReadEntity.h"
#include "../../../models/Entity/PrintEntity.h"
#include "../../../models/Entity/VariableEntity.h"
#include "../../../models/Entity/ProcedureEntity.h"
#include "../../../models/Entity/StatementEntity.h"
#include "../../../models/Entity/CallEntity.h"
#include "../../../models/Entity/WhileEntity.h"
#include "../../../models/Entity/IfEntity.h"
#include "../../../models/Entity/AssignEntity.h"
#include "../../../models/Entity/VariableEntity.h"
#include "../../../models/Entity/ConstantEntity.h"

#include "../../../models/Relationship/Relationship.h"
#include "../../../models/Relationship/FollowsRelationship.h"
#include "../../../models/Relationship/FollowsTRelationship.h"
#include "../../../models/Relationship/ParentRelationship.h"
#include "../../../models/Relationship/ParentTRelationship.h"
#include "../../../models/Relationship/UsesRelationship.h"
#include "../../../models/Relationship/ModifyRelationship.h"
#include "../../../models/Relationship/CallsRelationship.h"
#include "../../../models/Relationship/CallsTRelationship.h"
#include "../../../models/Relationship/NextRelationship.h"

#include "StmtStack.h"
#include "WhileStack.h"
#include "IfStack.h"
#include "ProcedureStack.h"

#include "../../../models/Pattern/AssignPattern.h"
#include "../../../models/Pattern/WhilePattern.h"
#include "../../../models/Pattern/IfPattern.h"

#include "../../pkb/clients/SPClient.h"

#include <stack>
#include <map>

class Entity;

class Extractor {
public:
	SPClient* client;
	std::stack<StmtStack*> parentStack;
	std::map<std::string, ProcedureStack*> procedures;
	StmtStack* currentStack;

	std::vector<SimpleToken> previousStmt;
	std::multimap<std::string, SimpleToken> usesForCalls;
	std::multimap<std::string, SimpleToken> modsForCalls;
	std::multimap<std::string, SimpleToken> whileIfCallMap;

	Extractor(SPClient* client);

	void extractRead(SimpleToken readToken);
	void extractPrint(SimpleToken printToken);
	void extractAssign(SimpleToken assignToken);
	void extractAssignPattern(SimpleToken assignToken);
	void extractWhile(SimpleToken whileToken);
	void extractIf(SimpleToken ifToken);
	void extractWhilePattern(SimpleToken whileToken);
	void extractIfPattern(SimpleToken ifToken);
	void extractExpr(SimpleToken stmtToken, SimpleToken exprToken);
	void extractCall(SimpleToken callToken);
	void extractProcedure(SimpleToken procedureToken);
	void close(int statementNumber);
	void endOfParser(std::multimap<std::string, std::string> callProcedures);
	void endOfParserHelper(std::string current, std::string called,
		std::multimap<std::string, std::string> callProcedures, std::vector<std::string> alrCalled);
	void addNestedRelationships(StmtStack* called, std::string parentName);
	
	Entity* generateEntity(SimpleToken token);
};
