#pragma once
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "EntityObject.h"

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
static TokenObject procedureTokenObject = TokenObject(TokenType::NAME_WITH_QUOTATION, procedure_value_one);
static TokenObject variableTokenObject = TokenObject(TokenType::NAME_WITH_QUOTATION, variable_value_one);
static TokenObject procedureTokenObjectTwo = TokenObject(TokenType::NAME_WITH_QUOTATION, procedure_value_two);
static TokenObject variableTokenObjectTwo = TokenObject(TokenType::NAME_WITH_QUOTATION, variable_value_two);
static TokenObject procedureTokenObjectThree = TokenObject(TokenType::NAME_WITH_QUOTATION, procedure_value_three);
static TokenObject variableTokenObjectThree = TokenObject(TokenType::NAME_WITH_QUOTATION, variable_value_three);
