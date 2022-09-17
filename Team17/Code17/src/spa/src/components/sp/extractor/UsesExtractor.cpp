#include "UsesExtractor.h"

std::vector<UsesRelationship*> UsesExtractor::extractUses(SimpleToken procOrWhileIfToken) {
	std::vector<UsesRelationship*> usesVector;

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

	std::vector<UsesRelationship*> moreUsesVector = getUsesRelationships(procOrWhileIfToken, stmtSeries);
	std::vector<UsesRelationship*> moreUsesVector_1 = getUsesRelationships(procOrWhileIfToken, stmtSeries_1);
	std::vector<UsesRelationship*> moreUsesVector_2 = getUsesRelationships(procOrWhileIfToken, stmtSeries_2);
	usesVector.insert(usesVector.end(), moreUsesVector.begin(), moreUsesVector.end());
	usesVector.insert(usesVector.end(), moreUsesVector_1.begin(), moreUsesVector_1.end());
	usesVector.insert(usesVector.end(), moreUsesVector_2.begin(), moreUsesVector_2.end());

	return usesVector;
}

std::vector<UsesRelationship*> UsesExtractor::getUsesRelationships(SimpleToken procOrWhileIfToken, std::vector<SimpleToken> stmtSeries) {
	std::vector<UsesRelationship*> usesVector;

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
			Entity* procEntity = generateEntity(procOrWhileIfToken);
			Entity* varEntity1 = generateEntity(printVar);
			UsesRelationship* uses1 = new UsesRelationship(procEntity, varEntity1);
			usesVector.push_back(uses1);
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
					Entity* procEntity = generateEntity(procOrWhileIfToken);
					Entity* varEntity1 = generateEntity(currentVarOprConst);
					UsesRelationship* uses1 = new UsesRelationship(procEntity, varEntity1);
					usesVector.push_back(uses1);
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
					Entity* procEntity = generateEntity(procOrWhileIfToken);
					Entity* varEntity1 = generateEntity(currentVarConst);
					UsesRelationship* uses1 = new UsesRelationship(procEntity, varEntity1);
					usesVector.push_back(uses1);
				}
			}
			std::vector<UsesRelationship*> moreUsesVector = getUsesRelationships(procOrWhileIfToken, current.getChildren().at(1).getChildren());
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
					Entity* procEntity = generateEntity(procOrWhileIfToken);
					Entity* varEntity1 = generateEntity(currentVarConst);
					UsesRelationship* uses1 = new UsesRelationship(procEntity, varEntity1);
					usesVector.push_back(uses1);
				}
			}
			std::vector<UsesRelationship*> moreUsesVector_1 = getUsesRelationships(procOrWhileIfToken, current.getChildren().at(1).getChildren());
			std::vector<UsesRelationship*> moreUsesVector_2 = getUsesRelationships(procOrWhileIfToken, current.getChildren().at(2).getChildren());
			usesVector.insert(usesVector.end(), moreUsesVector_1.begin(), moreUsesVector_1.end());
			usesVector.insert(usesVector.end(), moreUsesVector_2.begin(), moreUsesVector_2.end());
		}
	}

	for (int i = 0; i < stmtSeries.size(); i++) {
		SimpleToken current = stmtSeries.at(i);
		if (current.type == SpTokenType::TWHILE || current.type == SpTokenType::TIF || current.type == SpTokenType::TSTMTLIST) {
			std::vector<UsesRelationship*> moreUsesVector = UsesExtractor::extractUses(current);
			usesVector.insert(usesVector.end(), moreUsesVector.begin(), moreUsesVector.end());
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
