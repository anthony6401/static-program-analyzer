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
#include "../../../models/Relationship/ModifyRelationship.h"
#include "../../../models/Relationship/UsesRelationship.h"
#include "../../../models/Relationship/FollowsRelationship.h"
#include "../../../models/Relationship/ParentRelationship.h"

#include "../../pkb/clients/SPClient.h"

#include <vector>

class Extractor {
public:
	SPClient* client;
	Extractor(SPClient* client);

	void extractRead(SimpleToken simpleToken);
	void extractPrint(SimpleToken simpleToken);
	void extractAssign(SimpleToken simpleToken);
	void extractWhile(SimpleToken simpleToken);
	void extractIf(SimpleToken simpleToken);

	void extractCondExpr(Entity* entity, SimpleToken simpleToken);
	void extractStmtLst(Entity* entity, SimpleToken simpleToken);
	void extractReadInStmtLst(Entity* entity, SimpleToken simpleToken);
	void extractPrintInStmtLst(Entity* entity, SimpleToken simpleToken);
	void extractAssignInStmtLst(Entity* entity, SimpleToken simpleToken);

	void extractProcedure();
	void extractCall();
};
