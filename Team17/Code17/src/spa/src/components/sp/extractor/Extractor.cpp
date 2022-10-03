#include "Extractor.h"

#include <iostream>

// Constructor
Extractor::Extractor(SPClient* client) {
	this->client = client;
	currentStack = new ProcedureStack(SimpleToken(), this);
}

// ======================== //
// FUNCTIONS FOR EXTRACTION //
// =========================//

void Extractor::extractRead(SimpleToken readToken) {
	this->currentStack->addFollows(readToken);
	this->currentStack->modifies.push_back(readToken);

	Entity* left = generateEntity(readToken);
	Entity* right = generateEntity(readToken.getChildren().at(0));
	ModifyRelationship* relationship = new ModifyRelationship(left, right);
	this->client->storeRelationship(relationship);
}

void Extractor::extractPrint(SimpleToken printToken) {
	this->currentStack->addFollows(printToken);
	this->currentStack->uses.push_back(printToken);

	Entity* left = generateEntity(printToken);
	Entity* right = generateEntity(printToken.getChildren().at(0));
	UsesRelationship* relationship = new UsesRelationship(left, right);
	this->client->storeRelationship(relationship);
}

void Extractor::extractAssign(SimpleToken assignToken) {
	this->currentStack->addFollows(assignToken);
	SimpleToken varToken = assignToken.getChildren().at(0);
	this->currentStack->modifies.push_back(varToken);

	Entity* left = generateEntity(assignToken);
	Entity* right = generateEntity(assignToken.getChildren().at(0));
	ModifyRelationship* relationship = new ModifyRelationship(left, right);
	this->client->storeRelationship(relationship);

	SimpleToken exprToken = assignToken.getChildren().at(1);
	extractExpr(assignToken, exprToken);

	//Pattern assignPattern = createAssignPattern(assignToken);
	//this->currentStack->addAssignPattern(assignPattern);
}

void Extractor::extractWhile(SimpleToken whileToken) {
	this->currentStack->addFollows(whileToken);
	extractExpr(whileToken, whileToken);

	// create new while stack and set it as the current stack, old stack gets added to parentStack
	this->parentStack.push(currentStack);
	this->currentStack = new WhileStack(whileToken, this);
}

void Extractor::extractIf(SimpleToken ifToken) {
	this->currentStack->addFollows(ifToken);
	extractExpr(ifToken, ifToken);

	// create new if stack and set it as the current stack, old stack gets added to parentStack
	this->parentStack.push(currentStack);
	this->currentStack = new IfStack(ifToken, this);
}

void Extractor::extractExpr(SimpleToken stmtToken, SimpleToken exprToken) {
	std::vector<SimpleToken> exprChildren = exprToken.getChildren();
	for (int i = 0; i < exprChildren.size(); i++) {
		SimpleToken currentToken = exprChildren.at(i);
		if (currentToken.type == SpTokenType::TVARIABLE) {
			this->currentStack->uses.push_back(currentToken);

			Entity* left = generateEntity(stmtToken);
			Entity* right = generateEntity(currentToken);
			UsesRelationship* relationship = new UsesRelationship(left, right);
			this->client->storeRelationship(relationship);
		}
	}
}

void Extractor::extractCall(SimpleToken callToken) {
	this->currentStack->addFollows(callToken);

	Entity* left = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, this->currentProcedure, 0));
	Entity* right = generateEntity(callToken.getChildren().at(0));
	CallsRelationship* relationship = new CallsRelationship(left, right);
	this->client->storeRelationship(relationship);

	this->callProcedures.insert(std::pair<std::string, std::string>(this->currentStack->parent.value, callToken.value));
}

void Extractor::extractProcedure(SimpleToken procedureToken) {
	this->currentStack = new ProcedureStack(procedureToken, this);
	this->currentProcedure = procedureToken.value;
}

/*
void Extractor::endOfParser() {
	// for all called proc in proc, get procstack from the map, add the rel to parent proc
	// recurse
}


Pattern* Extractor::createAssignPattern(SimpleToken token) {

}*/

void Extractor::close(int statementNumber) {
	currentStack->close(statementNumber);
}

Entity* Extractor::generateEntity(SimpleToken token) {
	if (token.type == SpTokenType::TREAD) {
		return new ReadEntity(std::to_string(token.statementNumber));
	}
	if (token.type == SpTokenType::TPRINT) {
		return new PrintEntity(std::to_string(token.statementNumber));
	}
	if (token.type == SpTokenType::TASSIGN) {
		return new AssignEntity(std::to_string(token.statementNumber));
	}
	if (token.type == SpTokenType::TWHILE) {
		return new WhileEntity(std::to_string(token.statementNumber));
	}
	if (token.type == SpTokenType::TIF) {
		return new IfEntity(std::to_string(token.statementNumber));
	}
	if (token.type == SpTokenType::TVARIABLE) {
		return new VariableEntity(token.value);
	}
	if (token.type == SpTokenType::TCONSTANT) {
		return new ConstantEntity(token.value);
	}
	if (token.type == SpTokenType::TPROCEDURE) {
		return new ProcedureEntity(token.value);
	}
	if (token.type == SpTokenType::TCALL) {
		return new CallEntity(std::to_string(token.statementNumber));
	}
	return new Entity(std::to_string(token.statementNumber)); // Should not happen
}
