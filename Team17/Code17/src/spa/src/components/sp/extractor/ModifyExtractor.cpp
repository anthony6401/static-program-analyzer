#include "ModifyExtractor.h"

std::vector<ModifyRelationship*> ModifyExtractor::extractModify(SimpleToken procOrWhileIfToken) {
	std::vector<ModifyRelationship*> modifyVector;

	std::vector<SimpleToken> children = procOrWhileIfToken.getChildren();
	std::vector<SimpleToken> stmtSeries;
	std::vector<SimpleToken> stmtSeries_1;
	std::vector<SimpleToken> stmtSeries_2;

	if (procOrWhileIfToken.type == SpTokenType::TPROCEDURE) {
		stmtSeries = children;
	}
	if (procOrWhileIfToken.type == SpTokenType::TWHILE) {
		stmtSeries = children.at(1).getChildren();
	}
	if (procOrWhileIfToken.type == SpTokenType::TIF) {
		stmtSeries_1 = children.at(1).getChildren();
		stmtSeries_2 = children.at(2).getChildren();
	}

	std::vector<ModifyRelationship*> moreModifyVector = getModifyRelationships(stmtSeries);
	std::vector<ModifyRelationship*> moreModifyVector_1 = getModifyRelationships(stmtSeries_1);
	std::vector<ModifyRelationship*> moreModifyVector_2 = getModifyRelationships(stmtSeries_2);
	modifyVector.insert(modifyVector.end(), moreModifyVector.begin(), moreModifyVector.end());
	modifyVector.insert(modifyVector.end(), moreModifyVector_1.begin(), moreModifyVector_1.end());
	modifyVector.insert(modifyVector.end(), moreModifyVector_2.begin(), moreModifyVector_2.end());

	return modifyVector;
}

std::vector<ModifyRelationship*> ModifyExtractor::getModifyRelationships(std::vector<SimpleToken> stmtSeries) {
	std::vector<ModifyRelationship*> modifyVector;

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
			std::vector<ModifyRelationship*> moreModifyVector = ModifyExtractor::extractModify(current);
			modifyVector.insert(modifyVector.end(), moreModifyVector.begin(), moreModifyVector.end());
		}
		if (current.type == SpTokenType::TIF) {
			std::vector<ModifyRelationship*> moreModifyVector = ModifyExtractor::extractModify(current);
			modifyVector.insert(modifyVector.end(), moreModifyVector.begin(), moreModifyVector.end());
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
