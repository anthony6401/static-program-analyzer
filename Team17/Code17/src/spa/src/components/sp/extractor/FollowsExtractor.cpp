#include "FollowsExtractor.h"

std::vector<FollowsRelationship*> FollowsExtractor::extractFollows(SimpleToken procOrStmtLstToken) {
	std::vector<FollowsRelationship*> followsVector;

	std::vector<SimpleToken> stmtSeries = procOrStmtLstToken.getChildren();

	for (int i = 0; i < stmtSeries.size() - 1; i++) {
		SimpleToken formerToken = stmtSeries.at(i);
		SimpleToken latterToken = stmtSeries.at(i + 1);
		Entity* formerEntity = generateEntity(formerToken);
		Entity* latterEntity = generateEntity(latterToken);
		FollowsRelationship* follows = new FollowsRelationship(formerEntity, latterEntity);
		followsVector.push_back(follows);
	}

	for (int i = 0; i < stmtSeries.size(); i++) {
		SimpleToken current = stmtSeries.at(i);
		if (current.type == SpTokenType::TWHILE) {
			SimpleToken stmtLstToken = current.getChildren().at(1);
			std::vector<FollowsRelationship*> moreFollowsVector = FollowsExtractor::extractFollows(stmtLstToken);
			followsVector.insert(followsVector.end(), moreFollowsVector.begin(), moreFollowsVector.end());
		}
		if (current.type == SpTokenType::TIF) {
			SimpleToken stmtLstToken_1 = current.getChildren().at(1);
			SimpleToken stmtLstToken_2 = current.getChildren().at(2);
			std::vector<FollowsRelationship*> moreFollowsVector_1 = FollowsExtractor::extractFollows(stmtLstToken_1);
			std::vector<FollowsRelationship*> moreFollowsVector_2 = FollowsExtractor::extractFollows(stmtLstToken_2);
			followsVector.insert(followsVector.end(), moreFollowsVector_1.begin(), moreFollowsVector_1.end());
			followsVector.insert(followsVector.end(), moreFollowsVector_2.begin(), moreFollowsVector_2.end());
		}
	}

	return followsVector;
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
