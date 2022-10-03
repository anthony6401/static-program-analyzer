#include "Extractor.h"

#include <iostream>

// Constructor
Extractor::Extractor(SPClient* client) {
	this->client = client;
}

// Parser only needs to call Extractor::extractAll
void Extractor::extractAll(SimpleToken procedureToken) {
	extractFollows(procedureToken);
	extractParent(procedureToken);
	extractUses(procedureToken);
	extractModify(procedureToken);
	extractPattern(procedureToken);
	extractConstants(procedureToken);
}

void Extractor::close(int statementNumber) {
	currentStack->close(statementNumber);
}

// =============================== //
// HELPER FUNCTIONS FOR EXTRACTION //
// =============================== //

void Extractor::extractFollows(SimpleToken procOrWhileIfToken) {
	std::vector<FollowsRelationship*> followsVector = FollowsExtractor::extractFollows(procOrWhileIfToken);
	std::vector<FollowsTRelationship*> followsTVector = FollowsExtractor::extractFollowsT(procOrWhileIfToken);
	storeFollowsRelationships(followsVector);
	storeFollowsTRelationships(followsTVector);
}

void Extractor::extractParent(SimpleToken procOrWhileIfToken) {
	std::vector<ParentRelationship*> parentVector = ParentExtractor::extractParent(procOrWhileIfToken);
	std::vector<ParentTRelationship*> parentTVector = ParentExtractor::extractParentT(procOrWhileIfToken);
	storeParentRelationships(parentVector);
	storeParentTRelationships(parentTVector);
}

void Extractor::extractUses(SimpleToken procOrWhileIfToken) {
	std::vector<UsesRelationship*> usesVector = UsesExtractor::extractUses(procOrWhileIfToken);
	storeUsesRelationships(usesVector);
}

void Extractor::extractModify(SimpleToken procOrWhileIfToken) {
	std::vector<ModifyRelationship*> modifyVector = ModifyExtractor::extractModify(procOrWhileIfToken);
	storeModifyRelationships(modifyVector);
}

void Extractor::extractPattern(SimpleToken procOrWhileIfToken) {
	std::vector<AssignPattern*> assignPatternVector = PatternExtractor::extractPattern(procOrWhileIfToken);
	storeAssignPatterns(assignPatternVector);
}

void Extractor::extractConstants(SimpleToken procedureToken) {
	std::vector<ConstantEntity*> constantVector = extractConstantsVector(procedureToken);
	for (int i = 0; i < constantVector.size(); i++) {
		this->client->storeConstant(constantVector.at(i));
	}
}

std::vector<ConstantEntity*> Extractor::extractConstantsVector(SimpleToken procedureToken) {
	std::vector<ConstantEntity*> constantVector;

	for (int i = 0; i < procedureToken.getChildren().size(); i++) {
		SimpleToken current = procedureToken.getChildren().at(i);
		if (current.type == SpTokenType::TCONSTANT) {
			ConstantEntity* constantEntity = new ConstantEntity(current.value);
			constantVector.push_back(constantEntity);
		}

		std::vector<ConstantEntity*> moreConstantVector = extractConstantsVector(current);
		constantVector.insert(constantVector.end(), moreConstantVector.begin(), moreConstantVector.end());
	}

	return constantVector;
}

// ============================ //
// HELPER FUNCTIONS FOR STORING //
// ============================ //

void Extractor::storeFollowsRelationships(std::vector<FollowsRelationship*> vector) {
	for (int i = 0; i < vector.size(); i++) {
		this->client->storeRelationship(vector.at(i));
	}
}

void Extractor::storeFollowsTRelationships(std::vector<FollowsTRelationship*> vector) {
	for (int i = 0; i < vector.size(); i++) {
		this->client->storeRelationship(vector.at(i));
	}
}

void Extractor::storeParentRelationships(std::vector<ParentRelationship*> vector) {
	for (int i = 0; i < vector.size(); i++) {
		this->client->storeRelationship(vector.at(i));
	}
}

void Extractor::storeParentTRelationships(std::vector<ParentTRelationship*> vector) {
	for (int i = 0; i < vector.size(); i++) {
		this->client->storeRelationship(vector.at(i));
	}
}

void Extractor::storeUsesRelationships(std::vector<UsesRelationship*> vector) {
	for (int i = 0; i < vector.size(); i++) {
		this->client->storeRelationship(vector.at(i));
	}
}

void Extractor::storeModifyRelationships(std::vector<ModifyRelationship*> vector) {
	for (int i = 0; i < vector.size(); i++) {
		this->client->storeRelationship(vector.at(i));
	}
}

void Extractor::storeAssignPatterns(std::vector<AssignPattern*> vector) {
	for (int i = 0; i < vector.size(); i++) {
		this->client->storePattern(vector.at(i));
	}
}

/*
void Extractor::extractProcedure(SimpleToken procedureToken) {
	if (procedureToken.type != SpTokenType::TPROCEDURE) {
		throw std::invalid_argument("Invalid token type for extractProcedure");
	}
	std::vector<SimpleToken> childrenOfProcedureToken = procedureToken.getChildren();
	extractParentRelationships(procedureToken, childrenOfProcedureToken);
	extractFollowsRelationships(childrenOfProcedureToken);

	extractUsesRelationshipsForProcedure(procedureToken);
	extractModifyRelationshipsForProcedure(procedureToken);

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

void Extractor::extractUsesRelationshipsForProcedure(SimpleToken procedureToken) {

}

void Extractor::extractModifyRelationshipsForProcedure(SimpleToken procedureToken) {

}

void Extractor::extractSeriesOfStmts(std::vector<SimpleToken> seriesOfStmts) {
	int i = 0;
	while (i < seriesOfStmts.size()) {
		SimpleToken stmtToken = seriesOfStmts.at(i);
		if (stmtToken.type == SpTokenType::TREAD) {
			extractReadStmt(stmtToken);
		}
		if (stmtToken.type == SpTokenType::TPRINT) {
			extractPrintStmt(stmtToken);
		}
		if (stmtToken.type == SpTokenType::TASSIGN) {
			extractAssignStmt(stmtToken);
		}
		if (stmtToken.type == SpTokenType::TWHILE) {
			extractWhileStmt(stmtToken);
		}
		if (stmtToken.type == SpTokenType::TIF) {
			extractIfStmt(stmtToken);
		}
		if (stmtToken.type == SpTokenType::TCALL) {
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
	ModifyRelationship* modifyRelationship = getModifyRelationshipForAssign(simpleToken);
	this->client->storeRelationship(modifyRelationship);

	std::vector<UsesRelationship*> usesRelationships = getUsesRelationshipsForAssign(simpleToken);
	for (int i = 0; i < usesRelationships.size(); i++) {
		this->client->storeRelationship(usesRelationships.at(i));
	}

	PatternExtractor::extractPattern(*this, simpleToken);
}

ModifyRelationship* Extractor::getModifyRelationshipForAssign(SimpleToken simpleToken) {
	AssignEntity* assignEntity = new AssignEntity(std::to_string(simpleToken.statementNumber));
	std::vector<SimpleToken> children = simpleToken.getChildren();

	SimpleToken variable = children.at(0);
	VariableEntity* variableEntity = new VariableEntity(variable.value);

	return new ModifyRelationship(assignEntity, variableEntity);
}

std::vector<UsesRelationship*> Extractor::getUsesRelationshipsForAssign(SimpleToken simpleToken) {
	AssignEntity* assignEntity = new AssignEntity(std::to_string(simpleToken.statementNumber));
	std::vector<SimpleToken> children = simpleToken.getChildren();

	SimpleToken expression = children.at(1);
	std::vector<SimpleToken> expressionChildren = expression.getChildren();

	std::vector<UsesRelationship*> usesRelationships;

	for (int i = 0; i < expressionChildren.size(); i++) {
		SimpleToken token = expressionChildren.at(i);
		if (token.type == SpTokenType::TVARIABLE) {
			VariableEntity* variableEntityInExpression = new VariableEntity(token.value);
			UsesRelationship* usesRelationship = new UsesRelationship(assignEntity, variableEntityInExpression);
			usesRelationships.push_back(usesRelationship);
		}
	}

	return usesRelationships;
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
	if (stmtLstToken.type != SpTokenType::TSTMTLIST) {
		throw std::invalid_argument("Invalid token type for extractStmtLst");
	}
	std::vector<SimpleToken> seriesOfStmts = stmtLstToken.getChildren();
	extractSeriesOfStmts(seriesOfStmts);
}

void Extractor::extractCondExpr(SimpleToken condToken, SimpleToken condExpr) {
	if (condExpr.type != SpTokenType::TCONDEXPR) {
		throw std::invalid_argument("Invalid token type for extractCondExpr");
	}
	std::vector<UsesRelationship*> usesRelationships = getUsesRelationshipsForCondExpr(condToken, condExpr);
	for (int i = 0; i < usesRelationships.size(); i++) {
		this->client->storeRelationship(usesRelationships.at(i));
	}
}

std::vector<UsesRelationship*> Extractor::getUsesRelationshipsForCondExpr(SimpleToken condToken, SimpleToken condExpr) {
	if (condToken.type != SpTokenType::TWHILE && condToken.type != SpTokenType::TIF) {
		throw std::invalid_argument("Invalid token type for Condiional Token");
	}
	Entity* condEntity;
	if (condToken.type == SpTokenType::TWHILE) {
		condEntity = new WhileEntity(std::to_string(condToken.statementNumber));
	}
	if (condToken.type == SpTokenType::TIF) {
		condEntity = new IfEntity(std::to_string(condToken.statementNumber));
	}

	std::vector<UsesRelationship*> usesRelationships;

	std::vector<SimpleToken> childrenOfCondExpr = condExpr.getChildren();
	for (int i = 0; i < childrenOfCondExpr.size(); i++) {
		SimpleToken current = childrenOfCondExpr.at(i);
		if (current.type == SpTokenType::TVARIABLE) {
			VariableEntity* variableEntity = new VariableEntity(current.value);
			UsesRelationship* usesRelationship = new UsesRelationship(condEntity, variableEntity);
			usesRelationships.push_back(usesRelationship);
		}
	}
	
	return usesRelationships;
}

void Extractor::extractCall() {
	CallEntity* callEntity = new CallEntity("");
	VariableEntity* variableEntity = new VariableEntity("");

	// To be implemented
}
*/
