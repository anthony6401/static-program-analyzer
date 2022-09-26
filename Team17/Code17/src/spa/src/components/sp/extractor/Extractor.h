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

#include "FollowsExtractor.h"
#include "ParentExtractor.h"
#include "UsesExtractor.h"
#include "ModifyExtractor.h"
#include "PatternExtractor.h"

#include "../../../models/Pattern/AssignPattern.h"

#include "../../pkb/clients/SPClient.h"

class Extractor {
public:
	SPClient* client;
	Extractor(SPClient* client);

	void extractAll(SimpleToken procedureToken);
	void extractFollows(SimpleToken procOrWhileIfToken);
	void extractParent(SimpleToken procOrWhileIfToken);
	void extractUses(SimpleToken procOrWhileIfToken);
	void extractModify(SimpleToken procOrWhileIfToken);
	void extractPattern(SimpleToken procOrWhileIfToken);

	void storeFollowsRelationships(std::vector<FollowsRelationship*>);
	void storeFollowsTRelationships(std::vector<FollowsTRelationship*>);
	void storeParentRelationships(std::vector<ParentRelationship*>);
	void storeParentTRelationships(std::vector<ParentTRelationship*>);
	void storeUsesRelationships(std::vector<UsesRelationship*>);
	void storeModifyRelationships(std::vector<ModifyRelationship*>);
	void storeAssignPatterns(std::vector<AssignPattern*>);

	void extractConstants(SimpleToken procedureToken);
	std::vector<ConstantEntity*> extractConstantsVector(SimpleToken procedureToken);
};
