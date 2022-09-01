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

    Entity leftEntity = Entity(leftValue);
    Entity rightEntity = Entity(rightValue);
   
    Relationship relationship = Relationship(leftEntity, rightEntity);
    REQUIRE(relationship.getLeftEntity() == leftEntity);
    REQUIRE(relationship.getRightEntity() == rightEntity);
}

TEST_CASE("Uses Relationship Test") {
    std::string assignValue = "1";
    std::string varAssignValue = "variableA";
    Entity assignEntity = AssignEntity(assignValue);
    Entity varAssignEntity = VariableEntity(varAssignValue);
    Relationship assignUsesRelationship = UsesRelationship(assignEntity, varAssignEntity);

    std::string whileValue = "2";
    std::string varWhileValue = "variableB";
    Entity whileEntity = WhileEntity(whileValue);
    Entity varWhileEntity = VariableEntity(varWhileValue);
    Relationship whileUsesRelationship = UsesRelationship(whileEntity, varWhileEntity);

    std::string ifValue = "3";
    std::string varIfValue = "variableC";
    Entity ifEntity = IfEntity(ifValue);
    Entity varIfEntity = VariableEntity(varIfValue);
    Relationship ifUsesRelationship = UsesRelationship(ifEntity, varIfEntity);

    std::string printValue = "4";
    std::string varPrintValue = "variableD";
    Entity printEntity = PrintEntity(printValue);
    Entity varPrintEntity = VariableEntity(varPrintValue);
    Relationship printUsesRelationship = UsesRelationship(printEntity, varPrintEntity);

    std::string procedureValue = "main";
    std::string varProcedureValue = "variableE";
    Entity procedureEntity = ProcedureEntity(procedureValue);
    Entity varProcedureEntity = VariableEntity(varProcedureValue);
    Relationship procedureUsesRelationship = UsesRelationship(procedureEntity, varProcedureEntity);

    REQUIRE(assignUsesRelationship.getLeftEntity() == assignEntity);
    REQUIRE(assignUsesRelationship.getRightEntity() == varAssignEntity);

    REQUIRE(whileUsesRelationship.getLeftEntity() == whileEntity);
    REQUIRE(whileUsesRelationship.getRightEntity() == varWhileEntity);

    REQUIRE(ifUsesRelationship.getLeftEntity() == ifEntity);
    REQUIRE(ifUsesRelationship.getRightEntity() == varIfEntity);

    REQUIRE(printUsesRelationship.getLeftEntity() == printEntity);
    REQUIRE(printUsesRelationship.getRightEntity() == varPrintEntity);

    REQUIRE(procedureUsesRelationship.getLeftEntity() == procedureEntity);
    REQUIRE(procedureUsesRelationship.getRightEntity() == varProcedureEntity);
}

TEST_CASE("Modify Relationship Test") {
    std::string assignValue = "1";
    std::string varAssignValue = "variableA";
    Entity assignEntity = AssignEntity(assignValue);
    Entity varAssignEntity = VariableEntity(varAssignValue);
    Relationship assignModifyRelationship = ModifyRelationship(assignEntity, varAssignEntity);

    std::string whileValue = "2";
    std::string varWhileValue = "variableB";
    Entity whileEntity = WhileEntity(whileValue);
    Entity varWhileEntity = VariableEntity(varWhileValue);
    Relationship whileModifyRelationship = ModifyRelationship(whileEntity, varWhileEntity);

    std::string ifValue = "3";
    std::string varIfValue = "variableC";
    Entity ifEntity = IfEntity(ifValue);
    Entity varIfEntity = VariableEntity(varIfValue);
    Relationship ifModifyRelationship = ModifyRelationship(ifEntity, varIfEntity);

    std::string readValue = "4";
    std::string varReadValue = "variableD";
    Entity readEntity = ReadEntity(readValue);
    Entity varReadEntity = VariableEntity(varReadValue);
    Relationship readModifyRelationship = ModifyRelationship(readEntity, varReadEntity);

    std::string procedureValue = "main";
    std::string varProcedureValue = "variableE";
    Entity procedureEntity = ProcedureEntity(procedureValue);
    Entity varProcedureEntity = VariableEntity(varProcedureValue);
    Relationship procedureModifyRelationship = ModifyRelationship(procedureEntity, varProcedureEntity);

    REQUIRE(assignModifyRelationship.getLeftEntity() == assignEntity);
    REQUIRE(assignModifyRelationship.getRightEntity() == varAssignEntity);

    REQUIRE(whileModifyRelationship.getLeftEntity() == whileEntity);
    REQUIRE(whileModifyRelationship.getRightEntity() == varWhileEntity);

    REQUIRE(ifModifyRelationship.getLeftEntity() == ifEntity);
    REQUIRE(ifModifyRelationship.getRightEntity() == varIfEntity);

    REQUIRE(readModifyRelationship.getLeftEntity() == readEntity);
    REQUIRE(readModifyRelationship.getRightEntity() == varReadEntity);

    REQUIRE(procedureModifyRelationship.getLeftEntity() == procedureEntity);
    REQUIRE(procedureModifyRelationship.getRightEntity() == varProcedureEntity);
}
