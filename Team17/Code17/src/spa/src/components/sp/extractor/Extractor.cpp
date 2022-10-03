#include "Extractor.h"

#include <iostream>

// Constructor
Extractor::Extractor(SPClient* client) {
	this->client = client;
}

// ======================== //
// FUNCTIONS FOR EXTRACTION //
// =========================//

void Extractor::extractRead(SimpleToken readToken) {
	currentStack.addFollows(readToken);
	ModifyRelationship modifyRelationship = createModifyRelationship(readToken);
	currentStack.addUses(modifyRelationship);
}

void Extractor::extractPrint(SimpleToken printToken) {
	currentStack.addFollows(printToken);
	UsesRelationship usesRelationship = createUsesRelationship(printToken);
	currentStack.addUses(usesRelationship);
}

void Extractor::extractAssign(SimpleToken assignToken) {
	currentStack.addFollows(assignToken);
	SimpleToken varToken = assignToken.getChildren().at(0);
	ModifyRelationship modifyRelationship = createModifyRelationship(varToken);
	currentStack.addModify(modifyRelationship);

	SimpleToken exprToken = assignToken.getChildren().at(1);
	extractExpr(assignToken, exprToken);

	Pattern assignPattern = createAssignPattern(assignToken);
	currentStack.addAssignPattern(assignPattern);
}

void Extractor::extractWhile(SimpleToken whileToken) {
	currentStack.addFollows(whileToken);	
	extractExpr(whileToken, whileToken);

	// create new while stack and set it as the current stack, old stack gets added to parentStack
	parentStack.insert(currentStack);
	currentStack = new WhileStack(whileToken, this);
}

void Extractor::extractIf(SimpleToken ifToken) {
	currentStack.addFollows(ifToken);
	extractExpr(ifToken, ifToken);

	// create new if stack and set it as the current stack, old stack gets added to parentStack
	parentStack.insert(currentStack);
	currentStack = new IfStack(ifToken, this);
}

void Extractor::extractExpr(SimpleToken stmtToken, SimpleToken exprToken) {
	std::vector<SimpleToken> exprChildren = exprToken.getChildren();
	for (int i = 0; i < exprChildren.size(); i++) {
		SimpleToken currentToken = exprChildren.at(i);
		if (currentToken.type == SpTokenType::TVARIABLE) {
			UsesRelationship usesRelationship = createUsesRelationshipExpr(stmtToken, currentToken);
			currentStack.addUses(usesRelationship);
		}
	}
}

void Extractor::extractCall(SimpleToken callToken) {
	currentStack.addFollows(callToken);
	CallRelationship callRelationship = createCallRelationship(callToken);
	currentStack.addCall(callRelationship);
	currentStack.addProcedure();
}

void Extractor::extractProcedure(SimpleToken procedureToken) {
	parentStack.insert(currentStack);
	currentStack = new ProcedureStack(procedureToken, this);
}

void Extractor::extractClose(SimpleToken closeToken) {

}

void Extractor::extractFollows() {

}

void Extractor::extractParent() {

}

void Extractor::endOfParser() {

}

/*
// Parser only needs to call Extractor::extractAll
void Extractor::extractAll(SimpleToken procedureToken) {
	extractFollows(procedureToken);
	extractParent(procedureToken);
	extractUses(procedureToken);
	extractModify(procedureToken);
	extractPattern(procedureToken);
	extractConstants(procedureToken);
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
*/
