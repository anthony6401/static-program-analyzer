#include "ParentExtractor.h"

std::vector<ParentRelationship*> ParentExtractor::extractParent(SimpleToken procOrWhileIfToken) {
	std::vector<ParentRelationship*> parentVector;

	std::vector<SimpleToken> stmtSeries = procOrWhileIfToken.getChildren();

	if (procOrWhileIfToken.type == SpTokenType::TPROCEDURE) {
		for (int i = 0; i < stmtSeries.size(); i++) {
			SimpleToken childToken = stmtSeries.at(i);
			Entity* parentEntity = generateEntity(procOrWhileIfToken);
			Entity* childEntity = generateEntity(childToken);
			ParentRelationship* parent = new ParentRelationship(parentEntity, childEntity);
			parentVector.push_back(parent);
		}
	}
	
	if (procOrWhileIfToken.type == SpTokenType::TWHILE) {
		SimpleToken stmtLstToken = stmtSeries.at(1);
		std::vector<SimpleToken> stmtSeriesForStmtLst = stmtLstToken.getChildren();
		for (int i = 0; i < stmtSeriesForStmtLst.size(); i++) {
			SimpleToken childToken = stmtSeriesForStmtLst.at(i);
			Entity* parentEntity = generateEntity(procOrWhileIfToken);
			Entity* childEntity = generateEntity(childToken);
			ParentRelationship* parent = new ParentRelationship(parentEntity, childEntity);
			parentVector.push_back(parent);
		}
	}

	if (procOrWhileIfToken.type == SpTokenType::TIF) {
		SimpleToken stmtLstToken_1 = stmtSeries.at(1);
		SimpleToken stmtLstToken_2 = stmtSeries.at(2);
		std::vector<SimpleToken> stmtSeriesInStmtLst_1 = stmtLstToken_1.getChildren();
		std::vector<SimpleToken> stmtSeriesInStmtLst_2 = stmtLstToken_1.getChildren();
		for (int i = 0; i < stmtSeriesInStmtLst_1.size(); i++) {
			SimpleToken childToken = stmtSeriesInStmtLst_1.at(i);
			Entity* parentEntity = generateEntity(procOrWhileIfToken);
			Entity* childEntity = generateEntity(childToken);
			ParentRelationship* parent = new ParentRelationship(parentEntity, childEntity);
			parentVector.push_back(parent);
		}
		for (int i = 0; i < stmtSeriesInStmtLst_2.size(); i++) {
			SimpleToken childToken = stmtSeriesInStmtLst_2.at(i);
			Entity* parentEntity = generateEntity(procOrWhileIfToken);
			Entity* childEntity = generateEntity(childToken);
			ParentRelationship* parent = new ParentRelationship(parentEntity, childEntity);
			parentVector.push_back(parent);
		}
	}

	for (int i = 0; i < stmtSeries.size(); i++) {
		SimpleToken current = stmtSeries.at(i);
		if (current.type == SpTokenType::TWHILE || current.type == SpTokenType::TIF || current.type == SpTokenType::TSTMTLIST) {
			std::vector<ParentRelationship*> moreParentVector = ParentExtractor::extractParent(current);
			parentVector.insert(parentVector.end(), moreParentVector.begin(), moreParentVector.end());
		}
	}

	return parentVector;
}

std::vector<ParentTRelationship*> ParentExtractor::extractParentT(SimpleToken procOrWhileIfToken) {
	std::vector<ParentTRelationship*> parentTVector;
	
	std::vector<SimpleToken> stmtSeries = procOrWhileIfToken.getChildren();

	if (procOrWhileIfToken.type == SpTokenType::TPROCEDURE) {
		for (int i = 0; i < stmtSeries.size(); i++) {
			SimpleToken childToken = stmtSeries.at(i);
			Entity* parentEntity = generateEntity(procOrWhileIfToken);
			Entity* childEntity = generateEntity(childToken);
			ParentTRelationship* parent = new ParentTRelationship(parentEntity, childEntity);
			parentTVector.push_back(parent);
		}
		for (int i = 0; i < stmtSeries.size(); i++) {
			SimpleToken childToken = stmtSeries.at(i);
			if (childToken.type == SpTokenType::TWHILE || childToken.type == SpTokenType::TIF) {
				std::vector<ParentTRelationship*> nestedParentTVector = getNestedParentT(procOrWhileIfToken, childToken);
				parentTVector.insert(parentTVector.end(), nestedParentTVector.begin(), nestedParentTVector.end());
			}
		}
	}

	if (procOrWhileIfToken.type == SpTokenType::TWHILE) {
		SimpleToken stmtLstToken = stmtSeries.at(1);
		std::vector<SimpleToken> stmtSeriesInStmtLst = stmtLstToken.getChildren();
		for (int i = 0; i < stmtSeriesInStmtLst.size(); i++) {
			SimpleToken childToken = stmtSeriesInStmtLst.at(i);
			Entity* parentEntity = generateEntity(procOrWhileIfToken);
			Entity* childEntity = generateEntity(childToken);
			ParentTRelationship* parent = new ParentTRelationship(parentEntity, childEntity);
			parentTVector.push_back(parent);
		}
		for (int i = 0; i < stmtSeriesInStmtLst.size(); i++) {
			SimpleToken childToken = stmtSeriesInStmtLst.at(i);
			if (childToken.type == SpTokenType::TWHILE || childToken.type == SpTokenType::TIF) {
				std::vector<ParentTRelationship*> nestedParentTVector = getNestedParentT(procOrWhileIfToken, childToken);
				parentTVector.insert(parentTVector.end(), nestedParentTVector.begin(), nestedParentTVector.end());
			}
		}
	}

	if (procOrWhileIfToken.type == SpTokenType::TIF) {
		SimpleToken stmtLstToken_1 = stmtSeries.at(1);
		SimpleToken stmtLstToken_2 = stmtSeries.at(2);
		std::vector<SimpleToken> stmtSeriesInStmtLst_1 = stmtLstToken_1.getChildren();
		std::vector<SimpleToken> stmtSeriesInStmtLst_2 = stmtLstToken_1.getChildren();
		for (int i = 0; i < stmtSeriesInStmtLst_1.size(); i++) {
			SimpleToken childToken = stmtSeriesInStmtLst_1.at(i);
			Entity* parentEntity = generateEntity(procOrWhileIfToken);
			Entity* childEntity = generateEntity(childToken);
			ParentTRelationship* parent = new ParentTRelationship(parentEntity, childEntity);
			parentTVector.push_back(parent);
		}
		for (int i = 0; i < stmtSeriesInStmtLst_2.size(); i++) {
			SimpleToken childToken = stmtSeriesInStmtLst_2.at(i);
			Entity* parentEntity = generateEntity(procOrWhileIfToken);
			Entity* childEntity = generateEntity(childToken);
			ParentTRelationship* parent = new ParentTRelationship(parentEntity, childEntity);
			parentTVector.push_back(parent);
		}
		for (int i = 0; i < stmtSeriesInStmtLst_1.size(); i++) {
			SimpleToken childToken = stmtSeriesInStmtLst_1.at(i);
			if (childToken.type == SpTokenType::TWHILE || childToken.type == SpTokenType::TIF) {
				std::vector<ParentTRelationship*> nestedParentTVector = getNestedParentT(procOrWhileIfToken, childToken);
				parentTVector.insert(parentTVector.end(), nestedParentTVector.begin(), nestedParentTVector.end());
			}
		}
		for (int i = 0; i < stmtSeriesInStmtLst_2.size(); i++) {
			SimpleToken childToken = stmtSeriesInStmtLst_2.at(i);
			if (childToken.type == SpTokenType::TWHILE || childToken.type == SpTokenType::TIF) {
				std::vector<ParentTRelationship*> nestedParentTVector = getNestedParentT(procOrWhileIfToken, childToken);
				parentTVector.insert(parentTVector.end(), nestedParentTVector.begin(), nestedParentTVector.end());
			}
		}
	}

	for (int i = 0; i < stmtSeries.size(); i++) {
		SimpleToken current = stmtSeries.at(i);
		if (current.type == SpTokenType::TWHILE || current.type == SpTokenType::TIF || current.type == SpTokenType::TSTMTLIST) {
			std::vector<ParentTRelationship*> moreParentTVector = ParentExtractor::extractParentT(current);
			parentTVector.insert(parentTVector.end(), moreParentTVector.begin(), moreParentTVector.end());
		}
	}

	return parentTVector;
}

std::vector<ParentTRelationship*> ParentExtractor::getNestedParentT(SimpleToken procOrWhileIfToken, SimpleToken whileOrIfToken) {
	std::vector<ParentTRelationship*> parentTVector;

	if (whileOrIfToken.type == SpTokenType::TWHILE) {
		SimpleToken stmtLstToken = whileOrIfToken.getChildren().at(1);
		std::vector<SimpleToken> stmtSeriesInStmtLst = stmtLstToken.getChildren();
		for (int i = 0; i < stmtSeriesInStmtLst.size(); i++) {
			SimpleToken childToken = stmtSeriesInStmtLst.at(i);
			Entity* parentEntity = generateEntity(procOrWhileIfToken);
			Entity* childEntity = generateEntity(childToken);
			ParentTRelationship* parent = new ParentTRelationship(parentEntity, childEntity);
			parentTVector.push_back(parent);
		}
		for (int i = 0; i < stmtSeriesInStmtLst.size(); i++) {
			SimpleToken current = stmtSeriesInStmtLst.at(i);
			if (current.type == SpTokenType::TWHILE || current.type == SpTokenType::TIF) {
				std::vector<ParentTRelationship*> moreParentTVector = ParentExtractor::getNestedParentT(procOrWhileIfToken, current);
				parentTVector.insert(parentTVector.end(), moreParentTVector.begin(), moreParentTVector.end());
			}
		}
	}

	if (whileOrIfToken.type == SpTokenType::TIF) {
		SimpleToken stmtLstToken_1 = whileOrIfToken.getChildren().at(1);
		SimpleToken stmtLstToken_2 = whileOrIfToken.getChildren().at(2);
		std::vector<SimpleToken> stmtSeriesInStmtLst_1 = stmtLstToken_1.getChildren();
		std::vector<SimpleToken> stmtSeriesInStmtLst_2 = stmtLstToken_2.getChildren();
		for (int i = 0; i < stmtSeriesInStmtLst_1.size(); i++) {
			SimpleToken childToken = stmtSeriesInStmtLst_1.at(i);
			Entity* parentEntity = generateEntity(procOrWhileIfToken);
			Entity* childEntity = generateEntity(childToken);
			ParentTRelationship* parent = new ParentTRelationship(parentEntity, childEntity);
			parentTVector.push_back(parent);
		}
		for (int i = 0; i < stmtSeriesInStmtLst_2.size(); i++) {
			SimpleToken childToken = stmtSeriesInStmtLst_2.at(i);
			Entity* parentEntity = generateEntity(procOrWhileIfToken);
			Entity* childEntity = generateEntity(childToken);
			ParentTRelationship* parent = new ParentTRelationship(parentEntity, childEntity);
			parentTVector.push_back(parent);
		}
		for (int i = 0; i < stmtSeriesInStmtLst_1.size(); i++) {
			SimpleToken current = stmtSeriesInStmtLst_1.at(i);
			if (current.type == SpTokenType::TWHILE || current.type == SpTokenType::TIF) {
				std::vector<ParentTRelationship*> moreParentTVector = ParentExtractor::getNestedParentT(procOrWhileIfToken, current);
				parentTVector.insert(parentTVector.end(), moreParentTVector.begin(), moreParentTVector.end());
			}
		}
		for (int i = 0; i < stmtSeriesInStmtLst_2.size(); i++) {
			SimpleToken current = stmtSeriesInStmtLst_2.at(i);
			if (current.type == SpTokenType::TWHILE || current.type == SpTokenType::TIF) {
				std::vector<ParentTRelationship*> moreParentTVector = ParentExtractor::getNestedParentT(procOrWhileIfToken, current);
				parentTVector.insert(parentTVector.end(), moreParentTVector.begin(), moreParentTVector.end());
			}
		}
	}

	return parentTVector;
}

Entity* ParentExtractor::generateEntity(SimpleToken token) {
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

/*
void ParentExtractor::extractParent(Extractor extractor, SimpleToken parentToken, std::vector<SimpleToken> seriesOfStmts) {
	while (seriesOfStmts.size() > 0) {
		SimpleToken childToken = seriesOfStmts.at(0);
		Entity* parent = generateEntity(parentToken);
		Entity* child = generateEntity(childToken);

		ParentRelationship* parentRelationship = new ParentRelationship(parent, child);
		extractor.client->storeRelationship(parentRelationship);

		seriesOfStmts.erase(seriesOfStmts.begin());
	}
}

void ParentExtractor::extractParentT(Extractor extractor, SimpleToken parent, std::vector<SimpleToken> seriesOfStmts) {
	// code here
}

Entity* ParentExtractor::generateEntity(SimpleToken token) {
	if (token.type == SpTokenType::TREAD) {
		return new ReadEntity(std::to_string(token.statementNumber));
	} else if (token.type == SpTokenType::TPRINT) {
		return new PrintEntity(std::to_string(token.statementNumber));
	} else if (token.type == SpTokenType::TASSIGN) {
		return new AssignEntity(std::to_string(token.statementNumber));
	} else if (token.type == SpTokenType::TWHILE) {
		return new WhileEntity(std::to_string(token.statementNumber));
	} else if (token.type == SpTokenType::TIF) {
		return new IfEntity(std::to_string(token.statementNumber));
	} else if (token.type == SpTokenType::TCALL) {
		return new CallEntity(std::to_string(token.statementNumber));
	}
	return new Entity(std::to_string(token.statementNumber));
}
*/
