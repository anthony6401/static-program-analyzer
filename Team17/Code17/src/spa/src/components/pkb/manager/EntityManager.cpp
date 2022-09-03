#include "EntityManager.h"
#include "../../../models/Entity/Entity.h"

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

#include "../../qps/query_preprocessor/query_tokenizer/TokenType.h"

#include <unordered_set>
//#include <bits/stdc++.h>

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

std::vector<std::string> EntityManager::getAllEntity(qps::TokenType returnType) {
	//TODO: to be implemented
	std::unordered_set<Entity*>* temp;
	std::vector<std::string> ret;

	for (auto& es : entityStore) {
		temp = es->getAllEntity(returnType);

		if (temp != nullptr) {
			for (const auto& entity: *temp) {
				std::string k = entity->getValue();
				if (std::find(ret.begin(), ret.end(), k) != ret.end()) {
					ret.push_back(k);
				}
			}
			break;
		}
	}

	return ret;
}
