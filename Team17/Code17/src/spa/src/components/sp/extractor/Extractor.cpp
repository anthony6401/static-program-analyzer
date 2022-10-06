#include "Extractor.h"

#include <iostream>

Extractor::Extractor(SPClient* client) : currentStack(nullptr) {
	this->client = client;
}

void Extractor::extractRead(SimpleToken readToken) {
	//std::cout << "extractRead\n";
	this->currentStack->follows.push_back(readToken);
	this->currentStack->modifies.push_back(readToken);

	Entity* left = generateEntity(readToken);
	Entity* right = generateEntity(SimpleToken(SpTokenType::TVARIABLE, readToken.value, 0));
	ModifyRelationship* relationship = new ModifyRelationship(left, right);
	this->client->storeRelationship(relationship);
}

void Extractor::extractPrint(SimpleToken printToken) {
	//std::cout << "extractPrint\n";
	this->currentStack->follows.push_back(printToken);
	this->currentStack->uses.push_back(printToken);

	Entity* left = generateEntity(printToken);
	Entity* right = generateEntity(SimpleToken(SpTokenType::TVARIABLE, printToken.value, 0));
	UsesRelationship* relationship = new UsesRelationship(left, right);
	this->client->storeRelationship(relationship);
}

void Extractor::extractAssign(SimpleToken assignToken) {
	//std::cout << "extractAssign\n";
	this->currentStack->follows.push_back(assignToken);
	SimpleToken varToken = assignToken.getChildren().at(0);
	this->currentStack->modifies.push_back(varToken);

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
	//std::cout << "extractWhile\n";
	this->currentStack->follows.push_back(whileToken);
	extractExpr(whileToken, whileToken);
	this->parentStack.push(currentStack);
	this->currentStack = new WhileStack(whileToken, this);
}

void Extractor::extractIf(SimpleToken ifToken) {
	//std::cout << "extractIf\n";
	this->currentStack->follows.push_back(ifToken);
	extractExpr(ifToken, ifToken);
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
		if (currentToken.type == SpTokenType::TCONSTANT) {
			this->client->storeConstant(new ConstantEntity(currentToken.value));
		}
	}
}

void Extractor::extractCall(SimpleToken callToken, std::string currentProcedure) {
	//std::cout << "extractCall\n";
	this->currentStack->follows.push_back(callToken);

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
	//std::cout << "addNestedRels\n";
	std::vector<SimpleToken> follows = calledStack->follows;
	std::vector<SimpleToken> parentT = calledStack->parentT;
	std::vector<SimpleToken> uses = calledStack->uses;
	std::vector<SimpleToken> modifies = calledStack->modifies;

	for (int i = 0; i < follows.size(); i++) {
		SimpleToken second = follows.at(i);
		Entity* firstEntity = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, name, 0));
		Entity* secondEntity = generateEntity(second);
		ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(parentTRel);
	}

	for (int i = 0; i < parentT.size(); i++) {
		SimpleToken second = parentT.at(i);
		Entity* firstEntity = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, name, 0));
		Entity* secondEntity = generateEntity(second);
		ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(parentTRel);
	}

	for (int i = 0; i < uses.size(); i++) {
		SimpleToken second = uses.at(i);
		Entity* firstEntity = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, name, 0));
		Entity* secondEntity = generateEntity(second);
		UsesRelationship* usesRel = new UsesRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(usesRel);
	}

	for (int i = 0; i < modifies.size(); i++) {
		SimpleToken second = modifies.at(i);
		Entity* firstEntity = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, name, 0));
		Entity* secondEntity = generateEntity(second);
		ModifyRelationship* modifyRel = new ModifyRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(modifyRel);
	}
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
