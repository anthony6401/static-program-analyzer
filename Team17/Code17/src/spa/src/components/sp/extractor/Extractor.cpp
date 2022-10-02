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

}

void Extractor::extractPrint(SimpleToken printToken) {

}

void Extractor::extractAssign(SimpleToken assignToken) {

}

void Extractor::extractWhile(SimpleToken whileToken) {

}

void Extractor::extractIf(SimpleToken ifToken) {

}

void Extractor::extractExpr(SimpleToken exprToken) {

}

void Extractor::extractCall(SimpleToken callToken) {

}

void Extractor::extractProcedure(SimpleToken procedureToken) {

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
