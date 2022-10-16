#include "Extractor.h"
#include <iostream>

Extractor::Extractor(SPClient* client) : currentStack(nullptr) {
	this->client = client;
}

void Extractor::extractRead(SimpleToken readToken) {
	this->currentStack->stmts.push_back(readToken);
	this->currentStack->varMod.insert(SimpleToken(SpTokenType::TVARIABLE, readToken.value, 0));

	Entity* left = generateEntity(readToken);
	Entity* right = generateEntity(SimpleToken(SpTokenType::TVARIABLE, readToken.value, 0));
	ModifyRelationship* relationship = new ModifyRelationship(left, right);
	this->client->storeRelationship(relationship);

	this->currentStack->extractNext(readToken);
}

void Extractor::extractPrint(SimpleToken printToken) {
	this->currentStack->stmts.push_back(printToken);
	this->currentStack->varUse.insert(SimpleToken(SpTokenType::TVARIABLE, printToken.value, 0));

	Entity* left = generateEntity(printToken);
	Entity* right = generateEntity(SimpleToken(SpTokenType::TVARIABLE, printToken.value, 0));
	UsesRelationship* relationship = new UsesRelationship(left, right);
	this->client->storeRelationship(relationship);

	this->currentStack->extractNext(printToken);
}

void Extractor::extractAssign(SimpleToken assignToken) {
	this->currentStack->stmts.push_back(assignToken);
	std::vector<SimpleToken> assignTokens = assignToken.getChildren();
	SimpleToken varToken = assignTokens.at(0);
	this->currentStack->varMod.insert(varToken);

	Entity* left = generateEntity(assignToken);
	Entity* right = generateEntity(varToken);
	ModifyRelationship* relationship = new ModifyRelationship(left, right);
	this->client->storeRelationship(relationship);

	SimpleToken exprToken = assignTokens.at(1);
	extractExpr(assignToken, exprToken);
	extractAssignPattern(assignToken);

	this->currentStack->extractNext(assignToken);
}

void Extractor::extractAssignPattern(SimpleToken assignToken) {
	std::vector<SimpleToken> assignTokens = assignToken.getChildren();
	SimpleToken varToken = assignTokens.at(0);
	SimpleToken exprToken = assignTokens.at(1);
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

	this->currentStack->extractNext(whileToken);

	this->parentStack.push(currentStack);
	this->currentStack = new WhileStack(whileToken, this);
}

void Extractor::extractIf(SimpleToken ifToken) {
	this->currentStack->stmts.push_back(ifToken);
	extractExpr(ifToken, ifToken);
	extractIfPattern(ifToken);
	
	this->currentStack->extractNext(ifToken);

	this->parentStack.push(currentStack);
	this->currentStack = new IfStack(ifToken, this);
}

void Extractor::extractWhilePattern(SimpleToken whileToken) {
	std::vector<SimpleToken> condExpr = whileToken.getChildren();
	std::string lineNum = std::to_string(whileToken.statementNumber);
	for (int i = 0; i < condExpr.size(); i++) {
		if (condExpr.at(i).type == SpTokenType::TVARIABLE) {
			std::string value = condExpr.at(i).value;
			WhilePattern* whilePattern = new WhilePattern(lineNum, value);
			this->client->storePattern(whilePattern);
		}
	}
}

void Extractor::extractIfPattern(SimpleToken ifToken) {
	std::vector<SimpleToken> condExpr = ifToken.getChildren();
	std::string lineNum = std::to_string(ifToken.statementNumber);
	for (int i = 0; i < condExpr.size(); i++) {
		if (condExpr.at(i).type == SpTokenType::TVARIABLE) {
			std::string value = condExpr.at(i).value;
			IfPattern* ifPattern = new IfPattern(lineNum, value);
			this->client->storePattern(ifPattern);
		}
	}
}

void Extractor::extractExpr(SimpleToken stmtToken, SimpleToken exprToken) {
	std::vector<SimpleToken> exprChildren = exprToken.getChildren();
	Entity* left = generateEntity(stmtToken);
	for (int i = 0; i < exprChildren.size(); i++) {
		SimpleToken currentToken = exprChildren.at(i);
		if (currentToken.type == SpTokenType::TVARIABLE) {
			this->currentStack->varUse.insert(currentToken);

			Entity* right = generateEntity(currentToken);
			UsesRelationship* relationship = new UsesRelationship(left, right);
			this->client->storeRelationship(relationship);
		}
		if (currentToken.type == SpTokenType::TCONSTANT) {
			this->client->storeConstant(new ConstantEntity(currentToken.value));
		}
	}
}

void Extractor::extractCall(SimpleToken callToken) {
	this->currentStack->stmts.push_back(callToken);
	this->currentStack->callStmts.push_back(callToken);

	this->currentStack->extractNext(callToken);
}

void Extractor::extractProcedure(SimpleToken procedureToken) {
	this->currentStack = new ProcedureStack(procedureToken, this);
}

void Extractor::close(int statementNumber) {
	if (currentStack->parent.type == SpTokenType::TWHILE) {
		currentStack->close(statementNumber);
	} else if (currentStack->parent.type == SpTokenType::TIF) {
		currentStack->close(statementNumber);
	} else {
		currentStack->close(statementNumber);
		previousStmt.clear();
	}
}

void Extractor::endOfParser(std::multimap<std::string, std::string> callProcedures) {
	for (auto itr = callProcedures.begin(); itr != callProcedures.end(); ++itr) {
		std::string parent = itr->first;
		std::string called = itr->second;

		Entity* left = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, parent, 0));
		Entity* right = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, called, 0));
		CallsRelationship* relationship = new CallsRelationship(left, right);
		this->client->storeRelationship(relationship);
	}

	std::vector<std::string> allProcedures;
	for (auto itr = procedures.begin(); itr != procedures.end(); ++itr) {
		allProcedures.push_back(itr->first);
	}

	for (std::string proc : allProcedures) {
		StmtStack* stack = procedures.find(proc)->second;
		std::unordered_set<SimpleToken, SimpleHash> varUse = stack->varUse;
		std::unordered_set<SimpleToken, SimpleHash> varMod = stack->varMod;
		for (SimpleToken use : varUse) {
			usesForCalls.insert(std::pair<std::string, SimpleToken>(proc, use));
		}
		for (SimpleToken mod : varMod) {
			modsForCalls.insert(std::pair<std::string, SimpleToken>(proc, mod));
		}
	}

	for (std::string proc : allProcedures) {
		std::vector<std::string> alrCalled;
		alrCalled.push_back(proc);
		endOfParserHelper(proc, proc, callProcedures, alrCalled);
	}

	for (std::string proc : allProcedures) {
		StmtStack* procStack = procedures.find(proc)->second;
		std::vector<SimpleToken> callStmts = procStack->callStmts;
		for (SimpleToken callStmt : callStmts) {
			Entity* left = generateEntity(callStmt);
			for (auto itr = usesForCalls.begin(); itr != usesForCalls.end(); ++itr) {
				if (itr->first == callStmt.value) {
					Entity* right = generateEntity(itr->second);
					UsesRelationship* rel = new UsesRelationship(left, right);
					this->client->storeRelationship(rel);
				}
			}
			for (auto itr = modsForCalls.begin(); itr != modsForCalls.end(); ++itr) {
				if (itr->first == callStmt.value) {
					Entity* left = generateEntity(callStmt);
					Entity* right = generateEntity(itr->second);
					ModifyRelationship* rel = new ModifyRelationship(left, right);
					this->client->storeRelationship(rel);
				}
			}
		}
	}
	
	for (auto itr = this->whileIfCallMap.begin(); itr != this->whileIfCallMap.end(); ++itr) {
		std::string callStmt = itr->first;
		SimpleToken whileIfToken = itr->second;
		for (auto itr2 = usesForCalls.begin(); itr2 != usesForCalls.end(); ++itr2) {
			if (itr2->first == callStmt) {
				Entity* left = generateEntity(whileIfToken);
				Entity* right = generateEntity(itr2->second);
				UsesRelationship* rel = new UsesRelationship(left, right);
				this->client->storeRelationship(rel);
			}
		}
		for (auto itr2 = modsForCalls.begin(); itr2 != modsForCalls.end(); ++itr2) {
			if (itr2->first == callStmt) {
				Entity* left = generateEntity(whileIfToken);
				Entity* right = generateEntity(itr2->second);
				ModifyRelationship* rel = new ModifyRelationship(left, right);
				this->client->storeRelationship(rel);
			}
		}
	}
}

void Extractor::endOfParserHelper(std::string current, std::string called,
	std::multimap<std::string, std::string> callProcedures, std::vector<std::string> alrCalled) {
	if (current != called) {
		StmtStack* calledStack = procedures.find(called)->second;
		CallsTRelationship* callsTRel = new CallsTRelationship(new ProcedureEntity(current), new ProcedureEntity(called));
		this->client->storeRelationship(callsTRel);
		addNestedRelationships(calledStack, current);
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

void Extractor::addNestedRelationships(StmtStack* calledStack, std::string name) {
	std::vector<SimpleToken> stmts = calledStack->stmts;
	std::unordered_set<SimpleToken, SimpleHash> stmtsNested = calledStack->stmtsNested;
	std::unordered_set<SimpleToken, SimpleHash> varUse = calledStack->varUse;
	std::unordered_set<SimpleToken, SimpleHash> varMod = calledStack->varMod;
	Entity* firstEntity = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, name, 0));

	for (int i = 0; i < stmts.size(); i++) {
		SimpleToken second = stmts.at(i);
		Entity* secondEntity = generateEntity(second);
		ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(parentTRel);
	}

	for (SimpleToken stmt : stmtsNested) {
		SimpleToken second = stmt;
		Entity* secondEntity = generateEntity(second);
		ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(parentTRel);
	}

	for (SimpleToken var : varUse) {
		SimpleToken second = var;
		Entity* secondEntity = generateEntity(second);
		UsesRelationship* usesRel = new UsesRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(usesRel);
		usesForCalls.insert(std::pair<std::string, SimpleToken>(name, second));
	}

	for (SimpleToken var : varMod) {
		SimpleToken second = var;
		Entity* secondEntity = generateEntity(second);
		ModifyRelationship* modifyRel = new ModifyRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(modifyRel);
		modsForCalls.insert(std::pair<std::string, SimpleToken>(name, second));
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

