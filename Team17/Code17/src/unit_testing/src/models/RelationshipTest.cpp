#include "models/Relationship/Relationship.h"
#include "models/Relationship/ModifyRelationship.h"
#include "models/Relationship/UsesRelationship.h"
#include "models/Entity/Entity.h"
#include "models/Entity/AssignEntity.h"
#include "models/Entity/VariableEntity.h"
#include "models/Entity/WhileEntity.h"
#include "models/Entity/IfEntity.h"
#include "models/Entity/PrintEntity.h"
#include "models/Entity/ProcedureEntity.h"
#include "models/Entity/ReadEntity.h"

#include <catch.hpp>

// To be amended
TEST_CASE("Relationship Test") {
    std::string leftValue = "leftValue";
    std::string rightValue = "rightValue";

    Entity* leftEntity = new Entity(leftValue);
    Entity* rightEntity = new Entity(rightValue);
   
    Relationship* relationship = new Relationship(leftEntity, rightEntity);
    REQUIRE(*(relationship->getLeftEntity()) == *leftEntity);
    REQUIRE(*(relationship->getRightEntity()) == *rightEntity);
}

TEST_CASE("Uses Relationship Test") {
    std::string assignValue = "1";
    std::string varAssignValue = "variableA";
    Entity* assignEntity = new AssignEntity(assignValue);
    Entity* varAssignEntity = new VariableEntity(varAssignValue);
    Relationship* assignUsesRelationship = new UsesRelationship(assignEntity, varAssignEntity);

    std::string whileValue = "2";
    std::string varWhileValue = "variableB";
    Entity* whileEntity = new WhileEntity(whileValue);
    Entity* varWhileEntity = new VariableEntity(varWhileValue);
    Relationship* whileUsesRelationship = new UsesRelationship(whileEntity, varWhileEntity);

    std::string ifValue = "3";
    std::string varIfValue = "variableC";
    Entity* ifEntity = new IfEntity(ifValue);
    Entity* varIfEntity = new VariableEntity(varIfValue);
    Relationship* ifUsesRelationship = new UsesRelationship(ifEntity, varIfEntity);

    std::string printValue = "4";
    std::string varPrintValue = "variableD";
    Entity* printEntity = new PrintEntity(printValue);
    Entity* varPrintEntity = new VariableEntity(varPrintValue);
    Relationship* printUsesRelationship = new UsesRelationship(printEntity, varPrintEntity);

    std::string procedureValue = "main";
    std::string varProcedureValue = "variableE";
    Entity* procedureEntity = new ProcedureEntity(procedureValue);
    Entity* varProcedureEntity = new VariableEntity(varProcedureValue);
    Relationship* procedureUsesRelationship = new UsesRelationship(procedureEntity, varProcedureEntity);

    REQUIRE(*(assignUsesRelationship->getLeftEntity()) == *assignEntity);
    REQUIRE(*(assignUsesRelationship->getRightEntity()) == *varAssignEntity);

    REQUIRE(*(whileUsesRelationship->getLeftEntity()) == *whileEntity);
    REQUIRE(*(whileUsesRelationship->getRightEntity()) == *varWhileEntity);

    REQUIRE(*(ifUsesRelationship->getLeftEntity()) == *ifEntity);
    REQUIRE(*(ifUsesRelationship->getRightEntity()) == *varIfEntity);

    REQUIRE(*(printUsesRelationship->getLeftEntity()) == *printEntity);
    REQUIRE(*(printUsesRelationship->getRightEntity()) == *varPrintEntity);

    REQUIRE(*(procedureUsesRelationship->getLeftEntity()) == *procedureEntity);
    REQUIRE(*(procedureUsesRelationship->getRightEntity()) == *varProcedureEntity);
}

TEST_CASE("Modify Relationship Test") {
    std::string assignValue = "1";
    std::string varAssignValue = "variableA";
    Entity* assignEntity = new AssignEntity(assignValue);
    Entity* varAssignEntity = new VariableEntity(varAssignValue);
    Relationship* assignModifyRelationship = new ModifyRelationship(assignEntity, varAssignEntity);

    std::string whileValue = "2";
    std::string varWhileValue = "variableB";
    Entity* whileEntity = new WhileEntity(whileValue);
    Entity* varWhileEntity = new VariableEntity(varWhileValue);
    Relationship* whileModifyRelationship = new ModifyRelationship(whileEntity, varWhileEntity);

    std::string ifValue = "3";
    std::string varIfValue = "variableC";
    Entity* ifEntity = new IfEntity(ifValue);
    Entity* varIfEntity = new VariableEntity(varIfValue);
    Relationship* ifModifyRelationship = new ModifyRelationship(ifEntity, varIfEntity);

    std::string printValue = "4";
    std::string varReadValue = "variableD";
    Entity* readEntity = new ReadEntity(printValue);
    Entity* varReadEntity = new VariableEntity(varReadValue);
    Relationship* readModifyRelationship = new ModifyRelationship(readEntity, varReadEntity);

    std::string procedureValue = "main";
    std::string varProcedureValue = "variableE";
    Entity* procedureEntity = new ProcedureEntity(procedureValue);
    Entity* varProcedureEntity = new VariableEntity(varProcedureValue);
    Relationship* procedureModifyRelationship = new ModifyRelationship(procedureEntity, varProcedureEntity);

    REQUIRE(*(assignModifyRelationship->getLeftEntity()) == *assignEntity);
    REQUIRE(*(assignModifyRelationship->getRightEntity()) == *varAssignEntity);

    REQUIRE(*(whileModifyRelationship->getLeftEntity()) == *whileEntity);
    REQUIRE(*(whileModifyRelationship->getRightEntity()) == *varWhileEntity);

    REQUIRE(*(ifModifyRelationship->getLeftEntity()) == *ifEntity);
    REQUIRE(*(ifModifyRelationship->getRightEntity()) == *varIfEntity);

    REQUIRE(*(readModifyRelationship->getLeftEntity()) == *readEntity);
    REQUIRE(*(readModifyRelationship->getRightEntity()) == *varReadEntity);

    REQUIRE(*(procedureModifyRelationship->getLeftEntity()) == *procedureEntity);
    REQUIRE(*(procedureModifyRelationship->getRightEntity()) == *varProcedureEntity);
}
