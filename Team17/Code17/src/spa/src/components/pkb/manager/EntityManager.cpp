#include "EntityManager.h"

#include "../storage/AssignEntityStorage.h"
#include "../storage/CallEntityStorage.h"
#include "../storage/ConstantEntityStorage.h"
#include "../storage/EntityStorage.h"
#include "../storage/IfEntityStorage.h"
#include "../storage/PrintEntityStorage.h"
#include "../storage/ProcedureEntityStorage.h"
#include "../storage/ReadEntityStorage.h"
#include "../storage/StatementEntityStorage.h"
#include "../storage/VariableEntityStorage.h"
#include "../storage/WhileEntityStorage.h"

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
	entityStore.push_back(assStore);
	entityStore.push_back(callStore);
	entityStore.push_back(constStore);
	entityStore.push_back(ifStore);
	entityStore.push_back(prStore);
	entityStore.push_back(procStore);
	entityStore.push_back(reStore);
	entityStore.push_back(stStore);
	entityStore.push_back(varStore);
	entityStore.push_back(whileStore);
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

std::vector<std::string> EntityManager::getEntity(Entity entity) {
	//TODO: to be implemented
	return std::vector<std::string>{"hi"};
}
