#ifndef SPA_REUSABLETOKENS_H
#define SPA_REUSABLETOKENS_H

#include "components/qps/query_preprocessor/query_tokenizer/Tokenizer.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

TokenObject modifiesTokenObject = TokenObject(TokenType::MODIFIES, "Modifies");
TokenObject usesTokenObject = TokenObject(TokenType::USES, "Uses");

TokenObject stmtTokenObject = TokenObject(TokenType::STMT, "stmt");
TokenObject readTokenObject = TokenObject(TokenType::READ, "read");
TokenObject printTokenObject = TokenObject(TokenType::PRINT, "print");
TokenObject callTokenObject = TokenObject(TokenType::CALL, "call");
TokenObject assignTokenObject = TokenObject(TokenType::ASSIGN, "assign");
TokenObject whileTokenObject = TokenObject(TokenType::WHILE, "while");
TokenObject ifTokenObject = TokenObject(TokenType::IF, "if");
TokenObject variableTokenObject = TokenObject(TokenType::VARIABLE, "variable");
TokenObject constantTokenObject = TokenObject(TokenType::CONSTANT, "constant");


#endif //SPA_REUSABLETOKENS_H
