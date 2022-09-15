#include "FollowsExtractor.h"

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

Entity* FollowsExtractor::generateEntity(SimpleToken token) {
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
