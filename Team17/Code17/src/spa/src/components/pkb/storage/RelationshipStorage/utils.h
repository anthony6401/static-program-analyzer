#pragma once
#include <unordered_map>
#include <unordered_set>
#include "models/Entity/AssignEntity.h"
#include "models/Entity/CallEntity.h"
#include "models/Entity/ConstantEntity.h"
#include "models/Entity/Entity.h"
#include "models/Entity/IfEntity.h"
#include "models/Entity/PrintEntity.h"
#include "models/Entity/ProcedureEntity.h"
#include "models/Entity/ReadEntity.h"
#include "models/Entity/StatementEntity.h"
#include "models/Entity/VariableEntity.h"
#include "models/Entity/WhileEntity.h"
#include <string>

class RelationshipUtils {
public:
	// OUTDATED FUNCTION
	static bool insertEntity(std::unordered_map<std::string, std::unordered_set<std::string>>& map, std::string& leftValueTest, std::string& rightValueTest) {
		if (map.find(leftValueTest) == map.end()) {
			map.insert({ leftValueTest, std::unordered_set<std::string>() });
		}

		return map.find(leftValueTest)->second.insert(rightValueTest).second;
	}

	static bool insertEntity(std::unordered_map<std::string, std::unordered_set<std::string>>* map, std::string& leftValueTest, std::string& rightValueTest) {
		if (map == nullptr) {
			return false;
		}

		if (map->find(leftValueTest) == map->end()) {
			map->insert({ leftValueTest, std::unordered_set<std::string>() });
		}

		return map->find(leftValueTest)->second.insert(rightValueTest).second;
	}

	static DesignEntity entityToDesignEntity(Entity* entity) {
		if (typeid(*entity) == typeid(ProcedureEntity)) {
			return DesignEntity::PROCEDURE;
		}

		if (typeid(*entity) == typeid(AssignEntity)) {
			return DesignEntity::ASSIGN;
		}

		if (typeid(*entity) == typeid(CallEntity)) {
			return DesignEntity::CALL;
		}
	
		if (typeid(*entity) == typeid(ConstantEntity)) {
			return DesignEntity::CONSTANT;
		}

		if (typeid(*entity) == typeid(IfEntity)) {
			return DesignEntity::IF;
		}

		if (typeid(*entity) == typeid(PrintEntity)) {
			return DesignEntity::PRINT;
		}

		if (typeid(*entity) == typeid(ReadEntity)) {
			return DesignEntity::READ;
		}

		if (typeid(*entity) == typeid(VariableEntity)) {
			return DesignEntity::VARIABLE;
		}

		if (typeid(*entity) == typeid(WhileEntity)) {
			return DesignEntity::WHILE;
		}

		if (typeid(*entity) == typeid(StatementEntity)) {
			return DesignEntity::STMT;
		}

		return DesignEntity::NOT_FOUND;
	}
};
