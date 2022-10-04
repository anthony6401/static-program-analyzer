#include "Extractor.h"

#include <iostream>

Extractor::Extractor(SPClient* client) {
	this->client = client;
	currentStack = new ProcedureStack(SimpleToken(), this);
}

void Extractor::extractRead(SimpleToken readToken) {
	std::cout << "extractRead\n";
	this->currentStack->addFollows(readToken);
	this->currentStack->modifies.push_back(readToken);

	Entity* left = generateEntity(readToken);
	Entity* right = generateEntity(SimpleToken(SpTokenType::TVARIABLE, readToken.value, 0));
	ModifyRelationship* relationship = new ModifyRelationship(left, right);
	this->client->storeRelationship(relationship);
	std::cout << "extractRead OK\n";
}

void Extractor::extractPrint(SimpleToken printToken) {
	std::cout << "extractPrint\n";
	this->currentStack->addFollows(printToken);
	this->currentStack->uses.push_back(printToken);

	Entity* left = generateEntity(printToken);
	Entity* right = generateEntity(SimpleToken(SpTokenType::TVARIABLE, printToken.value, 0));
	UsesRelationship* relationship = new UsesRelationship(left, right);
	this->client->storeRelationship(relationship);
	std::cout << "extractPrint OK\n";
}

void Extractor::extractAssign(SimpleToken assignToken) {
	std::cout << "extractAssign\n";
	this->currentStack->addFollows(assignToken);
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
	std::cout << "extractAssign OK\n";
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
	std::cout << "extractWhile\n";
	this->currentStack->addFollows(whileToken);
	extractExpr(whileToken, whileToken);

	// create new while stack and set it as the current stack, old stack gets added to parentStack
	this->parentStack.push(currentStack);
	this->currentStack = new WhileStack(whileToken, this);
	std::cout << "extractWhile OK\n";
}

void Extractor::extractIf(SimpleToken ifToken) {
	std::cout << "extractIf\n";
	this->currentStack->addFollows(ifToken);
	extractExpr(ifToken, ifToken);

	// create new if stack and set it as the current stack, old stack gets added to parentStack
	this->parentStack.push(currentStack);
	this->currentStack = new IfStack(ifToken, this);
	std::cout << "extractIf OK\n";
}

void Extractor::extractExpr(SimpleToken stmtToken, SimpleToken exprToken) {
	std::cout << "extractExpr\n";
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
	std::cout << "extractExpr OK\n";
}

void Extractor::extractCall(SimpleToken callToken) {
	std::cout << "extractCall\n";
	this->currentStack->addFollows(callToken);

	Entity* left = generateEntity(SimpleToken(SpTokenType::TPROCEDURE, this->currentProcedure, 0));
	Entity* right = generateEntity(SimpleToken(SpTokenType::TCALL, callToken.value, 0));
	CallsRelationship* relationship = new CallsRelationship(left, right);
	this->client->storeRelationship(relationship);

	this->callProcedures.insert(std::pair<std::string, std::string>(this->currentStack->parent.value, callToken.value));
	std::cout << "extractCall OK\n";
}

void Extractor::extractProcedure(SimpleToken procedureToken) {
	std::cout << "extractProcedure\n";
	this->currentStack = new ProcedureStack(procedureToken, this);
	this->currentProcedure = procedureToken.value;
	std::cout << "extractProcedure OK\n";
}

void Extractor::close(int statementNumber) {
	std::cout << "close\n";
	currentStack->close(statementNumber);
	std::cout << "close OK\n";
}

void Extractor::endOfParser() {
	std::cout << "endOfParser\n";
	for (auto itr = callProcedures.begin(); itr != callProcedures.end(); ++itr) {
		std::cout << "for loop begin\n";

		std::string parent = itr->first;
		std::string called = itr->second;

		std::cout << "for loop middle\n";

		if (procedures.find(parent) != procedures.end() && procedures.find(called) != procedures.end()) {
			StmtStack* parentStack = procedures.find(parent)->second;
			StmtStack* calledStack = procedures.find(called)->second;
			addNestedRelationships(parentStack, calledStack);
		}

		std::cout << "for loop end OK\n";
	}
	std::cout << "endOfParser OK\n";
}

void Extractor::addNestedRelationships(StmtStack* parentStack, StmtStack* calledStack) {
	std::cout << "addNestedRels\n";
	std::vector<SimpleToken> follows = calledStack->follows;
	std::vector<SimpleToken> uses = calledStack->uses;
	std::vector<SimpleToken> modifies = calledStack->modifies;

	for (int i = 0; i < follows.size(); i++) {
		SimpleToken second = follows.at(i);
		Entity* firstEntity = generateEntity(parentStack->parent);
		Entity* secondEntity = generateEntity(second);
		ParentTRelationship* parentTRel = new ParentTRelationship(firstEntity, firstEntity);
		this->client->storeRelationship(parentTRel);
	}

	for (int i = 0; i < uses.size(); i++) {
		SimpleToken second = uses.at(i);
		Entity* firstEntity = generateEntity(parentStack->parent);
		Entity* secondEntity = generateEntity(second);
		UsesRelationship* usesRel = new UsesRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(usesRel);
	}

	for (int i = 0; i < modifies.size(); i++) {
		SimpleToken second = modifies.at(i);
		Entity* firstEntity = generateEntity(parentStack->parent);
		Entity* secondEntity = generateEntity(second);
		ModifyRelationship* modifyRel = new ModifyRelationship(firstEntity, secondEntity);
		this->client->storeRelationship(modifyRel);
	}
	std::cout << "addNestedRels OK\n";
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
