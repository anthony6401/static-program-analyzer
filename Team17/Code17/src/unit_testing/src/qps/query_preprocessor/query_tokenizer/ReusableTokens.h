#ifndef SPA_REUSABLETOKENS_H
#define SPA_REUSABLETOKENS_H

#include "components/qps/query_preprocessor/query_tokenizer/Tokenizer.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

TokenObject modifiesTokenObject = TokenObject(TokenType::MODIFIES, "Modifies");
TokenObject usesTokenObject = TokenObject(TokenType::USES, "Uses");
TokenObject parentTokenObject = TokenObject(TokenType::PARENT, "Parent");
TokenObject parentTTokenObject = TokenObject(TokenType::PARENT_T, "Parent*");
TokenObject followsTokenObject = TokenObject(TokenType::FOLLOWS, "Follows");
TokenObject followsTTokenObject = TokenObject(TokenType::FOLLOWS_T, "Follows*");
TokenObject callsTokenObject = TokenObject(TokenType::CALLS, "Calls");
TokenObject callsTTokenObject = TokenObject(TokenType::CALLS_T, "Calls*");
TokenObject nextTokenObject = TokenObject(TokenType::NEXT, "Next");
TokenObject nextTTokenObject = TokenObject(TokenType::NEXT_T, "Next*");
TokenObject affectsTokenObject = TokenObject(TokenType::AFFECTS, "Affects");
TokenObject affectsTTokenObject = TokenObject(TokenType::AFFECTS_T, "Affects*");
TokenObject patternTokenObject = TokenObject(TokenType::PATTERN, "pattern");
TokenObject selectTokenObject = TokenObject(TokenType::SELECT, "Select");
TokenObject suchTokenObject = TokenObject(TokenType::SUCH, "such");
TokenObject thatTokenObject = TokenObject(TokenType::THAT, "that");
TokenObject openBracketTokenObject = TokenObject(TokenType::OPEN_BRACKET, "(");
TokenObject closedBracketTokenObject = TokenObject(TokenType::CLOSED_BRACKET, ")");

TokenObject andTokenObject = TokenObject(TokenType::AND, "and");

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

TokenObject normsq_nameWithQuotesTokenObject = TokenObject(TokenType::NAME_WITH_QUOTATION, "normSq");
TokenObject x_nameWithQuotesTokenObject = TokenObject(TokenType::NAME_WITH_QUOTATION, "x");
TokenObject cenX_subexpressionTokenObject = TokenObject(TokenType::SUBEXPRESSION, "cenX");
TokenObject one_constantExpressionTokenObject = TokenObject(TokenType::EXPRESSION, "1");
TokenObject eleven_constantSubexpressionTokenObject = TokenObject(TokenType::SUBEXPRESSION, "11");

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
TokenObject newa_nameTokenObject = TokenObject(TokenType::NAME, "newa");
TokenObject capital_nameTokenObject = TokenObject(TokenType::NAME, "Statement");
TokenObject capitalEntity_nameTokenObject = TokenObject(TokenType::NAME, "Variable");

TokenObject six_intTokenObject = TokenObject(TokenType::INTEGER, "6");
TokenObject fourteen_intTokenObject = TokenObject(TokenType::INTEGER, "14");

#endif //SPA_REUSABLETOKENS_H
