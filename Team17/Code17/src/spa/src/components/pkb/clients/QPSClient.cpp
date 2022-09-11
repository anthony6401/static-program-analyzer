#include "QPSClient.h"

#include "models/Entity/DesignEntity.h"

#include "../pkb.h"

#include <string>
#include <unordered_set>

QPSClient::QPSClient(PKB* knowledge) {
	pkb = knowledge;
}

std::unordered_set<std::string> QPSClient::getAllEntity(DesignEntity returnType) {
	return pkb->getAllEntity(returnType);
}

