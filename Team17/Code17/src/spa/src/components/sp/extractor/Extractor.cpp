#include "Extractor.h"

void Extractor::extractRead(SimpleToken simpleToken, vector<string> tokens) {
	ReadEntity* leftEntity = new ReadEntity(to_string(simpleToken.statementNumber));
	VariableEntity* rightEntity = new VariableEntity(tokens.at(0));
	ModifyRelationship* modifyRelationship = new ModifyRelationship(leftEntity, rightEntity);
	// next step is to populate pkb
}

void Extractor::extractPrint(SimpleToken simpleToken, vector<string> tokens) {
	PrintEntity* leftEntity = new PrintEntity(to_string(simpleToken.statementNumber));
	VariableEntity* rightEntity = new VariableEntity(tokens.at(0));
	UsesRelationship* usesRelationship = new UsesRelationship(leftEntity, rightEntity);
	// next step is to populate pkb
}

/* TO BE IMPLEMENTED */
// ================= //
void Extractor::extractProcedure() {
	ProcedureEntity* procedureEntity = new ProcedureEntity("");
	VariableEntity* variableEntity = new VariableEntity("");
	// implement stack in the future for further processing
}

void Extractor::extractCall() {
	CallEntity* callEntity = new CallEntity("");
	VariableEntity* variableEntity = new VariableEntity("");
	// implement stack in the future for further processing
}

void Extractor::extractWhile() {
	WhileEntity* whileEntity = new WhileEntity("");
	VariableEntity* variableEntity = new VariableEntity("");
	// implement stack in the future for further processing
}

void Extractor::extractIf() {
	IfEntity* ifEntity = new IfEntity("");
	VariableEntity* variableEntity = new VariableEntity("");
	// implement stack in the future for further processing
}

void Extractor::extractAssign() {
	AssignEntity* assignEntity = new AssignEntity("");
	VariableEntity* variableEntity = new VariableEntity("");
	// could be a Uses or a Modify
	// Pattern
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
