#include "EntityManager.h"
#include "../../../models/Entity/Entity.h"

#include "../storage/EntityStorage/AssignEntityStorage.h"
#include "../storage/EntityStorage/CallEntityStorage.h"
#include "../storage/EntityStorage/ConstantEntityStorage.h"
#include "../storage/EntityStorage/EntityStorage.h"
#include "../storage/EntityStorage/IfEntityStorage.h"
#include "../storage/EntityStorage/PrintEntityStorage.h"
#include "../storage/EntityStorage/ProcedureEntityStorage.h"
#include "../storage/EntityStorage/ReadEntityStorage.h"
#include "../storage/EntityStorage/StatementEntityStorage.h"
#include "../storage/EntityStorage/VariableEntityStorage.h"
#include "../storage/EntityStorage/WhileEntityStorage.h"

#include "../../qps/query_preprocessor/query_tokenizer/TokenType.h"

#include <unordered_set>

EntityManager::EntityManager() {
	AssignEntityStorage* assStore = new AssignEntityStorage();
	CallEntityStorage* callStore = new CallEntityStorage();
	ConstantEntityStorage* constStore = new ConstantEntityStorage();
	IfEntityStorage* ifStore = new IfEntityStorage();
	PrintEntityStorage* prStore = new PrintEntityStorage();
	ProcedureEntityStorage* procStore = new ProcedureEntityStorage();
	ReadEntityStorage* reStore = new ReadEntityStorage();
	StatementEntityStorage* stStore = new StatementEntityStorage();
	VariableEntityStorage* varStore = new VariableEntityStorage();
	WhileEntityStorage* whileStore = new WhileEntityStorage();

	//Add each entity into the array
	//Parent Entity storage must be stored last
	entityStore.push_back(assStore);
	entityStore.push_back(callStore);
	entityStore.push_back(constStore);
	entityStore.push_back(ifStore);
	entityStore.push_back(prStore);
	entityStore.push_back(procStore);
	entityStore.push_back(reStore);
	entityStore.push_back(varStore);
	entityStore.push_back(whileStore);
	entityStore.push_back(stStore);
	
}

std::vector<EntityStorage*> EntityManager::getEntityStorage() {
	return entityStore;
}

//Returns true, if it manage to stored, else false
bool EntityManager::storeEntity(Entity* entity) {
 	bool ret = false;
	for (auto& et : entityStore) {
		ret = ret || et->storeEntity(entity);
	}
	return ret;
}

std::unordered_set<std::string> EntityManager::getAllEntity(DesignEntity returnType) {
	std::unordered_set<std::string> temp;
	std::unordered_set<std::string> ret;

	for (auto& es : entityStore) {
		temp = es->getAllEntity(returnType);
;		if (temp != std::unordered_set<std::string>()) {
			return temp;
		}
	}

	return std::unordered_set<std::string>();
}
