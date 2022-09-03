#include "Extractor.h"
#include "../../../models/Entity/ReadEntity.h"
#include "../../../models/Entity/PrintEntity.h"
#include "../../../models/Entity/VariableEntity.h"
#include "../../../models/Relationship/ModifyRelationship.h"
#include "../../../models/Relationship/UsesRelationship.h"

Extractor::Extractor() {}

void Extractor::extractRead(SimpleToken simpleToken, vector<string> tokens) {
	ReadEntity* leftEntity = new ReadEntity(to_string(simpleToken.statementNumber));
	VariableEntity* rightEntity = new VariableEntity(tokens.at(0));
	ModifyRelationship modifyRelationship = ModifyRelationship(leftEntity, rightEntity);
	// next step is to populate pkb
}

void Extractor::extractPrint(SimpleToken simpleToken, vector<string> tokens) {
	PrintEntity* leftEntity = new PrintEntity(to_string(simpleToken.statementNumber));
	VariableEntity* rightEntity = new VariableEntity(tokens.at(0));
	UsesRelationship usesRelationship = UsesRelationship(leftEntity, rightEntity);
	// next step is to populate pkb
}

/* TO BE IMPLEMENTED */
void Extractor::extractProcedure() {}
void Extractor::extractStatement() {}
void Extractor::extractCall() {}
void Extractor::extractWhile() {}
void Extractor::extractIf() {}
void Extractor::extractAssign() {}
void Extractor::extractCondExpr() {}
void Extractor::extractVariable() {}
void Extractor::extractConstant() {}
void Extractor::extractClose() {}
void Extractor::extractOpr() {}
void Extractor::extractError() {}
