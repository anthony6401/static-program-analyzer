#pragma once

#include "models/Entity/AssignEntity.h"
#include "models/Entity/CallEntity.h"
#include "models/Entity/ConstantEntity.h"
#include "models/Entity/Entity.h"
#include "models/Entity/IfEntity.h"
#include "models/Entity/PrintEntity.h"
#include "models/Entity/ProcedureEntity.h"
#include "models/Entity/ReadEntity.h"
#include "models/Entity/StatementEntity.h"
#include "models/Entity/VariableEntity.h"
#include "models/Entity/WhileEntity.h"

static std::string entity_value = "entity_value";
static std::string assign_value_one = "1";
static std::string call_value_one = "2";
static std::string constant_value_one = "100";
static std::string if_value_one = "3";
static std::string print_value_one = "4";
static std::string procedure_value_one = "procedure_value_one";
static std::string read_value_one = "5";
static std::string variable_value_one = "variable_value_one";
static std::string while_value_one = "6";
static std::string statement_value_one = "19";

static std::string assign_value_two = "7";
static std::string call_value_two = "8";
static std::string constant_value_two = "200";
static std::string if_value_two = "9";
static std::string print_value_two = "10";
static std::string procedure_value_two = "procedure_value_two";
static std::string read_value_two = "11";
static std::string variable_value_two = "variable_value_two";
static std::string while_value_two = "12";
static std::string statement_value_two = "20";

static std::string assign_value_three = "13";
static std::string call_value_three = "14";
static std::string constant_value_three = "300";
static std::string if_value_three = "15";
static std::string print_value_three = "16";
static std::string procedure_value_three = "procedure_value_three";
static std::string read_value_three = "17";
static std::string variable_value_three = "variable_value_three";
static std::string while_value_three = "18";
static std::string statement_value_three= "20";

static std::string procedure_value_four = "procedure_value_four";

static Entity* entity = new Entity(entity_value);
static Entity* assignEntity = new AssignEntity(assign_value_one);
static Entity* callEntity = new CallEntity(call_value_one, procedure_value_one);
static Entity* constantEntity = new ConstantEntity(constant_value_one);
static Entity* ifEntity = new IfEntity(if_value_one);
static Entity* printEntity = new PrintEntity(print_value_one, variable_value_one);
static Entity* procedureEntity = new ProcedureEntity(procedure_value_one);
static Entity* readEntity = new ReadEntity(read_value_one, variable_value_one);
static Entity* variableEntity = new VariableEntity(variable_value_one);
static Entity* whileEntity = new WhileEntity(while_value_one);
static Entity* statementEntity = new StatementEntity(statement_value_one);

static Entity* assignEntityTwo = new AssignEntity(assign_value_two);
static Entity* callEntityTwo = new CallEntity(call_value_two, procedure_value_two);
static Entity* constantEntityTwo = new ConstantEntity(constant_value_two);
static Entity* ifEntityTwo = new IfEntity(if_value_two);
static Entity* printEntityTwo = new PrintEntity(print_value_two, variable_value_two);
static Entity* procedureEntityTwo = new ProcedureEntity(procedure_value_two);
static Entity* readEntityTwo = new ReadEntity(read_value_two, variable_value_two);
static Entity* variableEntityTwo = new VariableEntity(variable_value_two);
static Entity* whileEntityTwo = new WhileEntity(while_value_two);
static Entity* statementEntityTwo = new StatementEntity(statement_value_two);

static Entity* assignEntityThree = new AssignEntity(assign_value_three);
static Entity* callEntityThree = new CallEntity(call_value_three, procedure_value_three);
static Entity* constantEntityThree = new ConstantEntity(constant_value_three);
static Entity* ifEntityThree = new IfEntity(if_value_three);
static Entity* printEntityThree = new PrintEntity(print_value_three, variable_value_three);
static Entity* procedureEntityThree = new ProcedureEntity(procedure_value_three);
static Entity* readEntityThree = new ReadEntity(read_value_three, variable_value_three);
static Entity* variableEntityThree = new VariableEntity(variable_value_three);
static Entity* whileEntityThree = new WhileEntity(while_value_three);
static Entity* statementEntityThree = new StatementEntity(statement_value_three);

static Entity* assignEntityDuplicate = new AssignEntity(assign_value_one);
static Entity* callEntityDuplicate = new CallEntity(call_value_one, procedure_value_one);
static Entity* constantEntityDuplicate = new ConstantEntity(constant_value_one);
static Entity* ifEntityDuplicate = new IfEntity(if_value_one);
static Entity* printEntityDuplicate = new PrintEntity(print_value_one, variable_value_one);
static Entity* procedureEntityDuplicate = new ProcedureEntity(procedure_value_one);
static Entity* readEntityDuplicate = new ReadEntity(read_value_one, variable_value_one);
static Entity* variableEntityDuplicate = new VariableEntity(variable_value_one);
static Entity* whileEntityDuplicate = new WhileEntity(while_value_one);

static Entity* assignEntityTwoDuplicate = new AssignEntity(assign_value_two);
static Entity* callEntityTwoDuplicate = new CallEntity(call_value_two, procedure_value_two);
static Entity* constantEntityTwoDuplicate = new ConstantEntity(constant_value_two);
static Entity* ifEntityTwoDuplicate = new IfEntity(if_value_two);
static Entity* printEntityTwoDuplicate = new PrintEntity(print_value_two, variable_value_two);
static Entity* procedureEntityTwoDuplicate = new ProcedureEntity(procedure_value_two);
static Entity* readEntityTwoDuplicate = new ReadEntity(read_value_two, variable_value_two);
static Entity* variableEntityTwoDuplicate = new VariableEntity(variable_value_two);
static Entity* whileEntityTwoDuplicate = new WhileEntity(while_value_two);

static Entity* assignEntityThreeDuplicate = new AssignEntity(assign_value_three);
static Entity* callEntityThreeDuplicate = new CallEntity(call_value_three, procedure_value_three);
static Entity* constantEntityThreeDuplicate = new ConstantEntity(constant_value_three);
static Entity* ifEntityThreeDuplicate = new IfEntity(if_value_three);
static Entity* printEntityThreeDuplicate = new PrintEntity(print_value_three, variable_value_three);
static Entity* procedureEntityThreeDuplicate = new ProcedureEntity(procedure_value_three);
static Entity* readEntityThreeDuplicate = new ReadEntity(read_value_three, variable_value_three);
static Entity* variableEntityThreeDuplicate = new VariableEntity(variable_value_three);
static Entity* whileEntityThreeDuplicate = new WhileEntity(while_value_three);