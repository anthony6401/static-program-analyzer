#include "UsesExtractor.h"

std::vector<UsesRelationship*> UsesExtractor::extractUses(SimpleToken procOrStmtLstToken) {
	std::vector<UsesRelationship*> usesVector;

	std::vector<SimpleToken> stmtSeries = procOrStmtLstToken.getChildren();

	for (int i = 0; i < stmtSeries.size(); i++) {
		SimpleToken current = stmtSeries.at(i);
		if (current.type == SpTokenType::TREAD) {
			// Do nothing
		}
		if (current.type == SpTokenType::TPRINT) {
			SimpleToken printVar = current.getChildren().at(0);
			Entity* printEntity = generateEntity(current);
			Entity* varEntity = generateEntity(printVar);
			UsesRelationship* uses = new UsesRelationship(printEntity, varEntity);
			usesVector.push_back(uses);
		}
		if (current.type == SpTokenType::TASSIGN) {
			SimpleToken expression = current.getChildren().at(1);
			std::vector<SimpleToken> seriesOfVarOprConst = expression.getChildren();
			for (int j = 0; j < seriesOfVarOprConst.size(); j++) {
				SimpleToken currentVarOprConst = seriesOfVarOprConst.at(j);
				if (currentVarOprConst.type == SpTokenType::TVARIABLE) {
					Entity* assignEntity = generateEntity(current);
					Entity* varEntity = generateEntity(currentVarOprConst);
					UsesRelationship* uses = new UsesRelationship(assignEntity, varEntity);
					usesVector.push_back(uses);
				}
			}
		}
		if (current.type == SpTokenType::TWHILE) {
			SimpleToken condExpr = current.getChildren().at(0);
			std::vector<SimpleToken> seriesOfVarConst = condExpr.getChildren();
			for (int j = 0; j < seriesOfVarConst.size(); j++) {
				SimpleToken currentVarConst = seriesOfVarConst.at(j);
				if (currentVarConst.type == SpTokenType::TVARIABLE) {
					Entity* whileEntity = generateEntity(current);
					Entity* varEntity = generateEntity(currentVarConst);
					UsesRelationship* uses = new UsesRelationship(whileEntity, varEntity);
					usesVector.push_back(uses);
				}
			}

			SimpleToken stmtLst = current.getChildren().at(1);
			std::vector<UsesRelationship*> moreUsesVector = UsesExtractor::extractUses(stmtLst);
			usesVector.insert(usesVector.end(), moreUsesVector.begin(), moreUsesVector.end());
		}
		if (current.type == SpTokenType::TIF) {
			SimpleToken condExpr = current.getChildren().at(0);
			std::vector<SimpleToken> seriesOfVarConst = condExpr.getChildren();
			for (int j = 0; j < seriesOfVarConst.size(); j++) {
				SimpleToken currentVarConst = seriesOfVarConst.at(j);
				if (currentVarConst.type == SpTokenType::TVARIABLE) {
					Entity* ifEntity = generateEntity(current);
					Entity* varEntity = generateEntity(currentVarConst);
					UsesRelationship* uses = new UsesRelationship(ifEntity, varEntity);
					usesVector.push_back(uses);
				}
			}

			SimpleToken stmtLst_1 = current.getChildren().at(1);
			SimpleToken stmtLst_2 = current.getChildren().at(2);
			std::vector<UsesRelationship*> moreUsesVector_1 = UsesExtractor::extractUses(stmtLst_1);
			std::vector<UsesRelationship*> moreUsesVector_2 = UsesExtractor::extractUses(stmtLst_2);
			usesVector.insert(usesVector.end(), moreUsesVector_1.begin(), moreUsesVector_1.end());
			usesVector.insert(usesVector.end(), moreUsesVector_2.begin(), moreUsesVector_2.end());
		}
	}

	return usesVector;
}

Entity* UsesExtractor::generateEntity(SimpleToken token) {
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
