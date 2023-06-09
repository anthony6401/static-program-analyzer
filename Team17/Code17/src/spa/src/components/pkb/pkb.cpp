#include "pkb.h"

PKB::PKB() {
	entityManager = new EntityManager();
	relManager = new RelationshipManager();
	patternManager = new PatternManager();
};


bool PKB::isRuntimeRelationship(RelationshipType relType) {
	return relType == RelationshipType::NEXT_T || relType == RelationshipType::AFFECTS || relType == RelationshipType::AFFECTS_T;
}

void PKB::clearCache() {
	relManager->clearCache();
}

std::unordered_set<std::string> PKB::getFilter(RelationshipType relType, DesignEntity designEntity) {
	if (relType == RelationshipType::AFFECTS || relType == RelationshipType::AFFECTS_T) {
		if (designEntity == DesignEntity::STMT || designEntity == DesignEntity::ASSIGN) {
			return entityManager->getAllEntity(DesignEntity::ASSIGN);
		}

		return std::unordered_set<std::string>();
	}

	return entityManager->getAllEntity(designEntity);
}

std::unordered_set<std::string> PKB::getAllEntity(DesignEntity returnType) {
	return entityManager->getAllEntity(returnType);
}

bool PKB::storeRelationship(Relationship* rel) {
	bool ret = false;

	//Store entity first if haven't
	bool resultOne = entityManager->storeEntity(rel->getLeftEntity());
	bool resultTwo = entityManager->storeEntity(rel->getRightEntity());
	ret = ret || resultOne || resultTwo;

	bool resultStoreRel = relManager->storeRelationship(rel);
	
	ret = ret || resultStoreRel;

	return ret;
}

bool PKB::storeConstant(Entity* entity) {
	return entityManager->storeEntity(entity);
}

bool PKB::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (isRuntimeRelationship(relType)) {
		return relManager->getRuntimeRelationship(relType, firstArgument, secondArgument);
	}
	return relManager->getRelationship(relType, firstArgument, secondArgument);
}

std::unordered_set<std::string> PKB::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType) {
	if (isRuntimeRelationship(relType)) {
		std::unordered_set<std::string> filter = getFilter(relType, returnType);

		if (filter.size() == 0) {
			return std::unordered_set<std::string>();
		}

		return relManager->getRuntimeRelationshipByFirst(relType, firstArgument, filter);
	}

	return relManager->getRelationshipByFirst(relType, firstArgument, returnType);
}

std::unordered_set<std::string> PKB::getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) {
	if (isRuntimeRelationship(relType)) {
		std::unordered_set<std::string> filter = getFilter(relType, returnType);

		if (filter.size() == 0) {
			return std::unordered_set<std::string>();
		}

		return relManager->getRuntimeRelationshipBySecond(relType, secondArgument, filter);
	}

	return relManager->getRelationshipBySecond(relType, returnType, secondArgument);
}

std::unordered_set<std::string> PKB::getRelationshipWithFirstWildcard(RelationshipType relType, DesignEntity returnType) {
	if (isRuntimeRelationship(relType)) {
		std::unordered_set<std::string> filter1 = getFilter(relType, DesignEntity::STMT);
		std::unordered_set<std::string> filter2 = getFilter(relType, returnType);

		if (filter1.size() == 0 || filter2.size() == 0) {
			return std::unordered_set<std::string>();
		}
		return relManager->getRuntimeRelationshipWithFirstWildcard(relType, filter1, filter2);
	}
	return relManager->getRelationshipWithFirstWildcard(relType, returnType);
}

std::unordered_set<std::string> PKB::getRelationshipWithSecondWildcard(RelationshipType relType, DesignEntity returnType) {
	if (isRuntimeRelationship(relType)) {
		std::unordered_set<std::string> filter1 = getFilter(relType, returnType);
		std::unordered_set<std::string> filter2 = getFilter(relType, DesignEntity::STMT);

		if (filter1.size() == 0 || filter2.size() == 0) {
			return std::unordered_set<std::string>();
		}

		return relManager->getRuntimeRelationshipWithSecondWildcard(relType, filter1, filter2);
	}
	return relManager->getRelationshipWithSecondWildcard(relType, returnType);
}

std::unordered_map<std::string, std::unordered_set<std::string>> PKB::getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2) {
	if (isRuntimeRelationship(relType)) {
		std::unordered_set<std::string> filter1 = getFilter(relType, returnType1);
		std::unordered_set<std::string> filter2 = getFilter(relType, returnType2);

		if (filter1.size() == 0 || filter2.size() == 0) {
			return std::unordered_map<std::string, std::unordered_set<std::string>>();
		}

		return relManager->getAllRuntimeRelationship(relType, filter1, filter2);
	}
	return relManager->getAllRelationship(relType, returnType1, returnType2);
}

bool PKB::storePattern(kb::Pattern* pattern) {
	return patternManager->storePattern(pattern);
}

std::unordered_set<std::string> PKB::getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument) {
	return patternManager->getPattern(designEntity, firstArgument, secondArgument);
}

std::unordered_set<std::string> PKB::getPatternWildcard(DesignEntity designEntity, TokenObject secondArgument) {
	return patternManager->getPatternWildcard(designEntity, secondArgument);
}

std::vector<std::pair<std::string, std::string>> PKB::getPatternPair(DesignEntity designEntity, TokenObject secondArgument) {
	return patternManager->getPatternPair(designEntity, secondArgument);
}

std::string PKB::getStatementMapping(std::string& stmtNumber, DesignEntity entityType) {
	return entityManager->getStatementMapping(stmtNumber, entityType);
}

std::unordered_set<std::string> PKB::getStatementByName(std::string& name, DesignEntity entityType) {
	return entityManager->getStatementByName(name, entityType);
}

std::unordered_set<std::string> PKB::getAllName(DesignEntity entityType) {
	return entityManager->getAllName(entityType);
}

EntityManager* PKB::getEntityManager() {
	return entityManager;
}

RelationshipManager* PKB::getRelationshipManager() {
	return relManager;
}

PatternManager* PKB::getPatternManager(){
	return patternManager;
}

PKB::~PKB() {
	delete relManager;
	delete patternManager;
	delete entityManager;
}
