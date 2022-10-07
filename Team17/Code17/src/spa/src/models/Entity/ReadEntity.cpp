#include "ReadEntity.h"
#include "Entity.h"

#include <string>

ReadEntity::ReadEntity(std::string entityValue, std::string valueName) : StatementEntity(entityValue), valueName(valueName) {};

std::string ReadEntity::getValueName() {
	return this->valueName;
}
