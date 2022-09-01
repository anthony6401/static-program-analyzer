#include "Extractor.h"

Extractor::Extractor() {}

vector<Relationship*> Extractor::extractRelationships(SimpleToken parentToken) {
	vector<Relationship*> relationships;
	vector<SimpleToken*> children = parentToken.getChildren();

	SimpleToken currentToken = parentToken;

	do {
		TokenType tokenType = currentToken.type;

		if (tokenType == TokenType::TPROCEDURE) {
			handleProcedure(relationships);
		} else if (tokenType == TokenType::TSTMT) {
			handleStatement(relationships);
		} else if (tokenType == TokenType::TREAD) {
			handleRead(relationships);
		} else if (tokenType == TokenType::TPRINT) {
			handlePrint(relationships);
		} else if (tokenType == TokenType::TCALL) {
			handleCall(relationships);
		} else if (tokenType == TokenType::TWHILE) {
			handleWhile(relationships);
		} else if (tokenType == TokenType::TIF) {
			handleIf(relationships);
		} else if (tokenType == TokenType::TASSIGN) {
			handleAssign(relationships);
		} else if (tokenType == TokenType::TCONDEXPR) {
			handleCondExpr(relationships);
		} else if (tokenType == TokenType::TVARIABLE) {
			handleVariable(relationships);
		} else if (tokenType == TokenType::TCONSTANT) {
			handleConstant(relationships);
		} else if (tokenType == TokenType::TCLOSE) {
			handleClose(relationships);
		} else if (tokenType == TokenType::TOPR) {
			handleOpr(relationships);
		} else {
			handleError();
		}

		currentToken = *children.front();
		children.erase(children.begin());

	} while (!children.empty());

	return relationships;
}

void handleProcedure(vector<Relationship*> relationships) {}
void handleStatement(vector<Relationship*> relationships) {}
void handleRead(vector<Relationship*> relationships) {}
void handlePrint(vector<Relationship*> relationships) {}
void handleCall(vector<Relationship*> relationships) {}
void handleWhile(vector<Relationship*> relationships) {}
void handleIf(vector<Relationship*> relationships) {}
void handleAssign(vector<Relationship*> relationships) {}
void handleCondExpr(vector<Relationship*> relationships) {}
void handleVariable(vector<Relationship*> relationships) {}
void handleConstant(vector<Relationship*> relationships) {}
void handleClose(vector<Relationship*> relationships) {}
void handleOpr(vector<Relationship*> relationships) {}
void handleError() {}
