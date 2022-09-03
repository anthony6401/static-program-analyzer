#include "Extractor.h"

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

#include "../../../models/Relationship/ModifyRelationship.h"
#include "../../../models/Relationship/UsesRelationship.h"

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
// ================= //
void Extractor::extractProcedure() {
	ProcedureEntity* procedureEntity = new ProcedureEntity("");
}

void Extractor::extractStatement() {
	StatementEntity* statementEntity = new StatementEntity("");
}

void Extractor::extractCall() {
	CallEntity* callEntity = new CallEntity("");
}

void Extractor::extractWhile() {
	WhileEntity* whileEntity = new WhileEntity("");
}

void Extractor::extractIf() {
	IfEntity* ifEntity = new IfEntity("");
}

void Extractor::extractAssign() {
	AssignEntity* assignEntity = new AssignEntity("");
}

void Extractor::extractCondExpr() {}

void Extractor::extractVariable() {
	VariableEntity* variableEntity = new VariableEntity("");
}

void Extractor::extractConstant() {
	ConstantEntity* constantEntity = new ConstantEntity("");
}

void Extractor::extractClose() {}
void Extractor::extractOpr() {}
void Extractor::extractError() {}
