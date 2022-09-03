#pragma once

#include "../SimpleToken.h"
#include "../../../models/Relationship/Relationship.h"

#include <vector>

using namespace std;

class Extractor {
public:
	Extractor();

	void extractRead(SimpleToken simpleToken, vector<string> tokens);
	void extractPrint(SimpleToken simpleToken, vector<string> tokens);

	void extractProcedure();
	void extractStatement();
	void extractCall();
	void extractWhile();
	void extractIf();
	void extractAssign();
	void extractCondExpr();
	void extractVariable();
	void extractConstant();
	void extractClose();
	void extractOpr();
	void extractError();
};
