#include "QPSClient.h"

#include "../../qps/query_preprocessor/query_tokenizer/TokenType.h"

#include "../pkb.h"

#include <string>
#include <vector>

QPSClient::QPSClient(PKB* knowledge) {
	pkb = knowledge;
}

std::vector<std::string> QPSClient::getAllEntity(qps::TokenType returnType) {
	return pkb->getAllEntity(returnType);
}

