#include "Extractor.h"

#include <iostream>

Extractor::Extractor(SPClient* client) {
	this->client = client;
}

void Extractor::extractProcedure(SimpleToken procedureToken) {
	if (procedureToken.type != SpTokenType::TPROCEDURE) {
		throw std::invalid_argument("Invalid token type for extractProcedure");
	}
	std::vector<SimpleToken> childrenOfProcedureToken = procedureToken.getChildren();
	extractParentRelationships(procedureToken, childrenOfProcedureToken);
	extractFollowsRelationships(childrenOfProcedureToken);

	extractSeriesOfStmts(childrenOfProcedureToken);
}

void Extractor::extractParentRelationships(SimpleToken parentToken, std::vector<SimpleToken> children) {
	ParentExtractor::extractParent(*this, parentToken, children);
	ParentExtractor::extractParentT(*this, parentToken, children);
}

void Extractor::extractFollowsRelationships(std::vector<SimpleToken> seriesOfStmts) {
	FollowsExtractor::extractFollows(*this, seriesOfStmts);
	FollowsExtractor::extractFollowsT(*this, seriesOfStmts);
}

void Extractor::extractSeriesOfStmts(std::vector<SimpleToken> seriesOfStmts) {
	int i = 0;
	while (i < seriesOfStmts.size()) {
		SimpleToken stmtToken = seriesOfStmts.at(i);
		if (stmtToken.type == SpTokenType::TREAD) {
			extractReadStmt(stmtToken);
		} else if (stmtToken.type == SpTokenType::TPRINT) {
			extractPrintStmt(stmtToken);
		} else if (stmtToken.type == SpTokenType::TASSIGN) {
			extractAssignStmt(stmtToken);
		} else if (stmtToken.type == SpTokenType::TWHILE) {
			extractWhileStmt(stmtToken);
		} else if (stmtToken.type == SpTokenType::TIF) {
			extractIfStmt(stmtToken);
		} else if (stmtToken.type == SpTokenType::TCALL) {
			// code here
		}
		i++;
	}
}

void Extractor::extractReadStmt(SimpleToken simpleToken) {
	if (simpleToken.type != SpTokenType::TREAD) {
		throw std::invalid_argument("Invalid token type for extractRead");
	}
	ModifyRelationship* modifyRelationship = getModifyRelationshipForRead(simpleToken);
	this->client->storeRelationship(modifyRelationship);
}

ModifyRelationship* Extractor::getModifyRelationshipForRead(SimpleToken simpleToken) {
	ReadEntity* leftEntity = new ReadEntity(std::to_string(simpleToken.statementNumber));
	VariableEntity* rightEntity = new VariableEntity(simpleToken.getChildren().at(0).value);
	return new ModifyRelationship(leftEntity, rightEntity);
}

void Extractor::extractPrintStmt(SimpleToken simpleToken) {
	if (simpleToken.type != SpTokenType::TPRINT) {
		throw std::invalid_argument("Invalid token type for extractPrint");
	}
	UsesRelationship* usesRelationship = getUsesRelationshipForPrint(simpleToken);
	this->client->storeRelationship(usesRelationship);
}

UsesRelationship* Extractor::getUsesRelationshipForPrint(SimpleToken simpleToken) {
	PrintEntity* leftEntity = new PrintEntity(std::to_string(simpleToken.statementNumber));
	VariableEntity* rightEntity = new VariableEntity(simpleToken.getChildren().at(0).value);
	return new UsesRelationship(leftEntity, rightEntity);
}

void Extractor::extractAssignStmt(SimpleToken simpleToken) {
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

	// Populate PKB with Patterns
	PatternExtractor::extractPattern(*this, variable, expression);

	// Populate PKB with UsesRelationship
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

void Extractor::extractWhileStmt(SimpleToken whileToken) {
	if (whileToken.type != SpTokenType::TWHILE) {
		throw std::invalid_argument("Invalid token type for extractWhile");
	}
	std::vector<SimpleToken> childrenOfWhileToken = whileToken.getChildren();
	extractParentRelationships(whileToken, childrenOfWhileToken);
	extractFollowsRelationships(childrenOfWhileToken);

	SimpleToken condExpr = childrenOfWhileToken.at(0); // Condition expression
	extractCondExpr(whileToken, condExpr);

	SimpleToken stmtLst = childrenOfWhileToken.at(1); // Statement list in while loop
	extractStmtLst(stmtLst);
}

void Extractor::extractIfStmt(SimpleToken ifToken) {
	if (ifToken.type != SpTokenType::TIF) {
		throw std::invalid_argument("Invalid token type for extractIf");
	}
	std::vector<SimpleToken> childrenOfIfToken = ifToken.getChildren();
	extractParentRelationships(ifToken, childrenOfIfToken);
	extractFollowsRelationships(childrenOfIfToken);

	SimpleToken condExpr = childrenOfIfToken.at(0); // Condition expression
	extractCondExpr(ifToken, condExpr);

	SimpleToken stmtLst1 = childrenOfIfToken.at(1); // If statement
	extractStmtLst(stmtLst1);
	SimpleToken stmtLst2 = childrenOfIfToken.at(2); // Else statement
	extractStmtLst(stmtLst2);
}

void Extractor::extractStmtLst(SimpleToken stmtLstToken) {
	if (stmtLstToken.type != SpTokenType::TSTMT) {
		throw std::invalid_argument("Invalid token type for extractStmtLst");
	}
	std::vector<SimpleToken> seriesOfStmts = stmtLstToken.getChildren();
	extractSeriesOfStmts(seriesOfStmts);
}

void Extractor::extractCondExpr(SimpleToken condToken, SimpleToken condExpr) {
	if (condExpr.type != SpTokenType::TCONDEXPR) {
		throw std::invalid_argument("Invalid token type for extractCondExpr");
	}

	// code here
}

void Extractor::extractCall() {
	CallEntity* callEntity = new CallEntity("");
	VariableEntity* variableEntity = new VariableEntity("");
	// implement stack in the future for further processing
}
