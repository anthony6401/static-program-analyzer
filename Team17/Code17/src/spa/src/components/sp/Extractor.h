#pragma once

#include "SimpleToken.h"
#include "../../models/Relationship/Relationship.h"

#include <vector>

using namespace std;

class Extractor {
public:
	Extractor();
	vector<Relationship*> extractRelationships(SimpleToken parentToken);
	void handleProcedure(vector<Relationship*> relationships);
	void handleStatement(vector<Relationship*> relationships);
	void handleRead(vector<Relationship*> relationships);
	void handlePrint(vector<Relationship*> relationships);
	void handleCall(vector<Relationship*> relationships);
	void handleWhile(vector<Relationship*> relationships);
	void handleIf(vector<Relationship*> relationships);
	void handleAssign(vector<Relationship*> relationships);
	void handleCondExpr(vector<Relationship*> relationships);
	void handleVariable(vector<Relationship*> relationships);
	void handleConstant(vector<Relationship*> relationships);
	void handleClose(vector<Relationship*> relationships);
	void handleOpr(vector<Relationship*> relationships);
	void handleError();
};
