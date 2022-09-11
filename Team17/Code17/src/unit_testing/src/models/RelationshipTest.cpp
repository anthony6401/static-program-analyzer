#include "models/Relationship/Relationship.h"
#include "models/Relationship/ModifyRelationship.h"
#include "models/Relationship/UsesRelationship.h"
#include "models/Relationship/ParentRelationship.h"
#include "models/Relationship/FollowsRelationship.h"

#include "models/Entity/Entity.h"
#include "models/Entity/AssignEntity.h"
#include "models/Entity/CallEntity.h"
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

TEST_CASE("Parent Relationship Test") {
    std::string whileValue = "1";
    std::string ifValue = "2";

    std::string assignValue = "3";
    std::string readValue = "4";
    std::string printValue = "5";
    std::string callValue = "6";
    std::string whileValue2 = "7";
    std::string ifValue2 = "8";
    
    Entity* whileEntity = new WhileEntity(whileValue);
    Entity* ifEntity =  new IfEntity(ifValue);

    Entity* readEntity = new ReadEntity(readValue);
    Entity* printEntity = new PrintEntity(printValue);
    Entity* assignEntity = new AssignEntity(ifValue);
    Entity* callEntity = new CallEntity(callValue);
    Entity* whileEntity2 = new WhileEntity(whileValue2);
    Entity* ifEntity2= new IfEntity(ifValue2);

    Relationship* whileAssignRel = new ParentRelationship(whileEntity, assignEntity);
    Relationship* whileReadRel = new ParentRelationship(whileEntity, readEntity);
    Relationship* whilePrintRel = new ParentRelationship(whileEntity, printEntity);
    Relationship* whileCallRel = new ParentRelationship(whileEntity, callEntity);
    Relationship* whileWhileRel = new ParentRelationship(whileEntity, whileEntity2);
    Relationship* whileIfRel = new ParentRelationship(whileEntity, ifEntity);

    REQUIRE(*(whileAssignRel->getLeftEntity()) == *whileEntity);
    REQUIRE(*(whileReadRel->getLeftEntity()) == *whileEntity);
    REQUIRE(*(whilePrintRel->getLeftEntity()) == *whileEntity);
    REQUIRE(*(whileCallRel->getLeftEntity()) == *whileEntity);
    REQUIRE(*(whileWhileRel->getLeftEntity()) == *whileEntity);
    REQUIRE(*(whileIfRel->getLeftEntity()) == *whileEntity);

    REQUIRE(*(whileAssignRel->getRightEntity()) == *assignEntity);
    REQUIRE(*(whileReadRel->getRightEntity()) == *readEntity);
    REQUIRE(*(whilePrintRel->getRightEntity()) == *printEntity);
    REQUIRE(*(whileCallRel->getRightEntity()) == *callEntity);
    REQUIRE(*(whileWhileRel->getRightEntity()) == *whileEntity2);
    REQUIRE(*(whileIfRel->getRightEntity()) == *ifEntity);

    Relationship* ifAssignRel = new ParentRelationship(ifEntity, assignEntity);
    Relationship* ifReadRel = new ParentRelationship(ifEntity, readEntity);
    Relationship* ifPrintRel = new ParentRelationship(ifEntity, printEntity);
    Relationship* ifCallRel = new ParentRelationship(ifEntity, callEntity);
    Relationship* ifWhileRel = new ParentRelationship(ifEntity, whileEntity);
    Relationship* ifIfRel = new ParentRelationship(ifEntity, ifEntity2);

    REQUIRE(*(ifAssignRel->getLeftEntity()) == *ifEntity);
    REQUIRE(*(ifReadRel->getLeftEntity()) == *ifEntity);
    REQUIRE(*(ifPrintRel->getLeftEntity()) == *ifEntity);
    REQUIRE(*(ifCallRel->getLeftEntity()) == *ifEntity);
    REQUIRE(*(ifWhileRel->getLeftEntity()) == *ifEntity);
    REQUIRE(*(ifIfRel->getLeftEntity()) == *ifEntity);

    REQUIRE(*(ifAssignRel->getRightEntity()) == *assignEntity);
    REQUIRE(*(ifReadRel->getRightEntity()) == *readEntity);
    REQUIRE(*(ifPrintRel->getRightEntity()) == *printEntity);
    REQUIRE(*(ifCallRel->getRightEntity()) == *callEntity);
    REQUIRE(*(ifWhileRel->getRightEntity()) == *whileEntity);
    REQUIRE(*(ifIfRel->getRightEntity()) == *ifEntity2);
}


TEST_CASE("Follows Relationship Test") {
    std::string whileValue = "1";
    std::string ifValue = "2";

    std::string assignValue = "3";
    std::string readValue = "4";
    std::string printValue = "5";
    std::string callValue = "6";
    std::string whileValue2 = "7";
    std::string ifValue2 = "8";

    Entity* whileEntity = new WhileEntity(whileValue);
    Entity* ifEntity = new IfEntity(ifValue);

    Entity* readEntity = new ReadEntity(readValue);
    Entity* printEntity = new PrintEntity(printValue);
    Entity* assignEntity = new AssignEntity(ifValue);
    Entity* callEntity = new CallEntity(callValue);
    Entity* whileEntity2 = new WhileEntity(whileValue2);
    Entity* ifEntity2 = new IfEntity(ifValue2);

    Relationship* whileAssignRel = new FollowsRelationship(whileEntity, assignEntity);
    Relationship* whileReadRel = new FollowsRelationship(whileEntity, readEntity);
    Relationship* whilePrintRel = new FollowsRelationship(whileEntity, printEntity);
    Relationship* whileCallRel = new FollowsRelationship(whileEntity, callEntity);
    Relationship* whileWhileRel = new FollowsRelationship(whileEntity, whileEntity2);
    Relationship* whileIfRel = new FollowsRelationship(whileEntity, ifEntity);

    REQUIRE(*(whileAssignRel->getLeftEntity()) == *whileEntity);
    REQUIRE(*(whileReadRel->getLeftEntity()) == *whileEntity);
    REQUIRE(*(whilePrintRel->getLeftEntity()) == *whileEntity);
    REQUIRE(*(whileCallRel->getLeftEntity()) == *whileEntity);
    REQUIRE(*(whileWhileRel->getLeftEntity()) == *whileEntity);
    REQUIRE(*(whileIfRel->getLeftEntity()) == *whileEntity);

    REQUIRE(*(whileAssignRel->getRightEntity()) == *assignEntity);
    REQUIRE(*(whileReadRel->getRightEntity()) == *readEntity);
    REQUIRE(*(whilePrintRel->getRightEntity()) == *printEntity);
    REQUIRE(*(whileCallRel->getRightEntity()) == *callEntity);
    REQUIRE(*(whileWhileRel->getRightEntity()) == *whileEntity2);
    REQUIRE(*(whileIfRel->getRightEntity()) == *ifEntity);

    Relationship* ifAssignRel = new FollowsRelationship(ifEntity, assignEntity);
    Relationship* ifReadRel = new FollowsRelationship(ifEntity, readEntity);
    Relationship* ifPrintRel = new FollowsRelationship(ifEntity, printEntity);
    Relationship* ifCallRel = new FollowsRelationship(ifEntity, callEntity);
    Relationship* ifWhileRel = new FollowsRelationship(ifEntity, whileEntity);
    Relationship* ifIfRel = new FollowsRelationship(ifEntity, ifEntity2);

    REQUIRE(*(ifAssignRel->getLeftEntity()) == *ifEntity);
    REQUIRE(*(ifReadRel->getLeftEntity()) == *ifEntity);
    REQUIRE(*(ifPrintRel->getLeftEntity()) == *ifEntity);
    REQUIRE(*(ifCallRel->getLeftEntity()) == *ifEntity);
    REQUIRE(*(ifWhileRel->getLeftEntity()) == *ifEntity);
    REQUIRE(*(ifIfRel->getLeftEntity()) == *ifEntity);

    REQUIRE(*(ifAssignRel->getRightEntity()) == *assignEntity);
    REQUIRE(*(ifReadRel->getRightEntity()) == *readEntity);
    REQUIRE(*(ifPrintRel->getRightEntity()) == *printEntity);
    REQUIRE(*(ifCallRel->getRightEntity()) == *callEntity);
    REQUIRE(*(ifWhileRel->getRightEntity()) == *whileEntity);
    REQUIRE(*(ifIfRel->getRightEntity()) == *ifEntity2);
}
