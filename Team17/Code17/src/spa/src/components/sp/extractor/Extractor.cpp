#include "Extractor.h"

#include <iostream>

Extractor::Extractor(SPClient* client) {
	this->client = client;
}

void Extractor::extractRead(SimpleToken simpleToken) {
	if (simpleToken.type == SpTokenType::TREAD) {
		ReadEntity* leftEntity = new ReadEntity(std::to_string(simpleToken.statementNumber));
		VariableEntity* rightEntity = new VariableEntity(simpleToken.getChildren().at(0).value);
		ModifyRelationship* modifyRelationship = new ModifyRelationship(leftEntity, rightEntity);
		this->client->storeRelationship(modifyRelationship);
	} else {
		throw std::invalid_argument("Invalid token type for extractRead");
	}
}

void Extractor::extractPrint(SimpleToken simpleToken) {
	if (simpleToken.type == SpTokenType::TPRINT) {
		PrintEntity* leftEntity = new PrintEntity(std::to_string(simpleToken.statementNumber));
		VariableEntity* rightEntity = new VariableEntity(simpleToken.getChildren().at(0).value);
		UsesRelationship* usesRelationship = new UsesRelationship(leftEntity, rightEntity);
		this->client->storeRelationship(usesRelationship);
	}
	else {
		throw std::invalid_argument("Invalid token type for extractPrint");
	}
}

void Extractor::extractAssign(SimpleToken simpleToken) {
	if (simpleToken.type != SpTokenType::TASSIGN) {
		throw std::invalid_argument("Invalid token type for extractAssign");
	}

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

void Extractor::extractWhile(SimpleToken simpleToken) {
	if (simpleToken.type != SpTokenType::TWHILE) {
		throw std::invalid_argument("Invalid token type for extractWhile");
	}

	WhileEntity* whileEntity = new WhileEntity(std::to_string(simpleToken.statementNumber));
	std::vector<SimpleToken> children = simpleToken.getChildren();

	SimpleToken condExpr = children.at(0); // Condirion expression
	extractCondExpr(whileEntity, condExpr);

	SimpleToken stmtLst = children.at(1); // Statement list in while loop
	extractStmtLst(stmtLst);
}

void Extractor::extractIf(SimpleToken simpleToken) {
	if (simpleToken.type != SpTokenType::TIF) {
		throw std::invalid_argument("Invalid token type for extractIf");
	}

	IfEntity* ifEntity = new IfEntity(std::to_string(simpleToken.statementNumber));
	std::vector<SimpleToken> children = simpleToken.getChildren();

	SimpleToken condExpr = children.at(0); // Condition expression
	extractCondExpr(ifEntity, condExpr);

	SimpleToken stmtLst1 = children.at(1); // If statement
	extractStmtLst(stmtLst1);
	SimpleToken stmtLst2 = children.at(2); // Else statement
	extractStmtLst(stmtLst2);
}

void Extractor::extractCondExpr(WhileEntity* whileEntity, SimpleToken simpleToken) {
	if (simpleToken.type != SpTokenType::TCONDEXPR) {
		throw std::invalid_argument("Invalid token type for extractCondExpr");
	}

	// code here
}

void Extractor::extractCondExpr(IfEntity* ifEntity, SimpleToken simpleToken) {
	if (simpleToken.type != SpTokenType::TIF) {
		throw std::invalid_argument("Invalid token type for extractCondExpr");
	}

	// code here
}

void Extractor::extractStmtLst(SimpleToken simpleToken) {
	if (simpleToken.type != SpTokenType::TSTMT) {
		throw std::invalid_argument("Invalid token type for extractStmtLst");
	}

	std::vector<SimpleToken> children = simpleToken.getChildren();
	while (children.size() != 0) {
		SimpleToken token = children.at(0);
		if (token.type == SpTokenType::TREAD) {
			extractRead(token);
		} else if (token.type == SpTokenType::TPRINT) {
			extractPrint(token);
		} else if (token.type == SpTokenType::TASSIGN) {
			extractAssign(token);
		} else if (token.type == SpTokenType::TWHILE) {
			extractWhile(token);
		} else if (token.type == SpTokenType::TIF) {
			extractIf(token);
		} else if (token.type == SpTokenType::TCALL) {
			// code here
		}
		children.erase(children.begin());
	}
}

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
