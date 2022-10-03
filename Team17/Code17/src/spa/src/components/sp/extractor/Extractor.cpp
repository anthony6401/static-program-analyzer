#include "Extractor.h"

#include <iostream>

// Constructor
Extractor::Extractor(SPClient* client) {
	std::stack<StmtStack> parentStack;
	std::map<std::string, ProcedureStack*> procedures;
	StmtStack currentStack = StmtStack();
	this->client = client;
	this->parentStack = parentStack;
	this->procedures = procedures;
	this->currentStack = currentStack;
}

// ======================== //
// FUNCTIONS FOR EXTRACTION //
// =========================//

void Extractor::extractRead(SimpleToken readToken) {
	this->currentStack.addFollows(readToken);
	ModifyRelationship* modifyRelationship = createModifyRelationship(readToken);
	this->currentStack.addModify(modifyRelationship);
}

void Extractor::extractPrint(SimpleToken printToken) {
	this->currentStack.addFollows(printToken);
	UsesRelationship* usesRelationship = createUsesRelationship(printToken);
	this->currentStack.addUses(usesRelationship);
}

void Extractor::extractAssign(SimpleToken assignToken) {
	this->currentStack.addFollows(assignToken);
	SimpleToken varToken = assignToken.getChildren().at(0);
	ModifyRelationship* modifyRelationship = createModifyRelationship(varToken);
	this->currentStack.addModify(modifyRelationship);

	SimpleToken exprToken = assignToken.getChildren().at(1);
	extractExpr(assignToken, exprToken);

	Pattern assignPattern = createAssignPattern(assignToken);
	this->currentStack.addAssignPattern(assignPattern);
}

void Extractor::extractWhile(SimpleToken whileToken) {
	this->currentStack.addFollows(whileToken);
	extractExpr(whileToken, whileToken);

	// create new while stack and set it as the current stack, old stack gets added to parentStack
	this->parentStack.push(currentStack);
	WhileStack whileStack = WhileStack(whileToken, this);
	this->currentStack = whileStack;
}

void Extractor::extractIf(SimpleToken ifToken) {
	this->currentStack.addFollows(ifToken);
	extractExpr(ifToken, ifToken);

	// create new if stack and set it as the current stack, old stack gets added to parentStack
	this->parentStack.push(currentStack);
	IfStack ifStack = IfStack(ifToken, this);
	this->currentStack = ifStack;
}

void Extractor::extractExpr(SimpleToken stmtToken, SimpleToken exprToken) {
	std::vector<SimpleToken> exprChildren = exprToken.getChildren();
	for (int i = 0; i < exprChildren.size(); i++) {
		SimpleToken currentToken = exprChildren.at(i);
		if (currentToken.type == SpTokenType::TVARIABLE) {
			UsesRelationship* usesRelationship = createUsesRelationshipExpr(stmtToken, currentToken);
			this->currentStack.addUses(usesRelationship);
		}
	}
}

void Extractor::extractCall(SimpleToken callToken) {
	this->currentStack.addFollows(callToken);
	CallsRelationship* callsRelationship = createCallsRelationship(callToken);
	this->currentStack.addCall(callsRelationship);
	this->procedures.addProcedure();
}

void Extractor::extractProcedure(SimpleToken procedureToken) {
	this->parentStack.push(currentStack);
	ProcedureStack procStack = ProcedureStack(procedureToken, this);
	this->currentStack = procStack;
}

void Extractor::extractClose(SimpleToken closeToken) {
	extractFollows(this->currentStack);
	extractParent(this->currentStack);
	this->currentStack.mergeStack();
}

void Extractor::extractFollows(StmtStack currentStack) {
	std::vector<SimpleToken> follows = this->currentStack.follows;
	for (int i = 0; i < follows.size() - 1; i++) {
		Entity* left = generateEntity(follows.at(i));
		Entity* right = generateEntity(follows.at(i + 1));
		FollowsRelationship* followsRelationship = new FollowsRelationship(left, right);
		// add to client here?
	}
	for (int i = 0; i < follows.size(); i++) {
		for (int j = i + 1; j < follows.size(); j++) {
			SimpleToken left = follows.at(i);
			SimpleToken right = follows.at(j);
			FollowsTRelationship* followsTRelationship = new FollowsTRelationship(left, right);
			// add to client here?
		}
	}
}

void Extractor::extractParent(StmtStack currentStack) {

}

void Extractor::endOfParser() {

}

UsesRelationship* Extractor::createUsesRelationship(SimpleToken token) {
	Entity* left = generateEntity(token);
	Entity* right = generateEntity(token.getChildren().at(0));
	return new UsesRelationship(left, right);
}

ModifyRelationship* Extractor::createModifyRelationship(SimpleToken token) {
	Entity* left = generateEntity(token);
	Entity* right = generateEntity(token.getChildren().at(0));
	return new ModifyRelationship(left, right);
}

UsesRelationship* Extractor::createUsesRelationshipExpr(SimpleToken stmtToken, SimpleToken exprToken) {
	Entity* left = generateEntity(stmtToken);
	Entity* right = generateEntity(exprToken);
	return new UsesRelationship(left, right);
}

CallsRelationship* Extractor::createCallsRelationship(SimpleToken token) {
	Entity* left = generateEntity(token);
	Entity* right = generateEntity(token);
	return new CallsRelationship(left, right);
}

Pattern* Extractor::createAssignPattern(SimpleToken token) {

}

void Extractor::close(int statementNumber) {
	currentStack.close(statementNumber);
}

Entity* UsesExtractor::generateEntity(SimpleToken token) {
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
	// add in call type
	return new Entity(std::to_string(token.statementNumber)); // Should not happen
}
