#pragma once

#include "../SimpleToken.h"

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
#include "../../../models/Relationship/ModifyRelationship.h"
#include "../../../models/Relationship/UsesRelationship.h"

#include "../../pkb/clients/SPClient.h"

#include <vector>

using namespace std;

class Extractor {
public:
	void extractRead(SimpleToken simpleToken, vector<string> tokens);
	void extractPrint(SimpleToken simpleToken, vector<string> tokens);
	void extractProcedure();
	void extractCall();
	void extractWhile();
	void extractIf();
	void extractAssign();
	void extractCondExpr();
	void extractVariable();
	void extractConstant();
	void extractClose();
	void extractOpr();
	void extractError();

	static SPClient* client;
};
