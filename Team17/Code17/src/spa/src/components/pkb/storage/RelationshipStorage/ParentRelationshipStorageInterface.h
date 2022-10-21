#pragma once
#include "RelationshipStorage.h"

class ParentRelationshipStorageInterface : public RelationshipStorage {
public:
	ParentRelationshipStorageInterface(RelationshipType relationshipType);
	virtual bool storeRelationship(Relationship* rel) = 0;
	bool getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType);
	std::unordered_set<std::string> getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returntype2);

protected:
	std::unordered_map<std::string, std::unordered_set<std::string>>* getStorageForward(DesignEntity left, DesignEntity right);
	std::unordered_map<std::string, std::unordered_set<std::string>>* getStorageBackward(DesignEntity left);
	std::unordered_map<std::string, std::unordered_set<std::string>>* getIfToSpecificStorage(DesignEntity right);
	std::unordered_map<std::string, std::unordered_set<std::string>>* getWhileToSpecificStorage(DesignEntity right);
	std::unordered_map<std::string, std::unordered_set<std::string>>* getStmtToSpecificStorage(DesignEntity right);

	RelationshipType relationshipType;

	// FOR IF STATEMENT (total 7)
	//Parent(if,r)
	std::unordered_map<std::string, std::unordered_set<std::string>> ifToReadForwardMap;

	//Parent(if,pr)
	std::unordered_map<std::string, std::unordered_set<std::string>> ifToPrintForwardMap;

	//Parent(if,a)
	std::unordered_map<std::string, std::unordered_set<std::string>> ifToAssignForwardMap;

	//Parent(if,call)
	std::unordered_map<std::string, std::unordered_set<std::string>> ifToCallForwardMap;

	//Parent(if,w)
	std::unordered_map<std::string, std::unordered_set<std::string>> ifToWhileForwardMap;

	//Parent(if,if)
	std::unordered_map<std::string, std::unordered_set<std::string>> ifToIfForwardMap;

	//Parent(if,s)
	std::unordered_map<std::string, std::unordered_set<std::string>> ifToStmtForwardMap;

	//Parent(if,2)
	std::unordered_map<std::string, std::unordered_set<std::string>> ifToStmtBackwardMap;

	// FOR WHILE STATEMENT (total 7)
	//Parent(w,r)
	std::unordered_map<std::string, std::unordered_set<std::string>> whileToReadForwardMap;

	//Parent(w,pr)
	std::unordered_map<std::string, std::unordered_set<std::string>> whileToPrintForwardMap;

	//Parent(w,a)
	std::unordered_map<std::string, std::unordered_set<std::string>> whileToAssignForwardMap;

	//Parent(w,call)
	std::unordered_map<std::string, std::unordered_set<std::string>> whileToCallForwardMap;

	//Parent(w,w)
	std::unordered_map<std::string, std::unordered_set<std::string>> whileToWhileForwardMap;

	//Parent(w,if)
	std::unordered_map<std::string, std::unordered_set<std::string>> whileToIfForwardMap;

	//Parent(w,s)
	std::unordered_map<std::string, std::unordered_set<std::string>> whileToStmtForwardMap;

	//Parent(w,2)
	std::unordered_map<std::string, std::unordered_set<std::string>> whileToStmtBackwardMap;


	// For STMT (total 6)

	//Parent(s,r) and Parent(2,r)
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToReadForwardMap;

	//Parent(s,pr) and Parent(2,pr)
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToPrintForwardMap;

	//Parent(s,a) and Parent(2,a)
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToAssignForwardMap;

	//Parent(s,call) and Parent(2,call)
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToCallForwardMap;

	//Parent(s,w) and Parent(2,w)
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToWhileForwardMap;

	//Parent(s,if) and Parent(2,if)
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToIfForwardMap;

	//Parent(s,s) and Parent(2,s) and Parent(1,2)
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToStmtForwardMap;

	//Parent(s,2)
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToStmtBackwardMap;
};
