#pragma once
#include "models/Relationship/Relationship.h"
#include "models/Relationship/RelationshipType.h"

#include "models/Entity/DesignEntity.h"

#include "RelationshipStorage.h"

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

#include <unordered_set>
#include <unordered_map>
#include <string>

class ParentRelationshipStorage : public RelationshipStorage {
public:
	ParentRelationshipStorage();
	bool storeRelationship(Relationship* rel);
	bool getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType);
	std::unordered_set<std::string> getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returntype2);
private:
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
