#include "ParentExtractor.h"

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
}
