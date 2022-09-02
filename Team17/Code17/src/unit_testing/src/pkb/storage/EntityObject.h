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
#include "models/Entity/StatementListEntity.h"
#include "models/Entity/VariableEntity.h"
#include "models/Entity/WhileEntity.h"

std::string value_one = "value_one";
std::string value_two = "value_two";
std::string value_three = "value_three";

Entity* entity = new Entity(value_one);
Entity* assignEntity = new AssignEntity(value_one);
Entity* callEntity = new CallEntity(value_one);
Entity* constantEntity = new ConstantEntity(value_one);
Entity* ifEntity = new IfEntity(value_one);
Entity* printEntity = new PrintEntity(value_one);
Entity* procedureEntity = new ProcedureEntity(value_one);
Entity* readEntity = new ReadEntity(value_one);
Entity* variableEntity = new VariableEntity(value_one);
Entity* whileEntity = new WhileEntity(value_one);

Entity* assignEntityTwo = new AssignEntity(value_two);
Entity* callEntityTwo = new CallEntity(value_two);
Entity* constantEntityTwo = new ConstantEntity(value_two);
Entity* ifEntityTwo = new IfEntity(value_two);
Entity* printEntityTwo = new PrintEntity(value_two);
Entity* procedureEntityTwo = new ProcedureEntity(value_two);
Entity* readEntityTwo = new ReadEntity(value_two);
Entity* variableEntityTwo = new VariableEntity(value_two);
Entity* whileEntityTwo = new WhileEntity(value_two);

Entity* assignEntityThree = new AssignEntity(value_three);
Entity* callEntityThree = new CallEntity(value_three);
Entity* constantEntityThree = new ConstantEntity(value_three);
Entity* ifEntityThree = new IfEntity(value_three);
Entity* printEntityThree = new PrintEntity(value_three);
Entity* procedureEntityThree = new ProcedureEntity(value_three);
Entity* readEntityThree = new ReadEntity(value_three);
Entity* variableEntityThree = new VariableEntity(value_three);
Entity* whileEntityThree = new WhileEntity(value_three);
