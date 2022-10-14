#include "Extractor.h"

#include <iostream>

Extractor::Extractor(SPClient* client) : currentStack(nullptr) {
	this->client = client;
	this->first = true;
}

void Extractor::extractRead(SimpleToken readToken) {
	this->currentStack->stmts.push_back(readToken);
	this->currentStack->varMod.push_back(SimpleToken(SpTokenType::TVARIABLE, readToken.value, 0));

	Entity* left = generateEntity(readToken);
	Entity* right = generateEntity(SimpleToken(SpTokenType::TVARIABLE, readToken.value, 0));
	ModifyRelationship* relationship = new ModifyRelationship(left, right);
	this->client->storeRelationship(relationship);

	extractNext(readToken);
}

void Extractor::extractPrint(SimpleToken printToken) {
	this->currentStack->stmts.push_back(printToken);
	this->currentStack->varUse.push_back(SimpleToken(SpTokenType::TVARIABLE, printToken.value, 0));

	Entity* left = generateEntity(printToken);
	Entity* right = generateEntity(SimpleToken(SpTokenType::TVARIABLE, printToken.value, 0));
	UsesRelationship* relationship = new UsesRelationship(left, right);
	this->client->storeRelationship(relationship);

	extractNext(printToken);
}

void Extractor::extractAssign(SimpleToken assignToken) {
	this->currentStack->stmts.push_back(assignToken);
	SimpleToken varToken = assignToken.getChildren().at(0);
	this->currentStack->varMod.push_back(varToken);

	Entity* left = generateEntity(assignToken);
	Entity* right = generateEntity(varToken);
	ModifyRelationship* relationship = new ModifyRelationship(left, right);
	this->client->storeRelationship(relationship);

	SimpleToken exprToken = assignToken.getChildren().at(1);
	extractExpr(assignToken, exprToken);
	extractAssignPattern(assignToken);

	extractNext(assignToken);
}

void Extractor::extractAssignPattern(SimpleToken assignToken) {
	SimpleToken varToken = assignToken.getChildren().at(0);
	SimpleToken exprToken = assignToken.getChildren().at(1);
	std::string lineNum = std::to_string(assignToken.statementNumber);
	std::string firstVal = varToken.value;
	std::string seconVal = exprToken.value;
	AssignPattern* assignPattern = new AssignPattern(lineNum, firstVal, seconVal);
	this->client->storePattern(assignPattern);
}

void Extractor::extractWhile(SimpleToken whileToken) {
	this->currentStack->stmts.push_back(whileToken);
	extractExpr(whileToken, whileToken);
	extractWhilePattern(whileToken);

	extractNext(whileToken);
	whileTokens.push(whileToken);

	this->parentStack.push(currentStack);
	this->currentStack = new WhileStack(whileToken, this);
}

void Extractor::extractIf(SimpleToken ifToken) {
	this->currentStack->stmts.push_back(ifToken);
	extractExpr(ifToken, ifToken);
	extractIfPattern(ifToken);
	
	extractNext(ifToken);
	if (first) {
		ifTokens.push(ifToken);
		first = false;
	} else {
		ifTokens.push(ifToken);
		ifTokens.push(ifToken);
	}

	this->parentStack.push(currentStack);
	this->currentStack = new IfStack(ifToken, this);
}

void Extractor::extractWhilePattern(SimpleToken whileToken) {
	std::vector<SimpleToken> condExpr = whileToken.getChildren();
	for (int i = 0; i < condExpr.size(); i++) {
		if (condExpr.at(i).type == SpTokenType::TVARIABLE) {
			std::string lineNum = std::to_string(whileToken.statementNumber);
			std::string value = condExpr.at(i).value;
			WhilePattern* whilePattern = new WhilePattern(lineNum, value);
			this->client->storePattern(whilePattern);
		}
	}
}

void Extractor::extractIfPattern(SimpleToken ifToken) {
	std::vector<SimpleToken> condExpr = ifToken.getChildren();
	for (int i = 0; i < condExpr.size(); i++) {
		if (condExpr.at(i).type == SpTokenType::TVARIABLE) {
			std::string lineNum = std::to_string(ifToken.statementNumber);
			std::string value = condExpr.at(i).value;
			IfPattern* ifPattern = new IfPattern(lineNum, value);
			this->client->storePattern(ifPattern);
		}
	}
}

void Extractor::extractExpr(SimpleToken stmtToken, SimpleToken exprToken) {
	std::vector<SimpleToken> exprChildren = exprToken.getChildren();
	for (int i = 0; i < exprChildren.size(); i++) {
		SimpleToken currentToken = exprChildren.at(i);
		if (currentToken.type == SpTokenType::TVARIABLE) {
			this->currentStack->varUse.push_back(currentToken);

			Entity* left = generateEntity(stmtToken);
			Entity* right = generateEntity(currentToken);
			UsesRelationship* relationship = new UsesRelationship(left, right);
			this->client->storeRelationship(relationship);
		}
		if (currentToken.type == SpTokenType::TCONSTANT) {
			this->client->storeConstant(new ConstantEntity(currentToken.value));
		}
	}
}

void Extractor::extractCall(SimpleToken callToken, std::string currentProcedure) {
	this->currentStack->stmts.push_back(callToken);

	extractNext(callToken);
}

void Extractor::extractProcedure(SimpleToken procedureToken) {
	this->currentStack = new ProcedureStack(procedureToken, this);
}

void Extractor::close(int statementNumber) {
	if (currentStack->parent.type == SpTokenType::TWHILE) {
		currentStack->close(statementNumber);
		extractNextWhile();
	} else if (currentStack->parent.type == SpTokenType::TIF) {
		currentStack->close(statementNumber);
		extractNextIf();
	} else {
		currentStack->close(statementNumber);
		endPoints.clear();
		previousStmt.clear();
	}
}

void Extractor::endOfParser(std::multimap<std::string, std::string> callProcedures) {
	std::vector<std::string> allProcedures;
	for (auto itr = callProcedures.begin(); itr != callProcedures.end(); ++itr) {
		std::string parent = itr->first;
		std::string called = itr->second;

		Entity* left = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, parent, 0));
		Entity* right = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, called, 0));
		CallsRelationship* relationship = new CallsRelationship(left, right);
		this->client->storeRelationship(relationship);

		auto itr2 = std::find(allProcedures.begin(), allProcedures.end(), parent);
		if (itr2 == allProcedures.end()) {
			allProcedures.push_back(parent);
		}
	}
	for (std::string proc : allProcedures) {
		std::vector<std::string> alrCalled;
		alrCalled.push_back(proc);
		endOfParserHelper(proc, proc, callProcedures, alrCalled);
	}
}

void Extractor::endOfParserHelper(std::string current, std::string called,
	std::multimap<std::string, std::string> callProcedures, std::vector<std::string> alrCalled) {
	if (current != called) {
		StmtStack* parentStack = procedures.find(current)->second;
		StmtStack* calledStack = procedures.find(called)->second;
		CallsTRelationship* callsTRel = new CallsTRelationship(new ProcedureEntity(current), new ProcedureEntity(called));
		this->client->storeRelationship(callsTRel);
		addNestedRelationships(parentStack, calledStack, current);
	}
	for (auto itr = callProcedures.begin(); itr != callProcedures.end(); ++itr) {
		std::string callProcParent = itr->first;
		std::string callProcCalled = itr->second;
		if (callProcParent == called && std::find(alrCalled.begin(), alrCalled.end(), callProcCalled) == alrCalled.end()) {
			alrCalled.push_back(callProcCalled);
			endOfParserHelper(current, callProcCalled, callProcedures, alrCalled);
		}
	}
}

void Extractor::addNestedRelationships(StmtStack* parentStack, StmtStack* calledStack, std::string name) {
	std::vector<SimpleToken> stmts = calledStack->stmts;
	std::vector<SimpleToken> stmtsNested = calledStack->stmtsNested;
	std::vector<SimpleToken> varUse = calledStack->varUse;
	std::vector<SimpleToken> varMod = calledStack->varMod;

	for (int i = 0; i < stmts.size(); i++) {
		SimpleToken second = stmts.at(i);
		Entity* firstEntity = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, name, 0));
		Entity* secondEntity = generateEntity(second);
		ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(parentTRel);
	}

	for (int i = 0; i < stmtsNested.size(); i++) {
		SimpleToken second = stmtsNested.at(i);
		Entity* firstEntity = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, name, 0));
		Entity* secondEntity = generateEntity(second);
		ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(parentTRel);
	}

	for (int i = 0; i < varUse.size(); i++) {
		SimpleToken second = varUse.at(i);
		Entity* firstEntity = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, name, 0));
		Entity* secondEntity = generateEntity(second);
		UsesRelationship* usesRel = new UsesRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(usesRel);
	}

	for (int i = 0; i < varMod.size(); i++) {
		SimpleToken second = varMod.at(i);
		Entity* firstEntity = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, name, 0));
		Entity* secondEntity = generateEntity(second);
		ModifyRelationship* modifyRel = new ModifyRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(modifyRel);
	}
}

void Extractor::extractNext(SimpleToken stmtToken) {
	if (currentStack->parent.type == SpTokenType::TPROCEDURE) {
		first = true;
		for (SimpleToken stmt : endPoints) {
			Entity* prev = generateEntity(stmt);
			Entity* next = generateEntity(stmtToken);
			NextRelationship* nextRel = new NextRelationship(prev, next);
			this->client->storeRelationship(nextRel);
		}
		endPoints.clear();
	}
	if (previousStmt.size() == 0) {
		for (SimpleToken stmt : endPoints) {
			Entity* prev = generateEntity(stmt);
			Entity* next = generateEntity(stmtToken);
			NextRelationship* nextRel = new NextRelationship(prev, next);
			this->client->storeRelationship(nextRel);
		}
		endPoints.clear();
	} else {
		Entity* prev = generateEntity(previousStmt.at(0));
		Entity* next = generateEntity(stmtToken);
		NextRelationship* nextRel = new NextRelationship(prev, next);
		this->client->storeRelationship(nextRel);	
	}
	previousStmt.clear();
	previousStmt.push_back(stmtToken);
}

void Extractor::extractNextWhile() {
	for (SimpleToken stmt : endPoints) {
		Entity* prev = generateEntity(stmt);
		Entity* next = generateEntity(whileTokens.top());
		NextRelationship* nextRel = new NextRelationship(prev, next);
		this->client->storeRelationship(nextRel);
	}
	endPoints.clear();
	previousStmt.clear();
	previousStmt.push_back(whileTokens.top());
	whileTokens.pop();
}

void Extractor::extractNextIf() {
	if (ifTokens.empty()) {
		previousStmt.clear();
	} else {
		previousStmt.clear();
		previousStmt.push_back(ifTokens.top());
		ifTokens.pop();
	}
}

Entity* Extractor::generateEntity(SimpleToken token) {
	if (token.type == SpTokenType::TREAD) {
		return new ReadEntity(std::to_string(token.statementNumber), token.value);
	}
	if (token.type == SpTokenType::TPRINT) {
		return new PrintEntity(std::to_string(token.statementNumber), token.value);
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
		return new CallEntity(std::to_string(token.statementNumber), token.value);
	}
	return new Entity(std::to_string(token.statementNumber)); // Should not happen
}
