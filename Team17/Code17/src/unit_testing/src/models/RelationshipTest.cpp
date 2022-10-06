#include "models/Relationship/Relationship.h"
#include "models/Relationship/ModifyRelationship.h"
#include "models/Relationship/UsesRelationship.h"
#include "models/Relationship/ParentRelationship.h"
#include "models/Relationship/ParentTRelationship.h"
#include "models/Relationship/FollowsRelationship.h"
#include "models/Relationship/FollowsTRelationship.h"
#include "models/Relationship/NextRelationship.h"
#include "models/Relationship/CallsRelationship.h"
#include "models/Relationship/CallsTRelationship.h"

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

TEST_CASE("ParentT Relationship Test") {
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

    Relationship* whileAssignRel = new ParentTRelationship(whileEntity, assignEntity);
    Relationship* whileReadRel = new ParentTRelationship(whileEntity, readEntity);
    Relationship* whilePrintRel = new ParentTRelationship(whileEntity, printEntity);
    Relationship* whileCallRel = new ParentTRelationship(whileEntity, callEntity);
    Relationship* whileWhileRel = new ParentTRelationship(whileEntity, whileEntity2);
    Relationship* whileIfRel = new ParentTRelationship(whileEntity, ifEntity);

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

    Relationship* ifAssignRel = new ParentTRelationship(ifEntity, assignEntity);
    Relationship* ifReadRel = new ParentTRelationship(ifEntity, readEntity);
    Relationship* ifPrintRel = new ParentTRelationship(ifEntity, printEntity);
    Relationship* ifCallRel = new ParentTRelationship(ifEntity, callEntity);
    Relationship* ifWhileRel = new ParentTRelationship(ifEntity, whileEntity);
    Relationship* ifIfRel = new ParentTRelationship(ifEntity, ifEntity2);

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
    Relationship* readIfRel = new FollowsRelationship(readEntity, ifEntity);
    Relationship* assignPrintRel = new FollowsRelationship(assignEntity, printEntity);
    Relationship* printCallRel = new FollowsRelationship(printEntity, callEntity);
    Relationship* callWhileRel = new FollowsRelationship(callEntity, whileEntity);
    Relationship* ifReadRel = new FollowsRelationship(whileEntity, readEntity);

    REQUIRE(*(whileAssignRel->getLeftEntity()) == *whileEntity);
    REQUIRE(*(readIfRel->getLeftEntity()) == *readEntity);
    REQUIRE(*(assignPrintRel->getLeftEntity()) == *assignEntity);
    REQUIRE(*(printCallRel->getLeftEntity()) == *printEntity);
    REQUIRE(*(callWhileRel->getLeftEntity()) == *callEntity);
    REQUIRE(*(ifReadRel->getLeftEntity()) == *whileEntity);

    REQUIRE(*(whileAssignRel->getRightEntity()) == *assignEntity);
    REQUIRE(*(readIfRel->getRightEntity()) == *ifEntity);
    REQUIRE(*(assignPrintRel->getRightEntity()) == *printEntity);
    REQUIRE(*(printCallRel->getRightEntity()) == *callEntity);
    REQUIRE(*(callWhileRel->getRightEntity()) == *whileEntity);
    REQUIRE(*(ifReadRel->getRightEntity()) == *readEntity);
}

TEST_CASE("FollowsT Relationship Test") {
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

    Relationship* whileAssignRel = new FollowsTRelationship(whileEntity, assignEntity);
    Relationship* readIfRel = new FollowsTRelationship(readEntity, ifEntity);
    Relationship* assignPrintRel = new FollowsTRelationship(assignEntity, printEntity);
    Relationship* printCallRel = new FollowsTRelationship(printEntity, callEntity);
    Relationship* callWhileRel = new FollowsTRelationship(callEntity, whileEntity);
    Relationship* ifReadRel = new FollowsTRelationship(whileEntity, readEntity);

    REQUIRE(*(whileAssignRel->getLeftEntity()) == *whileEntity);
    REQUIRE(*(readIfRel->getLeftEntity()) == *readEntity);
    REQUIRE(*(assignPrintRel->getLeftEntity()) == *assignEntity);
    REQUIRE(*(printCallRel->getLeftEntity()) == *printEntity);
    REQUIRE(*(callWhileRel->getLeftEntity()) == *callEntity);
    REQUIRE(*(ifReadRel->getLeftEntity()) == *whileEntity);

    REQUIRE(*(whileAssignRel->getRightEntity()) == *assignEntity);
    REQUIRE(*(readIfRel->getRightEntity()) == *ifEntity);
    REQUIRE(*(assignPrintRel->getRightEntity()) == *printEntity);
    REQUIRE(*(printCallRel->getRightEntity()) == *callEntity);
    REQUIRE(*(callWhileRel->getRightEntity()) == *whileEntity);
    REQUIRE(*(ifReadRel->getRightEntity()) == *readEntity);
}

TEST_CASE("Next Relationship Test") {
    std::string whileValue = "1";
    std::string ifValue = "2";
    std::string assignValue = "3";
    std::string readValue = "4";
    std::string printValue = "5";
    std::string callValue = "6";

    Entity* whileEntity = new WhileEntity(whileValue);
    Entity* ifEntity = new IfEntity(ifValue);
    Entity* readEntity = new ReadEntity(readValue);
    Entity* printEntity = new PrintEntity(printValue);
    Entity* assignEntity = new AssignEntity(ifValue);
    Entity* callEntity = new CallEntity(callValue);

    Relationship* whileAssignRel = new NextRelationship(whileEntity, assignEntity);
    Relationship* readIfRel = new NextRelationship(readEntity, ifEntity);
    Relationship* assignPrintRel = new NextRelationship(assignEntity, printEntity);
    Relationship* printCallRel = new NextRelationship(printEntity, callEntity);
    Relationship* callWhileRel = new NextRelationship(callEntity, whileEntity);
    Relationship* ifReadRel = new NextRelationship(whileEntity, readEntity);

    REQUIRE(*(whileAssignRel->getLeftEntity()) == *whileEntity);
    REQUIRE(*(readIfRel->getLeftEntity()) == *readEntity);
    REQUIRE(*(assignPrintRel->getLeftEntity()) == *assignEntity);
    REQUIRE(*(printCallRel->getLeftEntity()) == *printEntity);
    REQUIRE(*(callWhileRel->getLeftEntity()) == *callEntity);
    REQUIRE(*(ifReadRel->getLeftEntity()) == *whileEntity);

    REQUIRE(*(whileAssignRel->getRightEntity()) == *assignEntity);
    REQUIRE(*(readIfRel->getRightEntity()) == *ifEntity);
    REQUIRE(*(assignPrintRel->getRightEntity()) == *printEntity);
    REQUIRE(*(printCallRel->getRightEntity()) == *callEntity);
    REQUIRE(*(callWhileRel->getRightEntity()) == *whileEntity);
    REQUIRE(*(ifReadRel->getRightEntity()) == *readEntity);
}

TEST_CASE("Calls Relationship Test") {
    std::string procValue1 = "proc1";
    std::string procValue2 = "proc2";
    std::string procValue3 = "proc3";
    std::string procValue4 = "proc4";

    Entity* procEntity1 = new ProcedureEntity(procValue1);
    Entity* procEntity2 = new ProcedureEntity(procValue2);
    Entity* procEntity3 = new ProcedureEntity(procValue3);
    Entity* procEntity4 = new ProcedureEntity(procValue4);

    Relationship* callsRel1 = new CallsRelationship(procEntity1, procEntity2);
    Relationship* callsRel2 = new CallsRelationship(procEntity2, procEntity3);
    Relationship* callsRel3 = new CallsRelationship(procEntity3, procEntity4);

    REQUIRE(*(callsRel1->getLeftEntity()) == *procEntity1);
    REQUIRE(*(callsRel2->getLeftEntity()) == *procEntity2);
    REQUIRE(*(callsRel3->getLeftEntity()) == *procEntity3);

    REQUIRE(*(callsRel1->getRightEntity()) == *procEntity2);
    REQUIRE(*(callsRel2->getRightEntity()) == *procEntity3);
    REQUIRE(*(callsRel3->getRightEntity()) == *procEntity4);
}

TEST_CASE("CallsT Relationship Test") {
    std::string procValue1 = "proc1";
    std::string procValue2 = "proc2";
    std::string procValue3 = "proc3";
    std::string procValue4 = "proc4";

    Entity* procEntity1 = new ProcedureEntity(procValue1);
    Entity* procEntity2 = new ProcedureEntity(procValue2);
    Entity* procEntity3 = new ProcedureEntity(procValue3);
    Entity* procEntity4 = new ProcedureEntity(procValue4);

    Relationship* callsTRel1 = new CallsTRelationship(procEntity1, procEntity2);
    Relationship* callsTRel2 = new CallsTRelationship(procEntity2, procEntity3);
    Relationship* callsTRel3 = new CallsTRelationship(procEntity3, procEntity4);

    REQUIRE(*(callsTRel1->getLeftEntity()) == *procEntity1);
    REQUIRE(*(callsTRel2->getLeftEntity()) == *procEntity2);
    REQUIRE(*(callsTRel3->getLeftEntity()) == *procEntity3);

    REQUIRE(*(callsTRel1->getRightEntity()) == *procEntity2);
    REQUIRE(*(callsTRel2->getRightEntity()) == *procEntity3);
    REQUIRE(*(callsTRel3->getRightEntity()) == *procEntity4);
}
