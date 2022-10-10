#include "Extractor.h"

#include <iostream>

Extractor::Extractor(SPClient* client) : currentStack(nullptr) {
	this->client = client;
}

void Extractor::extractRead(SimpleToken readToken) {
	this->currentStack->stmts.push_back(readToken);
	this->currentStack->varMod.push_back(readToken);

	Entity* left = generateEntity(readToken);
	Entity* right = generateEntity(SimpleToken(SpTokenType::TVARIABLE, readToken.value, 0));
	ModifyRelationship* relationship = new ModifyRelationship(left, right);
	this->client->storeRelationship(relationship);
}

void Extractor::extractPrint(SimpleToken printToken) {
	this->currentStack->stmts.push_back(printToken);
	this->currentStack->varUse.push_back(printToken);

	Entity* left = generateEntity(printToken);
	Entity* right = generateEntity(SimpleToken(SpTokenType::TVARIABLE, printToken.value, 0));
	UsesRelationship* relationship = new UsesRelationship(left, right);
	this->client->storeRelationship(relationship);
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

	std::string lineNum = std::to_string(assignToken.statementNumber);
	std::string firstVal = varToken.value;
	std::string seconVal = getExpressionAsString(exprToken);
	AssignPattern * assignPattern = new AssignPattern(lineNum, firstVal, seconVal);
	this->client->storePattern(assignPattern);
}

std::string Extractor::getExpressionAsString(SimpleToken expression) {
	std::string expressionString;
	std::vector<SimpleToken> expressionChildren = expression.getChildren();
	for (int i = 0; i < expressionChildren.size(); i++) {
		std::string nextString = expressionChildren.at(i).value;
		expressionString = expressionString + nextString;
	}
	return expressionString;
}

void Extractor::extractWhile(SimpleToken whileToken) {
	this->currentStack->stmts.push_back(whileToken);
	extractExpr(whileToken, whileToken);
	this->parentStack.push(currentStack);
	this->currentStack = new WhileStack(whileToken, this);
}

void Extractor::extractIf(SimpleToken ifToken) {
	this->currentStack->stmts.push_back(ifToken);
	extractExpr(ifToken, ifToken);
	this->parentStack.push(currentStack);
	this->currentStack = new IfStack(ifToken, this);
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

	Entity* left = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, currentProcedure, 0));
	Entity* right = new ProcedureEntity(callToken.value);
	CallsRelationship* relationship = new CallsRelationship(left, right);
	this->client->storeRelationship(relationship);


}

void Extractor::extractProcedure(SimpleToken procedureToken) {
	this->currentStack = new ProcedureStack(procedureToken, this);
}

void Extractor::close(int statementNumber) {
	currentStack->close(statementNumber);
}

void Extractor::endOfParser(std::multimap<std::string, std::string> callProcedures) {
	for (auto itr = callProcedures.begin(); itr != callProcedures.end(); ++itr) {
		std::string parent = itr->first;
		std::string called = itr->second;
		if (procedures.find(parent) != procedures.end() && procedures.find(called) != procedures.end()) {
			StmtStack* parentStack = procedures.find(parent)->second;
			StmtStack* calledStack = procedures.find(called)->second;
			CallsTRelationship* callsTRel = new CallsTRelationship(new ProcedureEntity(parent), new ProcedureEntity(called));
			this->client->storeRelationship(callsTRel);
			addNestedRelationships(parentStack, calledStack, parent);
		}
		for (auto itrRec = callProcedures.begin(); itrRec != callProcedures.end(); ++itrRec) {
			std::string calledRecurse = itrRec->second;
			if (calledRecurse != called && parent != calledRecurse) {
				StmtStack* parentStack = procedures.find(parent)->second;
				StmtStack* calledStackRecurse = procedures.find(calledRecurse)->second;
				CallsTRelationship* callsTRel = new CallsTRelationship(new ProcedureEntity(parent), new ProcedureEntity(calledRecurse));
				this->client->storeRelationship(callsTRel);
				addNestedRelationships(parentStack, calledStackRecurse, parent);
			}
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

Entity* Extractor::generateEntity(SimpleToken token) {
	if (token.type == SpTokenType::TREAD) {
		return new ReadEntity(std::to_string(token.statementNumber), token.value);
	}
	if (token.type == SpTokenType::TPRINT) {
		return new PrintEntity(std::to_string(token.statementNumber), token.value;
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
