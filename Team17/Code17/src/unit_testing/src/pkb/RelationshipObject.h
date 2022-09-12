#pragma once

#include "EntityObject.h"
#include "models/Relationship/Relationship.h"
#include "models/Relationship/UsesRelationship.h"
#include "models/Relationship/ModifyRelationship.h"
#include "models/Relationship/ParentRelationship.h"
#include "models/Relationship/ParentTRelationship.h"
#include "models/Relationship/FollowsRelationship.h"
#include "models/Relationship/FollowsTRelationship.h"

Relationship* usesRelationshipAssignOne = new UsesRelationship(assignEntity, variableEntity);
Relationship* usesRelationshipAssignTwo = new UsesRelationship(assignEntityTwo, variableEntityTwo);
Relationship* usesRelationshipAssignOneDuplicate = new UsesRelationship(assignEntityDuplicate, variableEntityThree);
Relationship* usesRelationshipAssignTwoDuplicate = new UsesRelationship(assignEntityTwoDuplicate, variableEntity);

Relationship* usesRelationshipProcOne = new UsesRelationship(procedureEntity, variableEntity);
Relationship* usesRelationshipProcTwo = new UsesRelationship(procedureEntityTwo, variableEntityTwo);
Relationship* usesRelationshipProcOneDuplicate = new UsesRelationship(procedureEntityDuplicate, variableEntityThree);
Relationship* usesRelationshipProcTwoDuplicate = new UsesRelationship(procedureEntityTwoDuplicate, variableEntity);

Relationship* usesRelationshipReadOne = new UsesRelationship(readEntity, variableEntity);
Relationship* usesRelationshipReadTwo = new UsesRelationship(readEntityTwo, variableEntityTwo);
Relationship* usesRelationshipReadOneDuplicate = new UsesRelationship(readEntityDuplicate, variableEntityThree);
Relationship* usesRelationshipReadTwoDuplicate = new UsesRelationship(readEntityTwoDuplicate, variableEntity);

Relationship* usesRelationshipPrintOne = new UsesRelationship(printEntity, variableEntity);
Relationship* usesRelationshipPrintTwo = new UsesRelationship(printEntityTwo, variableEntityTwo);
Relationship* usesRelationshipPrintOneDuplicate = new UsesRelationship(printEntityDuplicate, variableEntityThree);
Relationship* usesRelationshipPrintTwoDuplicate = new UsesRelationship(printEntityTwoDuplicate, variableEntity);

Relationship* usesRelationshipWhileOne = new UsesRelationship(whileEntity, variableEntity);
Relationship* usesRelationshipWhileTwo = new UsesRelationship(whileEntityTwo, variableEntityTwo);
Relationship* usesRelationshipWhileOneDuplicate = new UsesRelationship(whileEntityDuplicate, variableEntityThree);
Relationship* usesRelationshipWhileTwoDuplicate = new UsesRelationship(whileEntityTwoDuplicate, variableEntity);

Relationship* usesRelationshipIfOne = new UsesRelationship(ifEntity, variableEntity);
Relationship* usesRelationshipIfTwo = new UsesRelationship(ifEntityTwo, variableEntityTwo);
Relationship* usesRelationshipIfOneDuplicate = new UsesRelationship(ifEntityDuplicate, variableEntityThree);
Relationship* usesRelationshipIfTwoDuplicate = new UsesRelationship(ifEntityTwoDuplicate, variableEntity);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Relationship* modifyRelationshipAssignOne = new ModifyRelationship(assignEntity, variableEntity);
Relationship* modifyRelationshipAssignTwo = new ModifyRelationship(assignEntityTwo, variableEntityTwo);
Relationship* modifyRelationshipAssignOneDuplicate = new ModifyRelationship(assignEntityDuplicate, variableEntityThree);
Relationship* modifyRelationshipAssignTwoDuplicate = new ModifyRelationship(assignEntityTwoDuplicate, variableEntity);

Relationship* modifyRelationshipProcOne = new ModifyRelationship(procedureEntity, variableEntity);
Relationship* modifyRelationshipProcTwo = new ModifyRelationship(procedureEntityTwo, variableEntityTwo);
Relationship* modifyRelationshipProcOneDuplicate = new ModifyRelationship(procedureEntityDuplicate, variableEntityThree);
Relationship* modifyRelationshipProcTwoDuplicate = new ModifyRelationship(procedureEntityTwoDuplicate, variableEntity);

Relationship* modifyRelationshipReadOne = new ModifyRelationship(readEntity, variableEntity);
Relationship* modifyRelationshipReadTwo = new ModifyRelationship(readEntityTwo, variableEntityTwo);
Relationship* modifyRelationshipReadOneDuplicate = new ModifyRelationship(readEntityDuplicate, variableEntityThree);
Relationship* modifyRelationshipReadTwoDuplicate = new ModifyRelationship(readEntityTwoDuplicate, variableEntity);

Relationship* modifyRelationshipPrintOne = new ModifyRelationship(printEntity, variableEntity);
Relationship* modifyRelationshipPrintTwo = new ModifyRelationship(printEntityTwo, variableEntityTwo);
Relationship* modifyRelationshipPrintOneDuplicate = new ModifyRelationship(printEntityDuplicate, variableEntityThree);
Relationship* modifyRelationshipPrintTwoDuplicate = new ModifyRelationship(printEntityTwoDuplicate, variableEntity);

Relationship* modifyRelationshipWhileOne = new ModifyRelationship(whileEntity, variableEntity);
Relationship* modifyRelationshipWhileTwo = new ModifyRelationship(whileEntityTwo, variableEntityTwo);
Relationship* modifyRelationshipWhileOneDuplicate = new ModifyRelationship(whileEntityDuplicate, variableEntityThree);
Relationship* modifyRelationshipWhileTwoDuplicate = new ModifyRelationship(whileEntityTwoDuplicate, variableEntity);

Relationship* modifyRelationshipIfOne = new ModifyRelationship(ifEntity, variableEntity);
Relationship* modifyRelationshipIfTwo = new ModifyRelationship(ifEntityTwo, variableEntityTwo);
Relationship* modifyRelationshipIfOneDuplicate = new ModifyRelationship(ifEntityDuplicate, variableEntityThree);
Relationship* modifyRelationshipIfTwoDuplicate = new ModifyRelationship(ifEntityTwoDuplicate, variableEntity);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// While Entity
Relationship* parentRelationshipWhileReadOne = new ParentRelationship(whileEntity, readEntity);
Relationship* parentRelationshipWhileReadTwo = new ParentRelationship(whileEntityTwo, readEntityTwo);
Relationship* parentRelationshipWhileReadDupOne = new ParentRelationship(whileEntityDuplicate, readEntityDuplicate);
Relationship* parentRelationshipWhileReadDupTwo = new ParentRelationship(whileEntityTwoDuplicate, readEntityTwoDuplicate);

Relationship* parentRelationshipWhilePrintOne = new ParentRelationship(whileEntity, printEntity);
Relationship* parentRelationshipWhilePrintTwo = new ParentRelationship(whileEntityTwo, printEntityTwo);
Relationship* parentRelationshipWhilePrintDupOne = new ParentRelationship(whileEntityDuplicate, printEntityDuplicate);
Relationship* parentRelationshipWhilePrintDupTwo = new ParentRelationship(whileEntityTwoDuplicate, printEntityTwoDuplicate);

Relationship* parentRelationshipWhileAssignOne = new ParentRelationship(whileEntity, assignEntity);
Relationship* parentRelationshipWhileAssignTwo = new ParentRelationship(whileEntityTwo, assignEntityTwo);
Relationship* parentRelationshipWhileAssignDupOne = new ParentRelationship(whileEntityDuplicate, assignEntityDuplicate);
Relationship* parentRelationshipWhileAssignDupTwo = new ParentRelationship(whileEntityTwoDuplicate, assignEntityTwoDuplicate);

Relationship* parentRelationshipWhileCallOne = new ParentRelationship(whileEntity, callEntity);
Relationship* parentRelationshipWhileCallTwo = new ParentRelationship(whileEntityTwo, callEntityTwo);
Relationship* parentRelationshipWhileCallDupOne = new ParentRelationship(whileEntityDuplicate, callEntityDuplicate);
Relationship* parentRelationshipWhileCallDupTwo = new ParentRelationship(whileEntityTwoDuplicate, callEntityTwoDuplicate);

Relationship* parentRelationshipWhileWhileOne = new ParentRelationship(whileEntity, whileEntityTwo);
Relationship* parentRelationshipWhileWhileTwo = new ParentRelationship(whileEntityTwo, whileEntityThree);
Relationship* parentRelationshipWhileWhileDupOne = new ParentRelationship(whileEntityDuplicate, whileEntityTwoDuplicate);
Relationship* parentRelationshipWhileWhileDupTwo = new ParentRelationship(whileEntityTwoDuplicate, whileEntityThreeDuplicate);

Relationship* parentRelationshipWhileIfOne = new ParentRelationship(whileEntity, ifEntity);
Relationship* parentRelationshipWhileIfTwo = new ParentRelationship(whileEntityTwo, ifEntityTwo);
Relationship* parentRelationshipWhileIfDupOne = new ParentRelationship(whileEntityDuplicate, ifEntityDuplicate);
Relationship* parentRelationshipWhileIfDupTwo = new ParentRelationship(whileEntityTwoDuplicate, ifEntityTwoDuplicate);

// If Entity
Relationship* parentRelationshipIfReadOne = new ParentRelationship(ifEntity, readEntity);
Relationship* parentRelationshipIfReadTwo = new ParentRelationship(ifEntityTwo, readEntityTwo);
Relationship* parentRelationshipIfReadDupOne = new ParentRelationship(ifEntityDuplicate, readEntityDuplicate);
Relationship* parentRelationshipIfReadDupTwo = new ParentRelationship(ifEntityTwoDuplicate, readEntityTwoDuplicate);

Relationship* parentRelationshipIfPrintOne = new ParentRelationship(ifEntity, printEntity);
Relationship* parentRelationshipIfPrintTwo = new ParentRelationship(ifEntityTwo, printEntityTwo);
Relationship* parentRelationshipIfPrintDupOne = new ParentRelationship(ifEntityDuplicate, printEntityDuplicate);
Relationship* parentRelationshipIfPrintDupTwo = new ParentRelationship(ifEntityTwoDuplicate, printEntityTwoDuplicate);

Relationship* parentRelationshipIfAssignOne = new ParentRelationship(ifEntity, assignEntity);
Relationship* parentRelationshipIfAssignTwo = new ParentRelationship(ifEntityTwo, assignEntityTwo);
Relationship* parentRelationshipIfAssignDupOne = new ParentRelationship(ifEntityDuplicate, assignEntityDuplicate);
Relationship* parentRelationshipIfAssignDupTwo = new ParentRelationship(ifEntityTwoDuplicate, assignEntityTwoDuplicate);

Relationship* parentRelationshipIfCallOne = new ParentRelationship(ifEntity, callEntity);
Relationship* parentRelationshipIfCallTwo = new ParentRelationship(ifEntityTwo, callEntityTwo);
Relationship* parentRelationshipIfCallDupOne = new ParentRelationship(ifEntityDuplicate, callEntityDuplicate);
Relationship* parentRelationshipIfCallDupTwo = new ParentRelationship(ifEntityTwoDuplicate, callEntityTwoDuplicate);

Relationship* parentRelationshipIfWhileOne = new ParentRelationship(ifEntity, whileEntity);
Relationship* parentRelationshipIfWhileTwo = new ParentRelationship(ifEntityTwo, whileEntityTwo);
Relationship* parentRelationshipIfWhileDupOne = new ParentRelationship(ifEntityDuplicate, whileEntityDuplicate);
Relationship* parentRelationshipIfWhileDupTwo = new ParentRelationship(ifEntityTwoDuplicate, whileEntityTwoDuplicate);

Relationship* parentRelationshipIfIfOne = new ParentRelationship(ifEntity, ifEntityTwo);
Relationship* parentRelationshipIfIfTwo = new ParentRelationship(ifEntityTwo, ifEntityThree);
Relationship* parentRelationshipIfIfDupOne = new ParentRelationship(ifEntityDuplicate, ifEntityTwoDuplicate);
Relationship* parentRelationshipIfIfDupTwo = new ParentRelationship(ifEntityTwoDuplicate, ifEntityThreeDuplicate);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// While Entity
Relationship* parentTRelationshipWhileReadOne = new ParentTRelationship(whileEntity, readEntity);
Relationship* parentTRelationshipWhileReadTwo = new ParentTRelationship(whileEntityTwo, readEntityTwo);
Relationship* parentTRelationshipWhileReadDupOne = new ParentTRelationship(whileEntityDuplicate, readEntityDuplicate);
Relationship* parentTRelationshipWhileReadDupTwo = new ParentTRelationship(whileEntityTwoDuplicate, readEntityTwoDuplicate);

Relationship* parentTRelationshipWhilePrintOne = new ParentTRelationship(whileEntity, printEntity);
Relationship* parentTRelationshipWhilePrintTwo = new ParentTRelationship(whileEntityTwo, printEntityTwo);
Relationship* parentTRelationshipWhilePrintDupOne = new ParentTRelationship(whileEntityDuplicate, printEntityDuplicate);
Relationship* parentTRelationshipWhilePrintDupTwo = new ParentTRelationship(whileEntityTwoDuplicate, printEntityTwoDuplicate);

Relationship* parentTRelationshipWhileAssignOne = new ParentTRelationship(whileEntity, assignEntity);
Relationship* parentTRelationshipWhileAssignTwo = new ParentTRelationship(whileEntityTwo, assignEntityTwo);
Relationship* parentTRelationshipWhileAssignDupOne = new ParentTRelationship(whileEntityDuplicate, assignEntityDuplicate);
Relationship* parentTRelationshipWhileAssignDupTwo = new ParentTRelationship(whileEntityTwoDuplicate, assignEntityTwoDuplicate);

Relationship* parentTRelationshipWhileCallOne = new ParentTRelationship(whileEntity, callEntity);
Relationship* parentTRelationshipWhileCallTwo = new ParentTRelationship(whileEntityTwo, callEntityTwo);
Relationship* parentTRelationshipWhileCallDupOne = new ParentTRelationship(whileEntityDuplicate, callEntityDuplicate);
Relationship* parentTRelationshipWhileCallDupTwo = new ParentTRelationship(whileEntityTwoDuplicate, callEntityTwoDuplicate);

Relationship* parentTRelationshipWhileWhileOne = new ParentTRelationship(whileEntity, whileEntityTwo);
Relationship* parentTRelationshipWhileWhileTwo = new ParentTRelationship(whileEntityTwo, whileEntityThree);
Relationship* parentTRelationshipWhileWhileDupOne = new ParentTRelationship(whileEntityDuplicate, whileEntityTwoDuplicate);
Relationship* parentTRelationshipWhileWhileDupTwo = new ParentTRelationship(whileEntityTwoDuplicate, whileEntityThreeDuplicate);

Relationship* parentTRelationshipWhileIfOne = new ParentTRelationship(whileEntity, ifEntity);
Relationship* parentTRelationshipWhileIfTwo = new ParentTRelationship(whileEntityTwo, ifEntityTwo);
Relationship* parentTRelationshipWhileIfDupOne = new ParentTRelationship(whileEntityDuplicate, ifEntityDuplicate);
Relationship* parentTRelationshipWhileIfDupTwo = new ParentTRelationship(whileEntityTwoDuplicate, ifEntityTwoDuplicate);

// If Entity
Relationship* parentTRelationshipIfReadOne = new ParentTRelationship(ifEntity, readEntity);
Relationship* parentTRelationshipIfReadTwo = new ParentTRelationship(ifEntityTwo, readEntityTwo);
Relationship* parentTRelationshipIfReadDupOne = new ParentTRelationship(ifEntityDuplicate, readEntityDuplicate);
Relationship* parentTRelationshipIfReadDupTwo = new ParentTRelationship(ifEntityTwoDuplicate, readEntityTwoDuplicate);

Relationship* parentTRelationshipIfPrintOne = new ParentTRelationship(ifEntity, printEntity);
Relationship* parentTRelationshipIfPrintTwo = new ParentTRelationship(ifEntityTwo, printEntityTwo);
Relationship* parentTRelationshipIfPrintDupOne = new ParentTRelationship(ifEntityDuplicate, printEntityDuplicate);
Relationship* parentTRelationshipIfPrintDupTwo = new ParentTRelationship(ifEntityTwoDuplicate, printEntityTwoDuplicate);

Relationship* parentTRelationshipIfAssignOne = new ParentTRelationship(ifEntity, assignEntity);
Relationship* parentTRelationshipIfAssignTwo = new ParentTRelationship(ifEntityTwo, assignEntityTwo);
Relationship* parentTRelationshipIfAssignDupOne = new ParentTRelationship(ifEntityDuplicate, assignEntityDuplicate);
Relationship* parentTRelationshipIfAssignDupTwo = new ParentTRelationship(ifEntityTwoDuplicate, assignEntityTwoDuplicate);

Relationship* parentTRelationshipIfCallOne = new ParentTRelationship(ifEntity, callEntity);
Relationship* parentTRelationshipIfCallTwo = new ParentTRelationship(ifEntityTwo, callEntityTwo);
Relationship* parentTRelationshipIfCallDupOne = new ParentTRelationship(ifEntityDuplicate, callEntityDuplicate);
Relationship* parentTRelationshipIfCallDupTwo = new ParentTRelationship(ifEntityTwoDuplicate, callEntityTwoDuplicate);

Relationship* parentTRelationshipIfWhileOne = new ParentTRelationship(ifEntity, whileEntity);
Relationship* parentTRelationshipIfWhileTwo = new ParentTRelationship(ifEntityTwo, whileEntityTwo);
Relationship* parentTRelationshipIfWhileDupOne = new ParentTRelationship(ifEntityDuplicate, whileEntityDuplicate);
Relationship* parentTRelationshipIfWhileDupTwo = new ParentTRelationship(ifEntityTwoDuplicate, whileEntityTwoDuplicate);

Relationship* parentTRelationshipIfIfOne = new ParentTRelationship(ifEntity, ifEntityTwo);
Relationship* parentTRelationshipIfIfTwo = new ParentTRelationship(ifEntityTwo, ifEntityThree);
Relationship* parentTRelationshipIfIfDupOne = new ParentTRelationship(ifEntityDuplicate, ifEntityTwoDuplicate);
Relationship* parentTRelationshipIfIfDupTwo = new ParentTRelationship(ifEntityTwoDuplicate, ifEntityThreeDuplicate);


// Read Entity
Relationship* followsRelationshipReadReadOne = new FollowsRelationship(readEntity, readEntityTwo);
Relationship* followsRelationshipReadReadDupOne = new FollowsRelationship(readEntityDuplicate, readEntityTwoDuplicate);

Relationship* followsRelationshipReadPrintOne = new FollowsRelationship(readEntity, printEntity);
Relationship* followsRelationshipReadPrintDupOne = new FollowsRelationship(readEntityDuplicate, printEntityDuplicate);

Relationship* followsRelationshipReadAssignOne = new FollowsRelationship(readEntity, assignEntity);
Relationship* followsRelationshipReadAssignDupOne = new FollowsRelationship(readEntityDuplicate, assignEntityDuplicate);

Relationship* followsRelationshipReadCallOne = new FollowsRelationship(readEntity, callEntity);
Relationship* followsRelationshipReadCallDupOne = new FollowsRelationship(readEntityDuplicate, callEntityDuplicate);

Relationship* followsRelationshipReadWhileOne = new FollowsRelationship(readEntity, whileEntity);
Relationship* followsRelationshipReadWhileDupOne = new FollowsRelationship(readEntityDuplicate, whileEntityDuplicate);

Relationship* followsRelationshipReadIfOne = new FollowsRelationship(readEntity, ifEntity);
Relationship* followsRelationshipReadIfDupOne = new FollowsRelationship(readEntityDuplicate, ifEntityDuplicate);

// Print Entity
Relationship* followsRelationshipPrintReadOne = new FollowsRelationship(printEntity, readEntity);
Relationship* followsRelationshipPrintReadDupOne = new FollowsRelationship(printEntityDuplicate, readEntityDuplicate);

Relationship* followsRelationshipPrintPrintOne = new FollowsRelationship(printEntity, printEntityTwo);
Relationship* followsRelationshipPrintPrintDupOne = new FollowsRelationship(printEntityDuplicate, printEntityTwoDuplicate);

Relationship* followsRelationshipPrintAssignOne = new FollowsRelationship(printEntity, assignEntity);
Relationship* followsRelationshipPrintAssignDupOne = new FollowsRelationship(printEntityDuplicate, assignEntityDuplicate);


Relationship* followsRelationshipPrintCallOne = new FollowsRelationship(printEntity, callEntity);
Relationship* followsRelationshipPrintCallDupOne =new FollowsRelationship(printEntityDuplicate, callEntityDuplicate);
Relationship* followsRelationshipPrintWhileOne = new FollowsRelationship(printEntity, whileEntity);
Relationship* followsRelationshipPrintWhileDupOne = new FollowsRelationship(printEntityDuplicate, whileEntityDuplicate);

Relationship* followsRelationshipPrintIfOne = new FollowsRelationship(printEntity, ifEntity);
Relationship* followsRelationshipPrintIfDupOne = new FollowsRelationship(printEntityDuplicate, ifEntityDuplicate);

// Assign Entity
Relationship* followsRelationshipAssignReadOne = new FollowsRelationship(assignEntity, readEntity);
Relationship* followsRelationshipAssignReadDupOne = new FollowsRelationship(assignEntityDuplicate, readEntityDuplicate);

Relationship* followsRelationshipAssignPrintOne = new FollowsRelationship(assignEntity, printEntity);
Relationship* followsRelationshipAssignPrintDupOne = new FollowsRelationship(assignEntityDuplicate, printEntityDuplicate);

Relationship* followsRelationshipAssignAssignOne = new FollowsRelationship(assignEntity, assignEntityTwo);
Relationship* followsRelationshipAssignAssignDupOne = new FollowsRelationship(assignEntityDuplicate, assignEntityTwoDuplicate);

Relationship* followsRelationshipAssignCallOne = new FollowsRelationship(assignEntity, callEntity);
Relationship* followsRelationshipAssignCallDupOne = new FollowsRelationship(assignEntityDuplicate, callEntityDuplicate);

Relationship* followsRelationshipAssignWhileOne = new FollowsRelationship(assignEntity, whileEntity);
Relationship* followsRelationshipAssignWhileDupOne = new FollowsRelationship(assignEntityDuplicate, whileEntityDuplicate);

Relationship* followsRelationshipAssignIfOne = new FollowsRelationship(assignEntity, ifEntity);
Relationship* followsRelationshipAssignIfDupOne = new FollowsRelationship(assignEntityDuplicate, ifEntityDuplicate);

// Call Entity
Relationship* followsRelationshipCallReadOne = new FollowsRelationship(callEntity, readEntity);
Relationship* followsRelationshipCallReadDupOne = new FollowsRelationship(callEntityDuplicate, readEntityDuplicate);

Relationship* followsRelationshipCallPrintOne = new FollowsRelationship(callEntity, printEntity);
Relationship* followsRelationshipCallPrintDupOne = new FollowsRelationship(callEntityDuplicate, printEntityDuplicate);

Relationship* followsRelationshipCallAssignOne = new FollowsRelationship(callEntity, assignEntity);
Relationship* followsRelationshipCallAssignDupOne = new FollowsRelationship(callEntityDuplicate, assignEntityDuplicate);

Relationship* followsRelationshipCallCallOne = new FollowsRelationship(callEntity, callEntityTwo);
Relationship* followsRelationshipCallCallDupOne = new FollowsRelationship(callEntityDuplicate, callEntityTwoDuplicate);

Relationship* followsRelationshipCallWhileOne = new FollowsRelationship(callEntity, whileEntity);
Relationship* followsRelationshipCallWhileDupOne = new FollowsRelationship(callEntityDuplicate, whileEntityDuplicate);

Relationship* followsRelationshipCallIfOne = new FollowsRelationship(callEntity, ifEntity);
Relationship* followsRelationshipCallIfDupOne = new FollowsRelationship(callEntityDuplicate, ifEntityDuplicate);

// While Entity
Relationship* followsRelationshipWhileReadOne = new FollowsRelationship(whileEntity, readEntity);
Relationship* followsRelationshipWhileReadDupOne = new FollowsRelationship(whileEntityDuplicate, readEntityDuplicate);

Relationship* followsRelationshipWhilePrintOne = new FollowsRelationship(whileEntity, printEntity);
Relationship* followsRelationshipWhilePrintDupOne = new FollowsRelationship(whileEntityDuplicate, printEntityDuplicate);

Relationship* followsRelationshipWhileAssignOne = new FollowsRelationship(whileEntity, assignEntity);
Relationship* followsRelationshipWhileAssignDupOne = new FollowsRelationship(whileEntityDuplicate, assignEntityDuplicate);

Relationship* followsRelationshipWhileCallOne = new FollowsRelationship(whileEntity, callEntity);
Relationship* followsRelationshipWhileCallDupOne = new FollowsRelationship(whileEntityDuplicate, callEntityDuplicate);

Relationship* followsRelationshipWhileWhileOne = new FollowsRelationship(whileEntity, whileEntityTwo);
Relationship* followsRelationshipWhileWhileDupOne = new FollowsRelationship(whileEntityDuplicate, whileEntityTwoDuplicate);

Relationship* followsRelationshipWhileIfOne = new FollowsRelationship(whileEntity, ifEntity);
Relationship* followsRelationshipWhileIfDupOne = new FollowsRelationship(whileEntityDuplicate, ifEntityDuplicate);

// If Entity
Relationship* followsRelationshipIfReadOne = new FollowsRelationship(ifEntity, readEntity);
Relationship* followsRelationshipIfReadDupOne = new FollowsRelationship(ifEntityDuplicate, readEntityDuplicate);

Relationship* followsRelationshipIfPrintOne = new FollowsRelationship(ifEntity, printEntity);
Relationship* followsRelationshipIfPrintDupOne = new FollowsRelationship(ifEntityDuplicate, printEntityDuplicate);

Relationship* followsRelationshipIfAssignOne = new FollowsRelationship(ifEntity, assignEntity);
Relationship* followsRelationshipIfAssignDupOne = new FollowsRelationship(ifEntityDuplicate, assignEntityDuplicate);

Relationship* followsRelationshipIfCallOne = new FollowsRelationship(ifEntity, callEntity);
Relationship* followsRelationshipIfCallDupOne = new FollowsRelationship(ifEntityDuplicate, callEntityDuplicate);

Relationship* followsRelationshipIfWhileOne = new FollowsRelationship(ifEntity, whileEntity);
Relationship* followsRelationshipIfWhileDupOne = new FollowsRelationship(ifEntityDuplicate, whileEntityDuplicate);

Relationship* followsRelationshipIfIfOne = new FollowsRelationship(ifEntity, ifEntityTwo);
Relationship* followsRelationshipIfIfDupOne = new FollowsRelationship(ifEntityDuplicate, ifEntityTwoDuplicate);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Read Entity
Relationship* followsTRelationshipReadReadOne = new FollowsTRelationship(readEntity, readEntityTwo);
Relationship* followsTRelationshipReadReadDupOne = new FollowsTRelationship(readEntityDuplicate, readEntityTwoDuplicate);

Relationship* followsTRelationshipReadPrintOne = new FollowsTRelationship(readEntity, printEntity);
Relationship* followsTRelationshipReadPrintDupOne = new FollowsTRelationship(readEntityDuplicate, printEntityDuplicate);

Relationship* followsTRelationshipReadAssignOne = new FollowsTRelationship(readEntity, assignEntity);
Relationship* followsTRelationshipReadAssignDupOne = new FollowsTRelationship(readEntityDuplicate, assignEntityDuplicate);

Relationship* followsTRelationshipReadCallOne = new FollowsTRelationship(readEntity, callEntity);
Relationship* followsTRelationshipReadCallDupOne = new FollowsTRelationship(readEntityDuplicate, callEntityDuplicate);

Relationship* followsTRelationshipReadWhileOne = new FollowsTRelationship(readEntity, whileEntity);
Relationship* followsTRelationshipReadWhileDupOne = new FollowsTRelationship(readEntityDuplicate, whileEntityDuplicate);

Relationship* followsTRelationshipReadIfOne = new FollowsTRelationship(readEntity, ifEntity);
Relationship* followsTRelationshipReadIfDupOne = new FollowsTRelationship(readEntityDuplicate, ifEntityDuplicate);

// Print Entity
Relationship* followsTRelationshipPrintReadOne = new FollowsTRelationship(printEntity, readEntity);
Relationship* followsTRelationshipPrintReadDupOne = new FollowsTRelationship(printEntityDuplicate, readEntityDuplicate);

Relationship* followsTRelationshipPrintPrintOne = new FollowsTRelationship(printEntity, printEntityTwo);
Relationship* followsTRelationshipPrintPrintDupOne = new FollowsTRelationship(printEntityDuplicate, printEntityTwoDuplicate);

Relationship* followsTRelationshipPrintAssignOne = new FollowsTRelationship(printEntity, assignEntity);
Relationship* followsTRelationshipPrintAssignDupOne = new FollowsTRelationship(printEntityDuplicate, assignEntityDuplicate);


Relationship* followsTRelationshipPrintCallOne = new FollowsTRelationship(printEntity, callEntity);
Relationship* followsTRelationshipPrintCallDupOne = new FollowsTRelationship(printEntityDuplicate, callEntityDuplicate);

Relationship* followsTRelationshipPrintWhileOne = new FollowsTRelationship(printEntity, whileEntity);
Relationship* followsTRelationshipPrintWhileDupOne = new FollowsTRelationship(printEntityDuplicate, whileEntityDuplicate);

Relationship* followsTRelationshipPrintIfOne = new FollowsTRelationship(printEntity, ifEntity);
Relationship* followsTRelationshipPrintIfDupOne = new FollowsTRelationship(printEntityDuplicate, ifEntityDuplicate);

// Assign Entity
Relationship* followsTRelationshipAssignReadOne = new FollowsTRelationship(assignEntity, readEntity);
Relationship* followsTRelationshipAssignReadDupOne = new FollowsTRelationship(assignEntityDuplicate, readEntityDuplicate);

Relationship* followsTRelationshipAssignPrintOne = new FollowsTRelationship(assignEntity, printEntity);
Relationship* followsTRelationshipAssignPrintDupOne = new FollowsTRelationship(assignEntityDuplicate, printEntityDuplicate);

Relationship* followsTRelationshipAssignAssignOne = new FollowsTRelationship(assignEntity, assignEntityTwo);
Relationship* followsTRelationshipAssignAssignDupOne = new FollowsTRelationship(assignEntityDuplicate, assignEntityTwoDuplicate);

Relationship* followsTRelationshipAssignCallOne = new FollowsTRelationship(assignEntity, callEntity);
Relationship* followsTRelationshipAssignCallDupOne = new FollowsTRelationship(assignEntityDuplicate, callEntityDuplicate);

Relationship* followsTRelationshipAssignWhileOne = new FollowsTRelationship(assignEntity, whileEntity);
Relationship* followsTRelationshipAssignWhileDupOne = new FollowsTRelationship(assignEntityDuplicate, whileEntityDuplicate);

Relationship* followsTRelationshipAssignIfOne = new FollowsTRelationship(assignEntity, ifEntity);
Relationship* followsTRelationshipAssignIfDupOne = new FollowsTRelationship(assignEntityDuplicate, ifEntityDuplicate);

// Call Entity
Relationship* followsTRelationshipCallReadOne = new FollowsTRelationship(callEntity, readEntity);
Relationship* followsTRelationshipCallReadDupOne = new FollowsTRelationship(callEntityDuplicate, readEntityDuplicate);

Relationship* followsTRelationshipCallPrintOne = new FollowsTRelationship(callEntity, printEntity);
Relationship* followsTRelationshipCallPrintDupOne = new FollowsTRelationship(callEntityDuplicate, printEntityDuplicate);

Relationship* followsTRelationshipCallAssignOne = new FollowsTRelationship(callEntity, assignEntity);
Relationship* followsTRelationshipCallAssignDupOne = new FollowsTRelationship(callEntityDuplicate, assignEntityDuplicate);

Relationship* followsTRelationshipCallCallOne = new FollowsTRelationship(callEntity, callEntityTwo);
Relationship* followsTRelationshipCallCallDupOne = new FollowsTRelationship(callEntityDuplicate, callEntityTwoDuplicate);

Relationship* followsTRelationshipCallWhileOne = new FollowsTRelationship(callEntity, whileEntity);
Relationship* followsTRelationshipCallWhileDupOne = new FollowsTRelationship(callEntityDuplicate, whileEntityDuplicate);

Relationship* followsTRelationshipCallIfOne = new FollowsTRelationship(callEntity, ifEntity);
Relationship* followsTRelationshipCallIfDupOne = new FollowsTRelationship(callEntityDuplicate, ifEntityDuplicate);

// While Entity
Relationship* followsTRelationshipWhileReadOne = new FollowsTRelationship(whileEntity, readEntity);
Relationship* followsTRelationshipWhileReadDupOne = new FollowsTRelationship(whileEntityDuplicate, readEntityDuplicate);

Relationship* followsTRelationshipWhilePrintOne = new FollowsTRelationship(whileEntity, printEntity);
Relationship* followsTRelationshipWhilePrintDupOne = new FollowsTRelationship(whileEntityDuplicate, printEntityDuplicate);

Relationship* followsTRelationshipWhileAssignOne = new FollowsTRelationship(whileEntity, assignEntity);
Relationship* followsTRelationshipWhileAssignDupOne = new FollowsTRelationship(whileEntityDuplicate, assignEntityDuplicate);

Relationship* followsTRelationshipWhileCallOne = new FollowsTRelationship(whileEntity, callEntity);
Relationship* followsTRelationshipWhileCallDupOne = new FollowsTRelationship(whileEntityDuplicate, callEntityDuplicate);

Relationship* followsTRelationshipWhileWhileOne = new FollowsTRelationship(whileEntity, whileEntityTwo);
Relationship* followsTRelationshipWhileWhileDupOne = new FollowsTRelationship(whileEntityDuplicate, whileEntityTwoDuplicate);

Relationship* followsTRelationshipWhileIfOne = new FollowsTRelationship(whileEntity, ifEntity);
Relationship* followsTRelationshipWhileIfDupOne = new FollowsTRelationship(whileEntityDuplicate, ifEntityDuplicate);

// If Entity
Relationship* followsTRelationshipIfReadOne = new FollowsTRelationship(ifEntity, readEntity);
Relationship* followsTRelationshipIfReadDupOne = new FollowsTRelationship(ifEntityDuplicate, readEntityDuplicate);

Relationship* followsTRelationshipIfPrintOne = new FollowsTRelationship(ifEntity, printEntity);
Relationship* followsTRelationshipIfPrintDupOne = new FollowsTRelationship(ifEntityDuplicate, printEntityDuplicate);

Relationship* followsTRelationshipIfAssignOne = new FollowsTRelationship(ifEntity, assignEntity);
Relationship* followsTRelationshipIfAssignDupOne = new FollowsTRelationship(ifEntityDuplicate, assignEntityDuplicate);

Relationship* followsTRelationshipIfCallOne = new FollowsTRelationship(ifEntity, callEntity);
Relationship* followsTRelationshipIfCallDupOne = new FollowsTRelationship(ifEntityDuplicate, callEntityDuplicate);

Relationship* followsTRelationshipIfWhileOne = new FollowsTRelationship(ifEntity, whileEntity);
Relationship* followsTRelationshipIfWhileDupOne = new FollowsTRelationship(ifEntityDuplicate, whileEntityDuplicate);

Relationship* followsTRelationshipIfIfOne = new FollowsTRelationship(ifEntity, ifEntityTwo);
Relationship* followsTRelationshipIfIfDupOne = new FollowsTRelationship(ifEntityDuplicate, ifEntityTwoDuplicate);