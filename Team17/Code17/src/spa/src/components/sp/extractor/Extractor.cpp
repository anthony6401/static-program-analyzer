#include "Extractor.h"

Extractor::Extractor(SPClient* client) {
	this->client = client;
}

void Extractor::extractRead(SimpleToken simpleToken, std::vector<std::string> tokens) {
	ReadEntity* leftEntity = new ReadEntity(std::to_string(simpleToken.statementNumber));
	VariableEntity* rightEntity = new VariableEntity(tokens.at(0));
	ModifyRelationship* modifyRelationship = new ModifyRelationship(leftEntity, rightEntity);
	this->client->storeRelationship(modifyRelationship);
}

void Extractor::extractPrint(SimpleToken simpleToken, std::vector<std::string> tokens) {
	PrintEntity* leftEntity = new PrintEntity(std::to_string(simpleToken.statementNumber));
	VariableEntity* rightEntity = new VariableEntity(tokens.at(0));
	UsesRelationship* usesRelationship = new UsesRelationship(leftEntity, rightEntity);
	this->client->storeRelationship(usesRelationship);
}

void Extractor::extractProcedure() {
	ProcedureEntity* procedureEntity = new ProcedureEntity("");
	VariableEntity* variableEntity = new VariableEntity("");
	// implement stack in the future for further processing
}

void Extractor::extractAssign(SimpleToken simpleToken) {
	AssignEntity* assignEntity = new AssignEntity(std::to_string(simpleToken.statementNumber));
	std::vector<SimpleToken> children = simpleToken.getChildren();

	SimpleToken variable = children.at(0);
	VariableEntity* variableEntity = new VariableEntity(variable.value);
	ModifyRelationship* modifyRelationship = new ModifyRelationship(assignEntity, variableEntity);
	this->client->storeRelationship(modifyRelationship);

	SimpleToken expression = children.at(1);
	std::vector<SimpleToken> exprChildren = expression.getChildren();
	while (exprChildren.size() != 0) {
		SimpleToken token = exprChildren.at(0);
		if (token.type == SpTokenType::TVARIABLE) {
			VariableEntity* variableEntityInExpression = new VariableEntity(token.value);
			UsesRelationship* usesRelationship = new UsesRelationship(assignEntity, variableEntityInExpression);
			this->client->storeRelationship(usesRelationship);
		}
		else if (token.type == SpTokenType::TCONSTANT) {
			ConstantEntity* constantEntityInExpression = new ConstantEntity(token.value);
			UsesRelationship* usesRelationship = new UsesRelationship(assignEntity, constantEntityInExpression);
			this->client->storeRelationship(usesRelationship);
		}
		exprChildren.erase(exprChildren.begin());
	}
}

void Extractor::extractCall() {
	CallEntity* callEntity = new CallEntity("");
	VariableEntity* variableEntity = new VariableEntity("");
	// implement stack in the future for further processing
}

/* TO BE IMPLEMENTED */
// ================= //
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
