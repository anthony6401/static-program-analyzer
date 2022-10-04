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
#include "FollowsExtractor.h"
#include "ParentExtractor.h"
#include "UsesExtractor.h"
#include "ModifyExtractor.h"
#include "PatternExtractor.h"

#include "StmtStack.h"
#include "WhileStack.h"
#include "IfStack.h"
#include "ProcedureStack.h"

#include "../../../models/Pattern/AssignPattern.h"

#include "../../pkb/clients/SPClient.h"

class Entity;

class Extractor {
public:
	SPClient* client;
	std::stack<StmtStack*> parentStack;
	std::map<std::string, ProcedureStack*> procedures;
	StmtStack* currentStack;
	std::multimap<std::string, std::string> callProcedures;

	std::string currentProcedure;

	Extractor(SPClient* client);

	void close(int statementNumber);

	void extractRead(SimpleToken readToken);
	void extractPrint(SimpleToken printToken);
	void extractAssign(SimpleToken assignToken);
	void extractWhile(SimpleToken whileToken);
	void extractIf(SimpleToken ifToken);
	void extractExpr(SimpleToken stmtToken, SimpleToken exprToken);
	void extractCall(SimpleToken callToken);
	void extractProcedure(SimpleToken procedureToken);
	void endOfParser();
	void addNestedRelationships(StmtStack* parent, StmtStack* called, std::string name);
	std::string getExpressionAsString(SimpleToken exprToken);
	Entity* generateEntity(SimpleToken token);

	void extractConstants(SimpleToken procedureToken);
	std::vector<ConstantEntity*> extractConstantsVector(SimpleToken procedureToken);
};
