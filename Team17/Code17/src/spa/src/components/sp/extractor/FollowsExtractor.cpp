#include "FollowsExtractor.h"

std::vector<FollowsRelationship*> FollowsExtractor::extractFollows(SimpleToken procOrWhileIfToken) {
	std::vector<FollowsRelationship*> followsVector;

	std::vector<SimpleToken> stmtSeries = procOrWhileIfToken.getChildren();

	if (procOrWhileIfToken.type == SpTokenType::TPROCEDURE) {
		for (int i = 0; i < stmtSeries.size() - 1; i++) {
			SimpleToken formerToken = stmtSeries.at(i);
			SimpleToken latterToken = stmtSeries.at(i + 1);
			Entity* formerEntity = generateEntity(formerToken);
			Entity* latterEntity = generateEntity(latterToken);
			FollowsRelationship* follows = new FollowsRelationship(formerEntity, latterEntity);
			followsVector.push_back(follows);
		}
	}

	if (procOrWhileIfToken.type == SpTokenType::TWHILE) {
		SimpleToken stmtLstToken = stmtSeries.at(1);
		std::vector<SimpleToken> stmtSeriesInStmtLst = stmtLstToken.getChildren();
		for (int i = 0; i < stmtSeriesInStmtLst.size() - 1; i++) {
			SimpleToken formerToken = stmtSeriesInStmtLst.at(i);
			SimpleToken latterToken = stmtSeriesInStmtLst.at(i + 1);
			Entity* formerEntity = generateEntity(formerToken);
			Entity* latterEntity = generateEntity(latterToken);
			FollowsRelationship* follows = new FollowsRelationship(formerEntity, latterEntity);
			followsVector.push_back(follows);
		}
	}

	if (procOrWhileIfToken.type == SpTokenType::TIF) {
		SimpleToken stmtLstToken_1 = stmtSeries.at(1);
		SimpleToken stmtLstToken_2 = stmtSeries.at(2);
		std::vector<SimpleToken> stmtSeriesInStmtLst_1 = stmtLstToken_1.getChildren();
		std::vector<SimpleToken> stmtSeriesInStmtLst_2 = stmtLstToken_2.getChildren();
		for (int i = 0; i < stmtSeriesInStmtLst_1.size() - 1; i++) {
			SimpleToken formerToken = stmtSeriesInStmtLst_1.at(i);
			SimpleToken latterToken = stmtSeriesInStmtLst_1.at(i + 1);
			Entity* formerEntity = generateEntity(formerToken);
			Entity* latterEntity = generateEntity(latterToken);
			FollowsRelationship* follows = new FollowsRelationship(formerEntity, latterEntity);
			followsVector.push_back(follows);
		}
		for (int i = 0; i < stmtSeriesInStmtLst_2.size() - 1; i++) {
			SimpleToken formerToken = stmtSeriesInStmtLst_2.at(i);
			SimpleToken latterToken = stmtSeriesInStmtLst_2.at(i + 1);
			Entity* formerEntity = generateEntity(formerToken);
			Entity* latterEntity = generateEntity(latterToken);
			FollowsRelationship* follows = new FollowsRelationship(formerEntity, latterEntity);
			followsVector.push_back(follows);
		}
	}

	for (int i = 0; i < stmtSeries.size(); i++) {
		SimpleToken current = stmtSeries.at(i);
		if (current.type == SpTokenType::TWHILE || current.type == SpTokenType::TIF || current.type == SpTokenType::TSTMTLIST) {
			std::vector<FollowsRelationship*> moreFollowsVector = FollowsExtractor::extractFollows(current);
			followsVector.insert(followsVector.end(), moreFollowsVector.begin(), moreFollowsVector.end());
		}
	}

	return followsVector;
}

std::vector<FollowsTRelationship*> FollowsExtractor::extractFollowsT(SimpleToken procOrWhileIfToken) {
	std::vector<FollowsTRelationship*> followsTVector;

	std::vector<SimpleToken> stmtSeries = procOrWhileIfToken.getChildren();

	if (procOrWhileIfToken.type == SpTokenType::TPROCEDURE) {
		for (int i = 0; i < stmtSeries.size(); i++) {
			for (int j = i + 1; j < stmtSeries.size(); j++) {
				SimpleToken formerToken = stmtSeries.at(i);
				SimpleToken latterToken = stmtSeries.at(j);
				Entity* formerEntity = generateEntity(formerToken);
				Entity* latterEntity = generateEntity(latterToken);
				FollowsTRelationship* followsT = new FollowsTRelationship(formerEntity, latterEntity);
				followsTVector.push_back(followsT);
			}
		}
	}

	if (procOrWhileIfToken.type == SpTokenType::TWHILE) {
		SimpleToken stmtLstToken = stmtSeries.at(1);
		std::vector<SimpleToken> stmtSeriesInStmtLst = stmtLstToken.getChildren();
		for (int i = 0; i < stmtSeriesInStmtLst.size(); i++) {
			for (int j = i + 1; j < stmtSeriesInStmtLst.size(); j++) {
				SimpleToken formerToken = stmtSeriesInStmtLst.at(i);
				SimpleToken latterToken = stmtSeriesInStmtLst.at(j);
				Entity* formerEntity = generateEntity(formerToken);
				Entity* latterEntity = generateEntity(latterToken);
				FollowsTRelationship* followsT = new FollowsTRelationship(formerEntity, latterEntity);
				followsTVector.push_back(followsT);
			}
		}
	}

	if (procOrWhileIfToken.type == SpTokenType::TIF) {
		SimpleToken stmtLstToken_1 = stmtSeries.at(1);
		SimpleToken stmtLstToken_2 = stmtSeries.at(2);
		std::vector<SimpleToken> stmtSeriesInStmtLst_1 = stmtLstToken_1.getChildren();
		std::vector<SimpleToken> stmtSeriesInStmtLst_2 = stmtLstToken_1.getChildren();
		for (int i = 0; i < stmtSeriesInStmtLst_1.size(); i++) {
			for (int j = i + 1; j < stmtSeriesInStmtLst_1.size(); j++) {
				SimpleToken formerToken = stmtSeriesInStmtLst_1.at(i);
				SimpleToken latterToken = stmtSeriesInStmtLst_1.at(j);
				Entity* formerEntity = generateEntity(formerToken);
				Entity* latterEntity = generateEntity(latterToken);
				FollowsTRelationship* followsT = new FollowsTRelationship(formerEntity, latterEntity);
				followsTVector.push_back(followsT);
			}
		}
		for (int i = 0; i < stmtSeriesInStmtLst_2.size(); i++) {
			for (int j = i + 1; j < stmtSeriesInStmtLst_2.size(); j++) {
				SimpleToken formerToken = stmtSeriesInStmtLst_2.at(i);
				SimpleToken latterToken = stmtSeriesInStmtLst_2.at(j);
				Entity* formerEntity = generateEntity(formerToken);
				Entity* latterEntity = generateEntity(latterToken);
				FollowsTRelationship* followsT = new FollowsTRelationship(formerEntity, latterEntity);
				followsTVector.push_back(followsT);
			}
		}
	}

	for (int i = 0; i < stmtSeries.size(); i++) {
		SimpleToken current = stmtSeries.at(i);
		if (current.type == SpTokenType::TWHILE || current.type == SpTokenType::TIF || current.type == SpTokenType::TSTMT) {
			std::vector<FollowsTRelationship*> moreFollowsTVector = FollowsExtractor::extractFollowsT(current);
			followsTVector.insert(followsTVector.end(), moreFollowsTVector.begin(), moreFollowsTVector.end());
		}
	}

	return followsTVector;
}

Entity* FollowsExtractor::generateEntity(SimpleToken token) {
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
void FollowsExtractor::extractFollows(Extractor extractor, std::vector<SimpleToken> seriesOfStmts) {
	while (seriesOfStmts.size() > 1) {
		SimpleToken formerToken = seriesOfStmts.at(0);
		SimpleToken latterToken = seriesOfStmts.at(1);

		Entity* former = generateEntity(formerToken);
		Entity* latter = generateEntity(latterToken);

		FollowsRelationship* followsRelationship = new FollowsRelationship(former, latter);
		extractor.client->storeRelationship(followsRelationship);

		seriesOfStmts.erase(seriesOfStmts.begin());
	}
}

void FollowsExtractor::extractFollowsT(Extractor extractor, std::vector<SimpleToken> seriesOfStmts) {
	// code here
}
*/
