#include "QPSClient.h"

#include "../../qps/query_preprocessor/query_tokenizer/TokenType.h"

#include "../pkb.h"

#include <string>
#include <unordered_set>

QPSClient::QPSClient(PKB* knowledge) {
	pkb = knowledge;
}

std::unordered_set<std::string> QPSClient::getAllEntity(qps::TokenType returnType) {
	return pkb->getAllEntity(returnType);
}

