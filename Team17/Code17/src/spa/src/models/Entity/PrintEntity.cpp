#include "PrintEntity.h"
#include "Entity.h"

#include <string>

PrintEntity::PrintEntity(std::string entityValue, std::string valueName) : StatementEntity(entityValue), valueName(valueName) {};

std::string PrintEntity::getValueName() {
	return this->valueName;
}
