#pragma once

#include "../SimpleToken.h"
#include <vector>

using namespace std;

class Extractor {
public:
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
