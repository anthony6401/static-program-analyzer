#pragma once
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "EntityObject.h"
#include "PatternObject.h"

static TokenObject stmtTokenObject1 = TokenObject(TokenType::INTEGER, assign_value_one);
static TokenObject stmtTokenObject2 = TokenObject(TokenType::INTEGER, call_value_one);
static TokenObject stmtTokenObject3 = TokenObject(TokenType::INTEGER, if_value_one);
static TokenObject stmtTokenObject4 = TokenObject(TokenType::INTEGER, print_value_one);
static TokenObject stmtTokenObject5 = TokenObject(TokenType::INTEGER, read_value_one);
static TokenObject stmtTokenObject6 = TokenObject(TokenType::INTEGER, while_value_one);
static TokenObject stmtTokenObject7 = TokenObject(TokenType::INTEGER, assign_value_two);
static TokenObject stmtTokenObject8 = TokenObject(TokenType::INTEGER, call_value_two);
static TokenObject stmtTokenObject9 = TokenObject(TokenType::INTEGER, if_value_two);
static TokenObject stmtTokenObject10 = TokenObject(TokenType::INTEGER, print_value_two);
static TokenObject stmtTokenObject11 = TokenObject(TokenType::INTEGER, read_value_two);
static TokenObject stmtTokenObject12 = TokenObject(TokenType::INTEGER, while_value_two);
static TokenObject stmtTokenObject13 = TokenObject(TokenType::INTEGER, assign_value_three);
static TokenObject stmtTokenObject14 = TokenObject(TokenType::INTEGER, call_value_three);
static TokenObject stmtTokenObject15 = TokenObject(TokenType::INTEGER, if_value_three);
static TokenObject stmtTokenObject16 = TokenObject(TokenType::INTEGER, print_value_three);
static TokenObject stmtTokenObject17 = TokenObject(TokenType::INTEGER, read_value_three);
static TokenObject stmtTokenObject18 = TokenObject(TokenType::INTEGER, while_value_three);
static TokenObject stmtTokenObject19 = TokenObject(TokenType::INTEGER, statement_value_one);
static TokenObject procedureTokenObject = TokenObject(TokenType::NAME_WITH_QUOTATION, procedure_value_one);
static TokenObject variableTokenObject = TokenObject(TokenType::NAME_WITH_QUOTATION, variable_value_one);
static TokenObject procedureTokenObjectTwo = TokenObject(TokenType::NAME_WITH_QUOTATION, procedure_value_two);
static TokenObject variableTokenObjectTwo = TokenObject(TokenType::NAME_WITH_QUOTATION, variable_value_two);
static TokenObject procedureTokenObjectThree = TokenObject(TokenType::NAME_WITH_QUOTATION, procedure_value_three);
static TokenObject variableTokenObjectThree = TokenObject(TokenType::NAME_WITH_QUOTATION, variable_value_three);
static TokenObject procedureTokenObjectFour = TokenObject(TokenType::NAME_WITH_QUOTATION, procedure_value_four);

static TokenObject assignPatternTokenObjectFirstOne = TokenObject(TokenType::NAME_WITH_QUOTATION, assignFirstValueOne);
static TokenObject assignPatternTokenObjectFirstTwo = TokenObject(TokenType::NAME_WITH_QUOTATION, assignFirstValueTwo);
static TokenObject assignPatternTokenObjectFirstThree = TokenObject(TokenType::NAME_WITH_QUOTATION, assignFirstValueThree);

static TokenObject assignPatternTokenObjectSecondOne = TokenObject(TokenType::EXPRESSION, assignSecondValueForTokenOne);
static TokenObject assignPatternTokenObjectSecondTwo = TokenObject(TokenType::EXPRESSION, assignSecondValueForTokenTwo);
static TokenObject assignPatternTokenObjectSecondThree = TokenObject(TokenType::EXPRESSION, assignSecondValueForTokenThree);

static TokenObject assignPatternTokenObjectSubexprOne = TokenObject(TokenType::SUBEXPRESSION, assignSubexprOne);
static TokenObject assignPatternTokenObjectSubexprTwo = TokenObject(TokenType::SUBEXPRESSION, assignSubexprTwo);
static TokenObject assignPatternTokenObjectSubexprThree = TokenObject(TokenType::SUBEXPRESSION, assignSubexprThree);

static TokenObject wildCardTokenObject = TokenObject(TokenType::WILDCARD, "");

static TokenObject ifPatternTokenObjectFirstOne = TokenObject(TokenType::NAME_WITH_QUOTATION, ifLineNumOne);
static TokenObject ifPatternTokenObjectFirstTwo = TokenObject(TokenType::NAME_WITH_QUOTATION, ifLineNumTwo);

static TokenObject whilePatternTokenObjectFirstOne = TokenObject(TokenType::NAME_WITH_QUOTATION, whileLineNumOne);
static TokenObject whilePatternTokenObjectFirstTwo = TokenObject(TokenType::NAME_WITH_QUOTATION, whileLineNumTwo);

