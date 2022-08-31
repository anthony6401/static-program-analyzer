#ifndef SPA_REUSABLETOKENS_H
#define SPA_REUSABLETOKENS_H

#include "components/qps/query_preprocessor/query_tokenizer/Tokenizer.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

TokenObject modifiesTokenObject = TokenObject(TokenType::MODIFIES, "Modifies");
TokenObject usesTokenObject = TokenObject(TokenType::USES, "Uses");

TokenObject stmtTokenObject = TokenObject(TokenType::STMT, "stmt");
TokenObject procTokenObject = TokenObject(TokenType::PROCEDURE, "procedure");
TokenObject readTokenObject = TokenObject(TokenType::READ, "read");
TokenObject printTokenObject = TokenObject(TokenType::PRINT, "print");
TokenObject callTokenObject = TokenObject(TokenType::CALL, "call");
TokenObject assignTokenObject = TokenObject(TokenType::ASSIGN, "assign");
TokenObject whileTokenObject = TokenObject(TokenType::WHILE, "while");
TokenObject ifTokenObject = TokenObject(TokenType::IF, "if");
TokenObject variableTokenObject = TokenObject(TokenType::VARIABLE, "variable");
TokenObject constantTokenObject = TokenObject(TokenType::CONSTANT, "constant");

TokenObject semicolonTokenObject = TokenObject(TokenType::SEMI_COLON, ";");
TokenObject commaTokenObject = TokenObject(TokenType::COMMA, ",");

TokenObject v_nameTokenObject = TokenObject(TokenType::NAME, "v");
TokenObject v1_nameTokenObject = TokenObject(TokenType::NAME, "v1");
TokenObject s_nameTokenObject = TokenObject(TokenType::NAME, "s");
TokenObject s1_nameTokenObject = TokenObject(TokenType::NAME, "s1");
TokenObject p_nameTokenObject = TokenObject(TokenType::NAME, "p");
TokenObject q_nameTokenObject = TokenObject(TokenType::NAME, "q");
TokenObject a_nameTokenObject = TokenObject(TokenType::NAME, "a");
TokenObject a1_nameTokenObject = TokenObject(TokenType::NAME, "a1");
TokenObject w_nameTokenObject = TokenObject(TokenType::NAME, "w");
TokenObject ifs_nameTokenObject = TokenObject(TokenType::NAME, "ifs");
TokenObject c_nameTokenObject = TokenObject(TokenType::NAME, "c");
TokenObject re_nameTokenObject = TokenObject(TokenType::NAME, "re");
TokenObject pn_nameTokenObject = TokenObject(TokenType::NAME, "pn");
TokenObject cl_nameTokenObject = TokenObject(TokenType::NAME, "cl");

#endif //SPA_REUSABLETOKENS_H
