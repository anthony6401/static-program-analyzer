#include "QPSClient.h"

QPSClient::QPSClient(PKB* knowledge) {
	pkb = knowledge;
}

std::unordered_set<std::string> QPSClient::getAllEntity(DesignEntity returnType) {
	return pkb->getAllEntity(returnType);
}

bool QPSClient::storeRelationship(Relationship* rel) {
	return pkb->storeRelationship(rel);
}
bool QPSClient::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	return pkb->getRelationship(relType, firstArgument, secondArgument);
}
std::unordered_set<std::string>QPSClient::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType) {
	return pkb->getRelationshipByFirst(relType, firstArgument, returnType);
}
std::unordered_set<std::string> QPSClient::getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) {
	return pkb->getRelationshipBySecond(relType, returnType, secondArgument);
}
std::unordered_set<std::string> QPSClient::getRelationshipWithFirstWildcard(RelationshipType relType, DesignEntity returnType) {
	return pkb->getRelationshipWithFirstWildcard(relType, returnType);
}
std::unordered_set<std::string> QPSClient::getRelationshipWithSecondWildcard(RelationshipType relType, DesignEntity returnType) {
	return pkb->getRelationshipWithSecondWildcard(relType, returnType);
}
std::unordered_map<std::string, std::unordered_set<std::string>> QPSClient::getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returntype2) {
	return pkb->getAllRelationship(relType, returnType1, returntype2);
}

std::unordered_set<std::string> QPSClient::getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument) {
	return pkb->getPattern(designEntity, firstArgument, secondArgument);
}
std::unordered_set<std::string> QPSClient::getContainerPattern(DesignEntity designEntity, TokenObject firstArgument) {
	return pkb->getPattern(designEntity, firstArgument, TokenObject());
}
std::unordered_set<std::string> QPSClient::getPatternWildcard(DesignEntity designEntity, TokenObject secondArgument) {
	return pkb->getPatternWildcard(designEntity, secondArgument);
}
std::unordered_set<std::string> QPSClient::getPatternContainerWildcard(DesignEntity designEntity) {
	return pkb->getPatternWildcard(designEntity, TokenObject());
}
std::vector<std::pair<std::string, std::string>> QPSClient::getPatternPair(DesignEntity designEntity, TokenObject secondArgument) {
	return pkb->getPatternPair(designEntity, secondArgument);
}
std::vector<std::pair<std::string, std::string>> QPSClient::getContainerPatternPair(DesignEntity designEntity) {
	return pkb->getPatternPair(designEntity, TokenObject());
}
std::string QPSClient::getStatementMapping(std::string& stmtNumber, DesignEntity entityType) {
	return pkb->getStatementMapping(stmtNumber, entityType);
}

std::unordered_set<std::string> QPSClient::getStatementByName(std::string& name, DesignEntity entityType) {
	return pkb->getStatementByName(name, entityType);
}

std::unordered_set<std::string> QPSClient::getAllName(DesignEntity entityType) {
	return pkb->getAllName(entityType);
}
