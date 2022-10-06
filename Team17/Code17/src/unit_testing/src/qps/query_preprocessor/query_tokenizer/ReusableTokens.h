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
TokenObject booleanTokenObject = TokenObject(TokenType::BOOLEAN, "BOOLEAN");
TokenObject withTokenObject = TokenObject(TokenType::WITH, "with");
TokenObject equalsTokenObject = TokenObject(TokenType::EQUALS, "=");

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
TokenObject eleven_constantSubexpressionTokenObject = TokenObject(TokenType::SUBEXPRESSION, "11");
TokenObject subexpressionTokenObject1 = TokenObject(TokenType::SUBEXPRESSION, "(x+y)");
TokenObject subexpressionTokenObject2 = TokenObject(TokenType::SUBEXPRESSION, "((x+y))*(www/3)");
TokenObject subexpressionTokenObject3 = TokenObject(TokenType::SUBEXPRESSION, "((x1+y))*(1/3)");
TokenObject subexpressionTokenObject4 = TokenObject(TokenType::SUBEXPRESSION, "((x/(s-y)))*(www/(3*(2/x)))");

TokenObject one_constantExpressionTokenObject = TokenObject(TokenType::EXPRESSION, "1");
TokenObject expressionTokenObject1 = TokenObject(TokenType::EXPRESSION, "(x+y)");
TokenObject expressionTokenObject2 = TokenObject(TokenType::EXPRESSION, "((x+y))*(www/3)");
TokenObject expressionTokenObject3 = TokenObject(TokenType::EXPRESSION, "((x1+y))*(1/3)");
TokenObject expressionTokenObject4 = TokenObject(TokenType::EXPRESSION, "((x/(s-y)))*(www/(3*(2/x)))");

TokenObject attributeTokenObject1 = TokenObject(TokenType::ATTRIBUTE, "a.stmt#");
TokenObject attributeTokenObject2 = TokenObject(TokenType::ATTRIBUTE, "procName.procName");
TokenObject attributeTokenObject3 = TokenObject(TokenType::ATTRIBUTE, "c.value");
TokenObject attributeTokenObject4 = TokenObject(TokenType::ATTRIBUTE, "procName.varName");
TokenObject attributeTokenObject5 = TokenObject(TokenType::ATTRIBUTE, "s.stmt#");
TokenObject attributeTokenObject6 = TokenObject(TokenType::ATTRIBUTE, "s1.stmt#");

TokenObject oneSyn_tupleTokenObject = TokenObject(TokenType::TUPLE, "<a1>");
TokenObject twoSyn_tupleTokenObject = TokenObject(TokenType::TUPLE, "<a1,a2>");
TokenObject threeSyn_tupleTokenObject = TokenObject(TokenType::TUPLE, "<a,a1,a2>");
TokenObject attriSyn_tupleTokenObject1 = TokenObject(TokenType::TUPLE, "<a.stmt#,a1,a2>");
TokenObject attriSyn_tupleTokenObject2 = TokenObject(TokenType::TUPLE, "<a,p.procName,a2>");
TokenObject fourAttri_tupleTokenObject = TokenObject(TokenType::TUPLE, "<a.stmt#,p.procName,c.value,v.varName>");
TokenObject oneAttri_tupleTokenObject = TokenObject(TokenType::TUPLE, "<p.procName>");

TokenObject v_nameTokenObject = TokenObject(TokenType::NAME, "v");
TokenObject v1_nameTokenObject = TokenObject(TokenType::NAME, "v1");
TokenObject s_nameTokenObject = TokenObject(TokenType::NAME, "s");
TokenObject s1_nameTokenObject = TokenObject(TokenType::NAME, "s1");
TokenObject p_nameTokenObject = TokenObject(TokenType::NAME, "p");
TokenObject q_nameTokenObject = TokenObject(TokenType::NAME, "q");
TokenObject a_nameTokenObject = TokenObject(TokenType::NAME, "a");
TokenObject a1_nameTokenObject = TokenObject(TokenType::NAME, "a1");
TokenObject a2_nameTokenObject = TokenObject(TokenType::NAME, "a2");
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
