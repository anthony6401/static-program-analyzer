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
		std::vector<SimpleToken> stmtSeriesForStmtLst_1 = stmtLstToken_1.getChildren();
		std::vector<SimpleToken> stmtSeriesForStmtLst_2 = stmtLstToken_1.getChildren();
		for (int i = 0; i < stmtSeriesForStmtLst_1.size(); i++) {
			SimpleToken childToken = stmtSeriesForStmtLst_1.at(i);
			Entity* parentEntity = generateEntity(procOrWhileIfToken);
			Entity* childEntity = generateEntity(childToken);
			ParentRelationship* parent = new ParentRelationship(parentEntity, childEntity);
			parentVector.push_back(parent);
		}
		for (int i = 0; i < stmtSeriesForStmtLst_2.size(); i++) {
			SimpleToken childToken = stmtSeriesForStmtLst_2.at(i);
			Entity* parentEntity = generateEntity(procOrWhileIfToken);
			Entity* childEntity = generateEntity(childToken);
			ParentRelationship* parent = new ParentRelationship(parentEntity, childEntity);
			parentVector.push_back(parent);
		}
	}

	for (int i = 0; i < stmtSeries.size(); i++) {
		SimpleToken current = stmtSeries.at(i);
		if (current.type == SpTokenType::TWHILE || current.type == SpTokenType::TIF || current.type == SpTokenType::TSTMTLST) {
			std::vector<ParentRelationship*> moreParentVector = ParentExtractor::extractParent(current);
			parentVector.insert(parentVector.end(), moreParentVector.begin(), moreParentVector.end());
		}
	}

	return parentVector;
}

std::vector<ParentTRelationship*> ParentExtractor::extractParentT(SimpleToken procOrWhileIfToken) {
	// set as parent current for all stmts in stmtlst
	// then trot down to any while/ifs and set those stmts to be children as well, recurse
	// once done, trot again and repeat for any while/ifs
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
