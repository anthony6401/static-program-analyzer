#include "ModifyExtractor.h"

std::vector<ModifyRelationship*> ModifyExtractor::extractModify(SimpleToken procOrWhileIfToken) {
	std::vector<ModifyRelationship*> modifyVector;

	std::vector<SimpleToken> children = procOrWhileIfToken.getChildren();
	std::vector<SimpleToken> stmtSeries;
	std::vector<SimpleToken> stmtSeries_1;
	std::vector<SimpleToken> stmtSeries_2;

	if (procOrWhileIfToken.type == SpTokenType::TPROCEDURE) {
		stmtSeries = children;
		std::vector<ModifyRelationship*> modifyVectorProc = getModifyRelationshipsProc(procOrWhileIfToken, stmtSeries);
		modifyVector.insert(modifyVector.end(), modifyVectorProc.begin(), modifyVectorProc.end());
	}
	if (procOrWhileIfToken.type == SpTokenType::TWHILE) {
		stmtSeries = children.at(1).getChildren();
		std::vector<ModifyRelationship*> modifyVectorProc = getModifyRelationshipsProc(procOrWhileIfToken, stmtSeries);
		modifyVector.insert(modifyVector.end(), modifyVectorProc.begin(), modifyVectorProc.end());
	}
	if (procOrWhileIfToken.type == SpTokenType::TIF) {
		stmtSeries_1 = children.at(1).getChildren();
		stmtSeries_2 = children.at(2).getChildren();
		std::vector<ModifyRelationship*> modifyVectorProc_1 = getModifyRelationshipsProc(procOrWhileIfToken, stmtSeries_1);
		modifyVector.insert(modifyVector.end(), modifyVectorProc_1.begin(), modifyVectorProc_1.end());
		std::vector<ModifyRelationship*> modifyVectorProc_2 = getModifyRelationshipsProc(procOrWhileIfToken, stmtSeries_2);
		modifyVector.insert(modifyVector.end(), modifyVectorProc_2.begin(), modifyVectorProc_2.end());
	}

	std::vector<ModifyRelationship*> moreModifyVector = getModifyRelationships(procOrWhileIfToken, stmtSeries);
	std::vector<ModifyRelationship*> moreModifyVector_1 = getModifyRelationships(procOrWhileIfToken, stmtSeries_1);
	std::vector<ModifyRelationship*> moreModifyVector_2 = getModifyRelationships(procOrWhileIfToken, stmtSeries_2);
	modifyVector.insert(modifyVector.end(), moreModifyVector.begin(), moreModifyVector.end());
	modifyVector.insert(modifyVector.end(), moreModifyVector_1.begin(), moreModifyVector_1.end());
	modifyVector.insert(modifyVector.end(), moreModifyVector_2.begin(), moreModifyVector_2.end());

	return modifyVector;
}

std::vector<ModifyRelationship*> ModifyExtractor::getModifyRelationshipsProc(SimpleToken procToken, std::vector<SimpleToken> stmtSeries) {
	std::vector<ModifyRelationship*> modifyVector;

	for (int i = 0; i < stmtSeries.size(); i++) {
		SimpleToken current = stmtSeries.at(i);
		if (current.type == SpTokenType::TREAD) {
			SimpleToken readVar = current.getChildren().at(0);
			Entity* procEntity = generateEntity(procToken);
			Entity* varEntity1 = generateEntity(readVar);
			ModifyRelationship* modify1 = new ModifyRelationship(procEntity, varEntity1);
			modifyVector.push_back(modify1);
		}
		if (current.type == SpTokenType::TPRINT) {
			// Do nothing
		}
		if (current.type == SpTokenType::TASSIGN) {
			SimpleToken assignVar = current.getChildren().at(0);
			Entity* procEntity = generateEntity(procToken);
			Entity* varEntity1 = generateEntity(assignVar);
			ModifyRelationship* modify1 = new ModifyRelationship(procEntity, varEntity1);
			modifyVector.push_back(modify1);
		}
		if (current.type == SpTokenType::TWHILE) {
			std::vector<SimpleToken> stmtSeriesWhile = current.getChildren().at(1).getChildren();

			std::vector<ModifyRelationship*> moreModifyVector = ModifyExtractor::getModifyRelationshipsProc(procToken, stmtSeriesWhile);
			modifyVector.insert(modifyVector.end(), moreModifyVector.begin(), moreModifyVector.end());
		}
		if (current.type == SpTokenType::TIF) {
			std::vector<SimpleToken> stmtSeriesIf_1 = current.getChildren().at(1).getChildren();
			std::vector<SimpleToken> stmtSeriesIf_2 = current.getChildren().at(2).getChildren();

			std::vector<ModifyRelationship*> moreModifyVector_1 = ModifyExtractor::getModifyRelationshipsProc(procToken, stmtSeriesIf_1);
			std::vector<ModifyRelationship*> moreModifyVector_2 = ModifyExtractor::getModifyRelationshipsProc(procToken, stmtSeriesIf_2);
			modifyVector.insert(modifyVector.end(), moreModifyVector_1.begin(), moreModifyVector_1.end());
			modifyVector.insert(modifyVector.end(), moreModifyVector_2.begin(), moreModifyVector_2.end());
		}
	}

	return modifyVector;
}

std::vector<ModifyRelationship*> ModifyExtractor::getModifyRelationships(SimpleToken procOrWhileIfToken, std::vector<SimpleToken> stmtSeries) {
	std::vector<ModifyRelationship*> modifyVector;

		for (int i = 0; i < stmtSeries.size(); i++) {
			SimpleToken current = stmtSeries.at(i);
			if (current.type == SpTokenType::TREAD) {
				SimpleToken readVar = current.getChildren().at(0);
				Entity* readEntity = generateEntity(current);
				Entity* varEntity = generateEntity(readVar);
				ModifyRelationship* modify = new ModifyRelationship(readEntity, varEntity);
				modifyVector.push_back(modify);
				//Entity* procEntity = generateEntity(procOrWhileIfToken);
				//Entity* varEntity1 = generateEntity(readVar);
				//ModifyRelationship* modify1 = new ModifyRelationship(procEntity, varEntity1);
				//modifyVector.push_back(modify1);
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
				//Entity* procEntity = generateEntity(procOrWhileIfToken);
				//Entity* varEntity1 = generateEntity(assignVar);
				//ModifyRelationship* modify1 = new ModifyRelationship(procEntity, varEntity1);
				//modifyVector.push_back(modify1);
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
	if (token.type == SpTokenType::TVARIABLE) {
		return new VariableEntity(token.value);
	}
	if (token.type == SpTokenType::TCONSTANT) {
		return new ConstantEntity(token.value);
	}
	if (token.type == SpTokenType::TPROCEDURE) {
		return new ProcedureEntity(token.value);
	}
	//if (token.type == SpTokenType::TCALL) {
	//	return new CallEntity(std::to_string(token.statementNumber));
	//}
	return new Entity(std::to_string(token.statementNumber)); // Should not happen
}
