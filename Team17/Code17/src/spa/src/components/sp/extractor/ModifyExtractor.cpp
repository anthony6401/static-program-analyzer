#include "ModifyExtractor.h"

std::vector<ModifyRelationship*> ModifyExtractor::extractModify(SimpleToken procOrStmtLstToken) {
	std::vector<ModifyRelationship*> modifyVector;

	std::vector<SimpleToken> stmtSeries = procOrStmtLstToken.getChildren();

	for (int i = 0; i < stmtSeries.size(); i++) {
		SimpleToken current = stmtSeries.at(i);
		if (current.type == SpTokenType::TREAD) {
			SimpleToken readVar = current.getChildren().at(0);
			Entity* readEntity = generateEntity(current);
			Entity* varEntity = generateEntity(readVar);
			ModifyRelationship* modify = new ModifyRelationship(readEntity, varEntity);
			modifyVector.push_back(modify);
		}
		if (current.type == SpTokenType::TPRINT) {
			// Do nothing
		}
		if (current.type == SpTokenType::TASSIGN) {
			SimpleToken assignVar = current.getChildren().at(0);
			Entity* assignEntity = generateEntity(current);
			Entity* varEntity = generateEntity(assignVar);
			ModifyRelationship* modify = new ModifyRelationship(assignEntity, varEntity);
			modifyVector.push_back(modify);
		}
		if (current.type == SpTokenType::TWHILE) {
			SimpleToken stmtLst = current.getChildren().at(1);
			std::vector<ModifyRelationship*> moreModifyVector = ModifyExtractor::extractModify(stmtLst);
			modifyVector.insert(modifyVector.end(), moreModifyVector.begin(), moreModifyVector.end());
		}
		if (current.type == SpTokenType::TIF) {
			SimpleToken stmtLst_1 = current.getChildren().at(1);
			SimpleToken stmtLst_2 = current.getChildren().at(2);
			std::vector<ModifyRelationship*> moreModifyVector_1 = ModifyExtractor::extractModify(stmtLst_1);
			std::vector<ModifyRelationship*> moreModifyVector_2 = ModifyExtractor::extractModify(stmtLst_2);
			modifyVector.insert(modifyVector.end(), moreModifyVector_1.begin(), moreModifyVector_1.end());
			modifyVector.insert(modifyVector.end(), moreModifyVector_2.begin(), moreModifyVector_2.end());
		}
	}

	return modifyVector;
}

Entity* ModifyExtractor::generateEntity(SimpleToken token) {
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
	//if (token.type == SpTokenType::TCALL) {
	//	return new CallEntity(std::to_string(token.statementNumber));
	//}
	return new Entity(std::to_string(token.statementNumber)); // Should not happen
}
