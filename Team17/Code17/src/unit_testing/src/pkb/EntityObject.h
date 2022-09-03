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

static std::string value_one = "value_one";
static std::string value_two = "value_two";
static std::string value_three = "value_three";

static Entity* entity = new Entity(value_one);
static Entity* assignEntity = new AssignEntity(value_one);
static Entity* callEntity = new CallEntity(value_one);
static Entity* constantEntity = new ConstantEntity(value_one);
static Entity* ifEntity = new IfEntity(value_one);
static Entity* printEntity = new PrintEntity(value_one);
static Entity* procedureEntity = new ProcedureEntity(value_one);
static Entity* readEntity = new ReadEntity(value_one);
static Entity* variableEntity = new VariableEntity(value_one);
static Entity* whileEntity = new WhileEntity(value_one);

static Entity* assignEntityTwo = new AssignEntity(value_two);
static Entity* callEntityTwo = new CallEntity(value_two);
static Entity* constantEntityTwo = new ConstantEntity(value_two);
static Entity* ifEntityTwo = new IfEntity(value_two);
static Entity* printEntityTwo = new PrintEntity(value_two);
static Entity* procedureEntityTwo = new ProcedureEntity(value_two);
static Entity* readEntityTwo = new ReadEntity(value_two);
static Entity* variableEntityTwo = new VariableEntity(value_two);
static Entity* whileEntityTwo = new WhileEntity(value_two);

static Entity* assignEntityThree = new AssignEntity(value_three);
static Entity* callEntityThree = new CallEntity(value_three);
static Entity* constantEntityThree = new ConstantEntity(value_three);
static Entity* ifEntityThree = new IfEntity(value_three);
static Entity* printEntityThree = new PrintEntity(value_three);
static Entity* procedureEntityThree = new ProcedureEntity(value_three);
static Entity* readEntityThree = new ReadEntity(value_three);
static Entity* variableEntityThree = new VariableEntity(value_three);
static Entity* whileEntityThree = new WhileEntity(value_three);
