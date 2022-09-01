#include "Extractor.h"
#include "SimpleToken.h"
#include "../../models/Relationship/Relationship.h"

#include <vector>

using namespace std;

Extractor::Extractor() {}

vector<Relationship*> extractRelationship(SimpleToken parentToken) {
	vector<Relationship*> relationships;
	vector<SimpleToken*> children = parentToken.getChildren();

	SimpleToken currentToken = parentToken;

	do {
		TokenType tokenType = currentToken.type;

		if (tokenType == T_PROCEDURE) {
			handleProcedure(relationships);
		} else if (tokenType == T_STMT) {
			handleStatement(relationships);
		} else if (tokenType == T_READ) {
			handleRead(relationships);
		} else if (tokenType == T_PRINT) {
			handlePrint(relationships);
		} else if (tokenType == T_CALL) {
			handleCall(relationships);
		} else if (tokenType == T_WHILE) {
			handleWhile(relationships);
		} else if (tokenType == T_IF) {
			handleIf(relationships);
		} else if (tokenType == T_ASSIGN) {
			handleAssign(relationships);
		} else if (tokenType == T_COND_EXPR) {
			handleCondExpr(relationships);
		} else if (tokenType == T_VARIABLE) {
			handleVariable(relationships);
		} else if (tokenType == T_CONSTANT) {
			handleConstant(relationships);
		} else {
			handleError();
		}

		currentToken = children.

	} while (!children.empty());

	return relationships;
}
