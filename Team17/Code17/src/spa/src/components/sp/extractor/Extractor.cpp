#include "Extractor.h"
#include <iostream>

Extractor::Extractor(SPClient* client) : currentStack(nullptr) {
	this->client = client;
}

void Extractor::extractRead(SimpleToken readToken) {
	ReadEntity* readEntity = new ReadEntity(std::to_string(readToken.statementNumber), readToken.value);
	VariableEntity* varEntity = new VariableEntity(readToken.value);
	this->currentStack->stmts.push_back(readEntity);
	this->currentStack->varMod.insert(varEntity);
	this->currentStack->extractModify(readEntity, varEntity);
	this->currentStack->extractNext(readEntity);
}

void Extractor::extractPrint(SimpleToken printToken) {
	PrintEntity* printEntity = new PrintEntity(std::to_string(printToken.statementNumber), printToken.value);
	VariableEntity* varEntity = new VariableEntity(printToken.value);
	this->currentStack->stmts.push_back(printEntity);
	this->currentStack->varUse.insert(varEntity);
	this->currentStack->extractUses(printEntity, varEntity);
	this->currentStack->extractNext(printEntity);
}

void Extractor::extractAssign(SimpleToken assignToken) {
	AssignEntity* assignEntity = new AssignEntity(std::to_string(assignToken.statementNumber));
	std::vector<SimpleToken> assignTokens = assignToken.getChildren();
	SimpleToken varToken = assignTokens.at(0);
	SimpleToken exprToken = assignTokens.at(1);
	VariableEntity* varEntity = new VariableEntity(varToken.value);
	this->currentStack->stmts.push_back(assignEntity);
	this->currentStack->varMod.insert(varEntity);
	this->currentStack->extractModify(assignEntity, varEntity);
	this->currentStack->extractNext(assignEntity);
	extractExpr(assignEntity, exprToken);
	extractAssignPattern(assignToken);
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
	WhileEntity* whileEntity = new WhileEntity(std::to_string(whileToken.statementNumber));
	this->currentStack->stmts.push_back(whileEntity);
	this->currentStack->extractNext(whileEntity);
	extractExpr(whileEntity, whileToken);
	extractWhilePattern(whileToken);
	this->parentStack.push(currentStack);
	this->currentStack = new WhileStack(whileEntity, this);
}

void Extractor::extractIf(SimpleToken ifToken) {
	IfEntity* ifEntity = new IfEntity(std::to_string(ifToken.statementNumber));
	this->currentStack->stmts.push_back(ifEntity);
	this->currentStack->extractNext(ifEntity);
	extractExpr(ifEntity, ifToken);
	extractIfPattern(ifToken);
	this->parentStack.push(currentStack);
	this->currentStack = new IfStack(ifEntity, this);
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

void Extractor::extractExpr(Entity* entity, SimpleToken exprToken) {
	std::vector<SimpleToken> exprChildren = exprToken.getChildren();
	Entity* left = entity;
	for (int i = 0; i < exprChildren.size(); i++) {
		SimpleToken currentToken = exprChildren.at(i);
		if (currentToken.type == SpTokenType::TVARIABLE) {
			VariableEntity* currentVarEntity = new VariableEntity(currentToken.value);
			this->currentStack->varUse.insert(currentVarEntity);
			this->currentStack->extractUses(left, currentVarEntity);
		}
		if (currentToken.type == SpTokenType::TCONSTANT) {
			ConstantEntity* currentConstEntity = new ConstantEntity(currentToken.value);
			this->client->storeConstant(currentConstEntity);
		}
	}
}

void Extractor::extractCall(SimpleToken callToken) {
	CallEntity* callEntity = new CallEntity(std::to_string(callToken.statementNumber), callToken.value);
	this->currentStack->stmts.push_back(callEntity);
	this->currentStack->callStmts.push_back(callToken);
	this->currentStack->extractNext(callEntity);
}

void Extractor::extractProcedure(SimpleToken procedureToken) {
	ProcedureEntity* procedureEntity = new ProcedureEntity(procedureToken.value);
	this->currentStack = new ProcedureStack(procedureEntity, this);
}

void Extractor::close(int statementNumber) {
	this->currentStack->close(statementNumber);
}

void Extractor::endOfParser(std::multimap<std::string, std::string> callProcedures) {
	for (auto itr = callProcedures.begin(); itr != callProcedures.end(); ++itr) {
		std::string parent = itr->first;
		std::string called = itr->second;
		ProcedureEntity* left = new ProcedureEntity(parent);
		ProcedureEntity* right = new ProcedureEntity(called);
		CallsRelationship* relationship = new CallsRelationship(left, right);
		this->client->storeRelationship(relationship);
	}

	std::vector<std::string> allProcedures;
	for (auto itr = procedures.begin(); itr != procedures.end(); ++itr) {
		allProcedures.push_back(itr->first);
	}

	for (std::string proc : allProcedures) {
		StmtStack* stack = procedures.find(proc)->second;
		std::unordered_set<Entity*, SimpleHash> varUse = stack->varUse;
		std::unordered_set<Entity*, SimpleHash> varMod = stack->varMod;
		for (Entity* use : varUse) {
			usesForCalls.insert(std::pair<std::string, Entity*>(proc, use));
		}
		for (Entity* mod : varMod) {
			modsForCalls.insert(std::pair<std::string, Entity*>(proc, mod));
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
			CallEntity* left = new CallEntity(std::to_string(callStmt.statementNumber), callStmt.value);
			for (auto itr = usesForCalls.begin(); itr != usesForCalls.end(); ++itr) {
				if (itr->first == callStmt.value) {
					Entity* right = itr->second;
					UsesRelationship* rel = new UsesRelationship(left, right);
					this->client->storeRelationship(rel);
				}
			}
			for (auto itr = modsForCalls.begin(); itr != modsForCalls.end(); ++itr) {
				if (itr->first == callStmt.value) {
					Entity* right = itr->second;
					ModifyRelationship* rel = new ModifyRelationship(left, right);
					this->client->storeRelationship(rel);
				}
			}
		}
	}
	
	for (auto itr = this->whileIfCallMap.begin(); itr != this->whileIfCallMap.end(); ++itr) {
		std::string callStmt = itr->first;
		Entity* whileIfToken = itr->second;
		for (auto itr2 = usesForCalls.begin(); itr2 != usesForCalls.end(); ++itr2) {
			if (itr2->first == callStmt) {
				Entity* left = whileIfToken;
				Entity* right = itr2->second;
				UsesRelationship* rel = new UsesRelationship(left, right);
				this->client->storeRelationship(rel);
			}
		}
		for (auto itr2 = modsForCalls.begin(); itr2 != modsForCalls.end(); ++itr2) {
			if (itr2->first == callStmt) {
				Entity* left = whileIfToken;
				Entity* right = itr2->second;
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
	std::vector<Entity*> stmts = calledStack->stmts;
	std::unordered_set<Entity*, SimpleHash> stmtsNested = calledStack->stmtsNested;
	std::unordered_set<Entity*, SimpleHash> varUse = calledStack->varUse;
	std::unordered_set<Entity*, SimpleHash> varMod = calledStack->varMod;
	ProcedureEntity* firstEntity = new ProcedureEntity(name);
	for (Entity* var : varUse) {
		Entity* secondEntity = var;
		UsesRelationship* usesRel = new UsesRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(usesRel);
		usesForCalls.insert(std::pair<std::string, Entity*>(name, secondEntity));
	}
	for (Entity* var : varMod) {
		Entity* secondEntity = var;
		ModifyRelationship* modifyRel = new ModifyRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(modifyRel);
		modsForCalls.insert(std::pair<std::string, Entity*>(name, secondEntity));
	}
}
