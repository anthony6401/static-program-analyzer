#pragma once

#include "EntityObject.h"
#include "models/Relationship/Relationship.h"
#include "models/Relationship/UsesRelationship.h"
#include "models/Relationship/ModifyRelationship.h"
#include "models/Relationship/ParentRelationship.h"
#include "models/Relationship/ParentTRelationship.h"
#include "models/Relationship/FollowsRelationship.h"
#include "models/Relationship/FollowsTRelationship.h"
#include "models/Relationship/NextTRelationship.h"

static Relationship* usesRelationshipAssignOne = new UsesRelationship(assignEntity, variableEntity);
static Relationship* usesRelationshipAssignTwo = new UsesRelationship(assignEntityTwo, variableEntityTwo);
static Relationship* usesRelationshipAssignOneDuplicate = new UsesRelationship(assignEntityDuplicate, variableEntityThree);
static Relationship* usesRelationshipAssignTwoDuplicate = new UsesRelationship(assignEntityTwoDuplicate, variableEntity);

static Relationship* usesRelationshipProcOne = new UsesRelationship(procedureEntity, variableEntity);
static Relationship* usesRelationshipProcTwo = new UsesRelationship(procedureEntityTwo, variableEntityTwo);
static Relationship* usesRelationshipProcOneDuplicate = new UsesRelationship(procedureEntityDuplicate, variableEntityThree);
static Relationship* usesRelationshipProcTwoDuplicate = new UsesRelationship(procedureEntityTwoDuplicate, variableEntity);

static Relationship* usesRelationshipReadOne = new UsesRelationship(readEntity, variableEntity);
static Relationship* usesRelationshipReadTwo = new UsesRelationship(readEntityTwo, variableEntityTwo);
static Relationship* usesRelationshipReadOneDuplicate = new UsesRelationship(readEntityDuplicate, variableEntityThree);
static Relationship* usesRelationshipReadTwoDuplicate = new UsesRelationship(readEntityTwoDuplicate, variableEntity);

static Relationship* usesRelationshipPrintOne = new UsesRelationship(printEntity, variableEntity);
static Relationship* usesRelationshipPrintTwo = new UsesRelationship(printEntityTwo, variableEntityTwo);
static Relationship* usesRelationshipPrintOneDuplicate = new UsesRelationship(printEntityDuplicate, variableEntityThree);
static Relationship* usesRelationshipPrintTwoDuplicate = new UsesRelationship(printEntityTwoDuplicate, variableEntity);

static Relationship* usesRelationshipWhileOne = new UsesRelationship(whileEntity, variableEntity);
static Relationship* usesRelationshipWhileTwo = new UsesRelationship(whileEntityTwo, variableEntityTwo);
static Relationship* usesRelationshipWhileOneDuplicate = new UsesRelationship(whileEntityDuplicate, variableEntityThree);
static Relationship* usesRelationshipWhileTwoDuplicate = new UsesRelationship(whileEntityTwoDuplicate, variableEntity);

static Relationship* usesRelationshipIfOne = new UsesRelationship(ifEntity, variableEntity);
static Relationship* usesRelationshipIfTwo = new UsesRelationship(ifEntityTwo, variableEntityTwo);
static Relationship* usesRelationshipIfOneDuplicate = new UsesRelationship(ifEntityDuplicate, variableEntityThree);
static Relationship* usesRelationshipIfTwoDuplicate = new UsesRelationship(ifEntityTwoDuplicate, variableEntity);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static Relationship* modifyRelationshipAssignOne = new ModifyRelationship(assignEntity, variableEntity);
static Relationship* modifyRelationshipAssignTwo = new ModifyRelationship(assignEntityTwo, variableEntityTwo);
static Relationship* modifyRelationshipAssignOneDuplicate = new ModifyRelationship(assignEntityDuplicate, variableEntityThree);
static Relationship* modifyRelationshipAssignTwoDuplicate = new ModifyRelationship(assignEntityTwoDuplicate, variableEntity);

static Relationship* modifyRelationshipProcOne = new ModifyRelationship(procedureEntity, variableEntity);
static Relationship* modifyRelationshipProcTwo = new ModifyRelationship(procedureEntityTwo, variableEntityTwo);
static Relationship* modifyRelationshipProcOneDuplicate = new ModifyRelationship(procedureEntityDuplicate, variableEntityThree);
static Relationship* modifyRelationshipProcTwoDuplicate = new ModifyRelationship(procedureEntityTwoDuplicate, variableEntity);

static Relationship* modifyRelationshipReadOne = new ModifyRelationship(readEntity, variableEntity);
static Relationship* modifyRelationshipReadTwo = new ModifyRelationship(readEntityTwo, variableEntityTwo);
static Relationship* modifyRelationshipReadOneDuplicate = new ModifyRelationship(readEntityDuplicate, variableEntityThree);
static Relationship* modifyRelationshipReadTwoDuplicate = new ModifyRelationship(readEntityTwoDuplicate, variableEntity);

static Relationship* modifyRelationshipPrintOne = new ModifyRelationship(printEntity, variableEntity);
static Relationship* modifyRelationshipPrintTwo = new ModifyRelationship(printEntityTwo, variableEntityTwo);
static Relationship* modifyRelationshipPrintOneDuplicate = new ModifyRelationship(printEntityDuplicate, variableEntityThree);
static Relationship* modifyRelationshipPrintTwoDuplicate = new ModifyRelationship(printEntityTwoDuplicate, variableEntity);

static Relationship* modifyRelationshipWhileOne = new ModifyRelationship(whileEntity, variableEntity);
static Relationship* modifyRelationshipWhileTwo = new ModifyRelationship(whileEntityTwo, variableEntityTwo);
static Relationship* modifyRelationshipWhileOneDuplicate = new ModifyRelationship(whileEntityDuplicate, variableEntityThree);
static Relationship* modifyRelationshipWhileTwoDuplicate = new ModifyRelationship(whileEntityTwoDuplicate, variableEntity);

static Relationship* modifyRelationshipIfOne = new ModifyRelationship(ifEntity, variableEntity);
static Relationship* modifyRelationshipIfTwo = new ModifyRelationship(ifEntityTwo, variableEntityTwo);
static Relationship* modifyRelationshipIfOneDuplicate = new ModifyRelationship(ifEntityDuplicate, variableEntityThree);
static Relationship* modifyRelationshipIfTwoDuplicate = new ModifyRelationship(ifEntityTwoDuplicate, variableEntity);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// While Entity
static Relationship* parentRelationshipWhileReadOne = new ParentRelationship(whileEntity, readEntity);
static Relationship* parentRelationshipWhileReadTwo = new ParentRelationship(whileEntityTwo, readEntityTwo);
static Relationship* parentRelationshipWhileReadDupOne = new ParentRelationship(whileEntityDuplicate, readEntityDuplicate);
static Relationship* parentRelationshipWhileReadDupTwo = new ParentRelationship(whileEntityTwoDuplicate, readEntityTwoDuplicate);

static Relationship* parentRelationshipWhilePrintOne = new ParentRelationship(whileEntity, printEntity);
static Relationship* parentRelationshipWhilePrintTwo = new ParentRelationship(whileEntityTwo, printEntityTwo);
static Relationship* parentRelationshipWhilePrintDupOne = new ParentRelationship(whileEntityDuplicate, printEntityDuplicate);
static Relationship* parentRelationshipWhilePrintDupTwo = new ParentRelationship(whileEntityTwoDuplicate, printEntityTwoDuplicate);

static Relationship* parentRelationshipWhileAssignOne = new ParentRelationship(whileEntity, assignEntity);
static Relationship* parentRelationshipWhileAssignTwo = new ParentRelationship(whileEntityTwo, assignEntityTwo);
static Relationship* parentRelationshipWhileAssignDupOne = new ParentRelationship(whileEntityDuplicate, assignEntityDuplicate);
static Relationship* parentRelationshipWhileAssignDupTwo = new ParentRelationship(whileEntityTwoDuplicate, assignEntityTwoDuplicate);

static Relationship* parentRelationshipWhileCallOne = new ParentRelationship(whileEntity, callEntity);
static Relationship* parentRelationshipWhileCallTwo = new ParentRelationship(whileEntityTwo, callEntityTwo);
static Relationship* parentRelationshipWhileCallDupOne = new ParentRelationship(whileEntityDuplicate, callEntityDuplicate);
static Relationship* parentRelationshipWhileCallDupTwo = new ParentRelationship(whileEntityTwoDuplicate, callEntityTwoDuplicate);

static Relationship* parentRelationshipWhileWhileOne = new ParentRelationship(whileEntity, whileEntityTwo);
static Relationship* parentRelationshipWhileWhileTwo = new ParentRelationship(whileEntityTwo, whileEntityThree);
static Relationship* parentRelationshipWhileWhileDupOne = new ParentRelationship(whileEntityDuplicate, whileEntityTwoDuplicate);
static Relationship* parentRelationshipWhileWhileDupTwo = new ParentRelationship(whileEntityTwoDuplicate, whileEntityThreeDuplicate);

static Relationship* parentRelationshipWhileIfOne = new ParentRelationship(whileEntity, ifEntity);
static Relationship* parentRelationshipWhileIfTwo = new ParentRelationship(whileEntityTwo, ifEntityTwo);
static Relationship* parentRelationshipWhileIfDupOne = new ParentRelationship(whileEntityDuplicate, ifEntityDuplicate);
static Relationship* parentRelationshipWhileIfDupTwo = new ParentRelationship(whileEntityTwoDuplicate, ifEntityTwoDuplicate);

// If Entity
static Relationship* parentRelationshipIfReadOne = new ParentRelationship(ifEntity, readEntity);
static Relationship* parentRelationshipIfReadTwo = new ParentRelationship(ifEntityTwo, readEntityTwo);
static Relationship* parentRelationshipIfReadDupOne = new ParentRelationship(ifEntityDuplicate, readEntityDuplicate);
static Relationship* parentRelationshipIfReadDupTwo = new ParentRelationship(ifEntityTwoDuplicate, readEntityTwoDuplicate);

static Relationship* parentRelationshipIfPrintOne = new ParentRelationship(ifEntity, printEntity);
static Relationship* parentRelationshipIfPrintTwo = new ParentRelationship(ifEntityTwo, printEntityTwo);
static Relationship* parentRelationshipIfPrintDupOne = new ParentRelationship(ifEntityDuplicate, printEntityDuplicate);
static Relationship* parentRelationshipIfPrintDupTwo = new ParentRelationship(ifEntityTwoDuplicate, printEntityTwoDuplicate);

static Relationship* parentRelationshipIfAssignOne = new ParentRelationship(ifEntity, assignEntity);
static Relationship* parentRelationshipIfAssignTwo = new ParentRelationship(ifEntityTwo, assignEntityTwo);
static Relationship* parentRelationshipIfAssignDupOne = new ParentRelationship(ifEntityDuplicate, assignEntityDuplicate);
static Relationship* parentRelationshipIfAssignDupTwo = new ParentRelationship(ifEntityTwoDuplicate, assignEntityTwoDuplicate);

static Relationship* parentRelationshipIfCallOne = new ParentRelationship(ifEntity, callEntity);
static Relationship* parentRelationshipIfCallTwo = new ParentRelationship(ifEntityTwo, callEntityTwo);
static Relationship* parentRelationshipIfCallDupOne = new ParentRelationship(ifEntityDuplicate, callEntityDuplicate);
static Relationship* parentRelationshipIfCallDupTwo = new ParentRelationship(ifEntityTwoDuplicate, callEntityTwoDuplicate);

static Relationship* parentRelationshipIfWhileOne = new ParentRelationship(ifEntity, whileEntity);
static Relationship* parentRelationshipIfWhileTwo = new ParentRelationship(ifEntityTwo, whileEntityTwo);
static Relationship* parentRelationshipIfWhileDupOne = new ParentRelationship(ifEntityDuplicate, whileEntityDuplicate);
static Relationship* parentRelationshipIfWhileDupTwo = new ParentRelationship(ifEntityTwoDuplicate, whileEntityTwoDuplicate);

static Relationship* parentRelationshipIfIfOne = new ParentRelationship(ifEntity, ifEntityTwo);
static Relationship* parentRelationshipIfIfTwo = new ParentRelationship(ifEntityTwo, ifEntityThree);
static Relationship* parentRelationshipIfIfDupOne = new ParentRelationship(ifEntityDuplicate, ifEntityTwoDuplicate);
static Relationship* parentRelationshipIfIfDupTwo = new ParentRelationship(ifEntityTwoDuplicate, ifEntityThreeDuplicate);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// While Entity
static Relationship* parentTRelationshipWhileReadOne = new ParentTRelationship(whileEntity, readEntity);
static Relationship* parentTRelationshipWhileReadTwo = new ParentTRelationship(whileEntityTwo, readEntityTwo);
static Relationship* parentTRelationshipWhileReadDupOne = new ParentTRelationship(whileEntityDuplicate, readEntityDuplicate);
static Relationship* parentTRelationshipWhileReadDupTwo = new ParentTRelationship(whileEntityTwoDuplicate, readEntityTwoDuplicate);

static Relationship* parentTRelationshipWhilePrintOne = new ParentTRelationship(whileEntity, printEntity);
static Relationship* parentTRelationshipWhilePrintTwo = new ParentTRelationship(whileEntityTwo, printEntityTwo);
static Relationship* parentTRelationshipWhilePrintDupOne = new ParentTRelationship(whileEntityDuplicate, printEntityDuplicate);
static Relationship* parentTRelationshipWhilePrintDupTwo = new ParentTRelationship(whileEntityTwoDuplicate, printEntityTwoDuplicate);

static Relationship* parentTRelationshipWhileAssignOne = new ParentTRelationship(whileEntity, assignEntity);
static Relationship* parentTRelationshipWhileAssignTwo = new ParentTRelationship(whileEntityTwo, assignEntityTwo);
static Relationship* parentTRelationshipWhileAssignDupOne = new ParentTRelationship(whileEntityDuplicate, assignEntityDuplicate);
static Relationship* parentTRelationshipWhileAssignDupTwo = new ParentTRelationship(whileEntityTwoDuplicate, assignEntityTwoDuplicate);

static Relationship* parentTRelationshipWhileCallOne = new ParentTRelationship(whileEntity, callEntity);
static Relationship* parentTRelationshipWhileCallTwo = new ParentTRelationship(whileEntityTwo, callEntityTwo);
static Relationship* parentTRelationshipWhileCallDupOne = new ParentTRelationship(whileEntityDuplicate, callEntityDuplicate);
static Relationship* parentTRelationshipWhileCallDupTwo = new ParentTRelationship(whileEntityTwoDuplicate, callEntityTwoDuplicate);

static Relationship* parentTRelationshipWhileWhileOne = new ParentTRelationship(whileEntity, whileEntityTwo);
static Relationship* parentTRelationshipWhileWhileTwo = new ParentTRelationship(whileEntityTwo, whileEntityThree);
static Relationship* parentTRelationshipWhileWhileDupOne = new ParentTRelationship(whileEntityDuplicate, whileEntityTwoDuplicate);
static Relationship* parentTRelationshipWhileWhileDupTwo = new ParentTRelationship(whileEntityTwoDuplicate, whileEntityThreeDuplicate);

static Relationship* parentTRelationshipWhileIfOne = new ParentTRelationship(whileEntity, ifEntity);
static Relationship* parentTRelationshipWhileIfTwo = new ParentTRelationship(whileEntityTwo, ifEntityTwo);
static Relationship* parentTRelationshipWhileIfDupOne = new ParentTRelationship(whileEntityDuplicate, ifEntityDuplicate);
static Relationship* parentTRelationshipWhileIfDupTwo = new ParentTRelationship(whileEntityTwoDuplicate, ifEntityTwoDuplicate);

// If Entity
static Relationship* parentTRelationshipIfReadOne = new ParentTRelationship(ifEntity, readEntity);
static Relationship* parentTRelationshipIfReadTwo = new ParentTRelationship(ifEntityTwo, readEntityTwo);
static Relationship* parentTRelationshipIfReadDupOne = new ParentTRelationship(ifEntityDuplicate, readEntityDuplicate);
static Relationship* parentTRelationshipIfReadDupTwo = new ParentTRelationship(ifEntityTwoDuplicate, readEntityTwoDuplicate);

static Relationship* parentTRelationshipIfPrintOne = new ParentTRelationship(ifEntity, printEntity);
static Relationship* parentTRelationshipIfPrintTwo = new ParentTRelationship(ifEntityTwo, printEntityTwo);
static Relationship* parentTRelationshipIfPrintDupOne = new ParentTRelationship(ifEntityDuplicate, printEntityDuplicate);
static Relationship* parentTRelationshipIfPrintDupTwo = new ParentTRelationship(ifEntityTwoDuplicate, printEntityTwoDuplicate);

static Relationship* parentTRelationshipIfAssignOne = new ParentTRelationship(ifEntity, assignEntity);
static Relationship* parentTRelationshipIfAssignTwo = new ParentTRelationship(ifEntityTwo, assignEntityTwo);
static Relationship* parentTRelationshipIfAssignDupOne = new ParentTRelationship(ifEntityDuplicate, assignEntityDuplicate);
static Relationship* parentTRelationshipIfAssignDupTwo = new ParentTRelationship(ifEntityTwoDuplicate, assignEntityTwoDuplicate);

static Relationship* parentTRelationshipIfCallOne = new ParentTRelationship(ifEntity, callEntity);
static Relationship* parentTRelationshipIfCallTwo = new ParentTRelationship(ifEntityTwo, callEntityTwo);
static Relationship* parentTRelationshipIfCallDupOne = new ParentTRelationship(ifEntityDuplicate, callEntityDuplicate);
static Relationship* parentTRelationshipIfCallDupTwo = new ParentTRelationship(ifEntityTwoDuplicate, callEntityTwoDuplicate);

static Relationship* parentTRelationshipIfWhileOne = new ParentTRelationship(ifEntity, whileEntity);
static Relationship* parentTRelationshipIfWhileTwo = new ParentTRelationship(ifEntityTwo, whileEntityTwo);
static Relationship* parentTRelationshipIfWhileDupOne = new ParentTRelationship(ifEntityDuplicate, whileEntityDuplicate);
static Relationship* parentTRelationshipIfWhileDupTwo = new ParentTRelationship(ifEntityTwoDuplicate, whileEntityTwoDuplicate);

static Relationship* parentTRelationshipIfIfOne = new ParentTRelationship(ifEntity, ifEntityTwo);
static Relationship* parentTRelationshipIfIfTwo = new ParentTRelationship(ifEntityTwo, ifEntityThree);
static Relationship* parentTRelationshipIfIfDupOne = new ParentTRelationship(ifEntityDuplicate, ifEntityTwoDuplicate);
static Relationship* parentTRelationshipIfIfDupTwo = new ParentTRelationship(ifEntityTwoDuplicate, ifEntityThreeDuplicate);


// Read Entity
static Relationship* followsRelationshipReadReadOne = new FollowsRelationship(readEntity, readEntityTwo);
static Relationship* followsRelationshipReadReadDupOne = new FollowsRelationship(readEntityDuplicate, readEntityTwoDuplicate);

static Relationship* followsRelationshipReadPrintOne = new FollowsRelationship(readEntity, printEntity);
static Relationship* followsRelationshipReadPrintDupOne = new FollowsRelationship(readEntityDuplicate, printEntityDuplicate);

static Relationship* followsRelationshipReadAssignOne = new FollowsRelationship(readEntity, assignEntity);
static Relationship* followsRelationshipReadAssignDupOne = new FollowsRelationship(readEntityDuplicate, assignEntityDuplicate);

static Relationship* followsRelationshipReadCallOne = new FollowsRelationship(readEntity, callEntity);
static Relationship* followsRelationshipReadCallDupOne = new FollowsRelationship(readEntityDuplicate, callEntityDuplicate);

static Relationship* followsRelationshipReadWhileOne = new FollowsRelationship(readEntity, whileEntity);
static Relationship* followsRelationshipReadWhileDupOne = new FollowsRelationship(readEntityDuplicate, whileEntityDuplicate);

static Relationship* followsRelationshipReadIfOne = new FollowsRelationship(readEntity, ifEntity);
static Relationship* followsRelationshipReadIfDupOne = new FollowsRelationship(readEntityDuplicate, ifEntityDuplicate);

// Print Entity
static Relationship* followsRelationshipPrintReadOne = new FollowsRelationship(printEntity, readEntity);
static Relationship* followsRelationshipPrintReadDupOne = new FollowsRelationship(printEntityDuplicate, readEntityDuplicate);

static Relationship* followsRelationshipPrintPrintOne = new FollowsRelationship(printEntity, printEntityTwo);
static Relationship* followsRelationshipPrintPrintDupOne = new FollowsRelationship(printEntityDuplicate, printEntityTwoDuplicate);

static Relationship* followsRelationshipPrintAssignOne = new FollowsRelationship(printEntity, assignEntity);
static Relationship* followsRelationshipPrintAssignDupOne = new FollowsRelationship(printEntityDuplicate, assignEntityDuplicate);


static Relationship* followsRelationshipPrintCallOne = new FollowsRelationship(printEntity, callEntity);
static Relationship* followsRelationshipPrintCallDupOne = new FollowsRelationship(printEntityDuplicate, callEntityDuplicate);
static Relationship* followsRelationshipPrintWhileOne = new FollowsRelationship(printEntity, whileEntity);
static Relationship* followsRelationshipPrintWhileDupOne = new FollowsRelationship(printEntityDuplicate, whileEntityDuplicate);

static Relationship* followsRelationshipPrintIfOne = new FollowsRelationship(printEntity, ifEntity);
static Relationship* followsRelationshipPrintIfDupOne = new FollowsRelationship(printEntityDuplicate, ifEntityDuplicate);

// Assign Entity
static Relationship* followsRelationshipAssignReadOne = new FollowsRelationship(assignEntity, readEntity);
static Relationship* followsRelationshipAssignReadDupOne = new FollowsRelationship(assignEntityDuplicate, readEntityDuplicate);

static Relationship* followsRelationshipAssignPrintOne = new FollowsRelationship(assignEntity, printEntity);
static Relationship* followsRelationshipAssignPrintDupOne = new FollowsRelationship(assignEntityDuplicate, printEntityDuplicate);

static Relationship* followsRelationshipAssignAssignOne = new FollowsRelationship(assignEntity, assignEntityTwo);
static Relationship* followsRelationshipAssignAssignDupOne = new FollowsRelationship(assignEntityDuplicate, assignEntityTwoDuplicate);

static Relationship* followsRelationshipAssignCallOne = new FollowsRelationship(assignEntity, callEntity);
static Relationship* followsRelationshipAssignCallDupOne = new FollowsRelationship(assignEntityDuplicate, callEntityDuplicate);

static Relationship* followsRelationshipAssignWhileOne = new FollowsRelationship(assignEntity, whileEntity);
static Relationship* followsRelationshipAssignWhileDupOne = new FollowsRelationship(assignEntityDuplicate, whileEntityDuplicate);

static Relationship* followsRelationshipAssignIfOne = new FollowsRelationship(assignEntity, ifEntity);
static Relationship* followsRelationshipAssignIfDupOne = new FollowsRelationship(assignEntityDuplicate, ifEntityDuplicate);

// Call Entity
static Relationship* followsRelationshipCallReadOne = new FollowsRelationship(callEntity, readEntity);
static Relationship* followsRelationshipCallReadDupOne = new FollowsRelationship(callEntityDuplicate, readEntityDuplicate);

static Relationship* followsRelationshipCallPrintOne = new FollowsRelationship(callEntity, printEntity);
static Relationship* followsRelationshipCallPrintDupOne = new FollowsRelationship(callEntityDuplicate, printEntityDuplicate);

static Relationship* followsRelationshipCallAssignOne = new FollowsRelationship(callEntity, assignEntity);
static Relationship* followsRelationshipCallAssignDupOne = new FollowsRelationship(callEntityDuplicate, assignEntityDuplicate);

static Relationship* followsRelationshipCallCallOne = new FollowsRelationship(callEntity, callEntityTwo);
static Relationship* followsRelationshipCallCallDupOne = new FollowsRelationship(callEntityDuplicate, callEntityTwoDuplicate);

static Relationship* followsRelationshipCallWhileOne = new FollowsRelationship(callEntity, whileEntity);
static Relationship* followsRelationshipCallWhileDupOne = new FollowsRelationship(callEntityDuplicate, whileEntityDuplicate);

static Relationship* followsRelationshipCallIfOne = new FollowsRelationship(callEntity, ifEntity);
static Relationship* followsRelationshipCallIfDupOne = new FollowsRelationship(callEntityDuplicate, ifEntityDuplicate);

// While Entity
static Relationship* followsRelationshipWhileReadOne = new FollowsRelationship(whileEntity, readEntity);
static Relationship* followsRelationshipWhileReadDupOne = new FollowsRelationship(whileEntityDuplicate, readEntityDuplicate);

static Relationship* followsRelationshipWhilePrintOne = new FollowsRelationship(whileEntity, printEntity);
static Relationship* followsRelationshipWhilePrintDupOne = new FollowsRelationship(whileEntityDuplicate, printEntityDuplicate);

static Relationship* followsRelationshipWhileAssignOne = new FollowsRelationship(whileEntity, assignEntity);
static Relationship* followsRelationshipWhileAssignDupOne = new FollowsRelationship(whileEntityDuplicate, assignEntityDuplicate);

static Relationship* followsRelationshipWhileCallOne = new FollowsRelationship(whileEntity, callEntity);
static Relationship* followsRelationshipWhileCallDupOne = new FollowsRelationship(whileEntityDuplicate, callEntityDuplicate);

static Relationship* followsRelationshipWhileWhileOne = new FollowsRelationship(whileEntity, whileEntityTwo);
static Relationship* followsRelationshipWhileWhileDupOne = new FollowsRelationship(whileEntityDuplicate, whileEntityTwoDuplicate);

static Relationship* followsRelationshipWhileIfOne = new FollowsRelationship(whileEntity, ifEntity);
static Relationship* followsRelationshipWhileIfDupOne = new FollowsRelationship(whileEntityDuplicate, ifEntityDuplicate);

// If Entity
static Relationship* followsRelationshipIfReadOne = new FollowsRelationship(ifEntity, readEntity);
static Relationship* followsRelationshipIfReadDupOne = new FollowsRelationship(ifEntityDuplicate, readEntityDuplicate);

static Relationship* followsRelationshipIfPrintOne = new FollowsRelationship(ifEntity, printEntity);
static Relationship* followsRelationshipIfPrintDupOne = new FollowsRelationship(ifEntityDuplicate, printEntityDuplicate);

static Relationship* followsRelationshipIfAssignOne = new FollowsRelationship(ifEntity, assignEntity);
static Relationship* followsRelationshipIfAssignDupOne = new FollowsRelationship(ifEntityDuplicate, assignEntityDuplicate);

static Relationship* followsRelationshipIfCallOne = new FollowsRelationship(ifEntity, callEntity);
static Relationship* followsRelationshipIfCallDupOne = new FollowsRelationship(ifEntityDuplicate, callEntityDuplicate);

static Relationship* followsRelationshipIfWhileOne = new FollowsRelationship(ifEntity, whileEntity);
static Relationship* followsRelationshipIfWhileDupOne = new FollowsRelationship(ifEntityDuplicate, whileEntityDuplicate);

static Relationship* followsRelationshipIfIfOne = new FollowsRelationship(ifEntity, ifEntityTwo);
static Relationship* followsRelationshipIfIfDupOne = new FollowsRelationship(ifEntityDuplicate, ifEntityTwoDuplicate);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Read Entity
static Relationship* followsTRelationshipReadReadOne = new FollowsTRelationship(readEntity, readEntityTwo);
static Relationship* followsTRelationshipReadReadDupOne = new FollowsTRelationship(readEntityDuplicate, readEntityTwoDuplicate);

static Relationship* followsTRelationshipReadPrintOne = new FollowsTRelationship(readEntity, printEntity);
static Relationship* followsTRelationshipReadPrintDupOne = new FollowsTRelationship(readEntityDuplicate, printEntityDuplicate);

static Relationship* followsTRelationshipReadAssignOne = new FollowsTRelationship(readEntity, assignEntity);
static Relationship* followsTRelationshipReadAssignDupOne = new FollowsTRelationship(readEntityDuplicate, assignEntityDuplicate);

static Relationship* followsTRelationshipReadCallOne = new FollowsTRelationship(readEntity, callEntity);
static Relationship* followsTRelationshipReadCallDupOne = new FollowsTRelationship(readEntityDuplicate, callEntityDuplicate);

static Relationship* followsTRelationshipReadWhileOne = new FollowsTRelationship(readEntity, whileEntity);
static Relationship* followsTRelationshipReadWhileDupOne = new FollowsTRelationship(readEntityDuplicate, whileEntityDuplicate);

static Relationship* followsTRelationshipReadIfOne = new FollowsTRelationship(readEntity, ifEntity);
static Relationship* followsTRelationshipReadIfDupOne = new FollowsTRelationship(readEntityDuplicate, ifEntityDuplicate);

// Print Entity
static Relationship* followsTRelationshipPrintReadOne = new FollowsTRelationship(printEntity, readEntity);
static Relationship* followsTRelationshipPrintReadDupOne = new FollowsTRelationship(printEntityDuplicate, readEntityDuplicate);

static Relationship* followsTRelationshipPrintPrintOne = new FollowsTRelationship(printEntity, printEntityTwo);
static Relationship* followsTRelationshipPrintPrintDupOne = new FollowsTRelationship(printEntityDuplicate, printEntityTwoDuplicate);

static Relationship* followsTRelationshipPrintAssignOne = new FollowsTRelationship(printEntity, assignEntity);
static Relationship* followsTRelationshipPrintAssignDupOne = new FollowsTRelationship(printEntityDuplicate, assignEntityDuplicate);

static Relationship* followsTRelationshipPrintCallOne = new FollowsTRelationship(printEntity, callEntity);
static Relationship* followsTRelationshipPrintCallDupOne = new FollowsTRelationship(printEntityDuplicate, callEntityDuplicate);

static Relationship* followsTRelationshipPrintWhileOne = new FollowsTRelationship(printEntity, whileEntity);
static Relationship* followsTRelationshipPrintWhileDupOne = new FollowsTRelationship(printEntityDuplicate, whileEntityDuplicate);

static Relationship* followsTRelationshipPrintIfOne = new FollowsTRelationship(printEntity, ifEntity);
static Relationship* followsTRelationshipPrintIfDupOne = new FollowsTRelationship(printEntityDuplicate, ifEntityDuplicate);

// Assign Entity
static Relationship* followsTRelationshipAssignReadOne = new FollowsTRelationship(assignEntity, readEntity);
static Relationship* followsTRelationshipAssignReadDupOne = new FollowsTRelationship(assignEntityDuplicate, readEntityDuplicate);

static Relationship* followsTRelationshipAssignPrintOne = new FollowsTRelationship(assignEntity, printEntity);
static Relationship* followsTRelationshipAssignPrintDupOne = new FollowsTRelationship(assignEntityDuplicate, printEntityDuplicate);

static Relationship* followsTRelationshipAssignAssignOne = new FollowsTRelationship(assignEntity, assignEntityTwo);
static Relationship* followsTRelationshipAssignAssignDupOne = new FollowsTRelationship(assignEntityDuplicate, assignEntityTwoDuplicate);

static Relationship* followsTRelationshipAssignCallOne = new FollowsTRelationship(assignEntity, callEntity);
static Relationship* followsTRelationshipAssignCallDupOne = new FollowsTRelationship(assignEntityDuplicate, callEntityDuplicate);

static Relationship* followsTRelationshipAssignWhileOne = new FollowsTRelationship(assignEntity, whileEntity);
static Relationship* followsTRelationshipAssignWhileDupOne = new FollowsTRelationship(assignEntityDuplicate, whileEntityDuplicate);

static Relationship* followsTRelationshipAssignIfOne = new FollowsTRelationship(assignEntity, ifEntity);
static Relationship* followsTRelationshipAssignIfDupOne = new FollowsTRelationship(assignEntityDuplicate, ifEntityDuplicate);

// Call Entity
static Relationship* followsTRelationshipCallReadOne = new FollowsTRelationship(callEntity, readEntity);
static Relationship* followsTRelationshipCallReadDupOne = new FollowsTRelationship(callEntityDuplicate, readEntityDuplicate);

static Relationship* followsTRelationshipCallPrintOne = new FollowsTRelationship(callEntity, printEntity);
static Relationship* followsTRelationshipCallPrintDupOne = new FollowsTRelationship(callEntityDuplicate, printEntityDuplicate);

static Relationship* followsTRelationshipCallAssignOne = new FollowsTRelationship(callEntity, assignEntity);
static Relationship* followsTRelationshipCallAssignDupOne = new FollowsTRelationship(callEntityDuplicate, assignEntityDuplicate);

static Relationship* followsTRelationshipCallCallOne = new FollowsTRelationship(callEntity, callEntityTwo);
static Relationship* followsTRelationshipCallCallDupOne = new FollowsTRelationship(callEntityDuplicate, callEntityTwoDuplicate);

static Relationship* followsTRelationshipCallWhileOne = new FollowsTRelationship(callEntity, whileEntity);
static Relationship* followsTRelationshipCallWhileDupOne = new FollowsTRelationship(callEntityDuplicate, whileEntityDuplicate);

static Relationship* followsTRelationshipCallIfOne = new FollowsTRelationship(callEntity, ifEntity);
static Relationship* followsTRelationshipCallIfDupOne = new FollowsTRelationship(callEntityDuplicate, ifEntityDuplicate);

// While Entity
static Relationship* followsTRelationshipWhileReadOne = new FollowsTRelationship(whileEntity, readEntity);
static Relationship* followsTRelationshipWhileReadDupOne = new FollowsTRelationship(whileEntityDuplicate, readEntityDuplicate);

static Relationship* followsTRelationshipWhilePrintOne = new FollowsTRelationship(whileEntity, printEntity);
static Relationship* followsTRelationshipWhilePrintDupOne = new FollowsTRelationship(whileEntityDuplicate, printEntityDuplicate);

static Relationship* followsTRelationshipWhileAssignOne = new FollowsTRelationship(whileEntity, assignEntity);
static Relationship* followsTRelationshipWhileAssignDupOne = new FollowsTRelationship(whileEntityDuplicate, assignEntityDuplicate);

static Relationship* followsTRelationshipWhileCallOne = new FollowsTRelationship(whileEntity, callEntity);
static Relationship* followsTRelationshipWhileCallDupOne = new FollowsTRelationship(whileEntityDuplicate, callEntityDuplicate);

static Relationship* followsTRelationshipWhileWhileOne = new FollowsTRelationship(whileEntity, whileEntityTwo);
static Relationship* followsTRelationshipWhileWhileDupOne = new FollowsTRelationship(whileEntityDuplicate, whileEntityTwoDuplicate);

static Relationship* followsTRelationshipWhileIfOne = new FollowsTRelationship(whileEntity, ifEntity);
static Relationship* followsTRelationshipWhileIfDupOne = new FollowsTRelationship(whileEntityDuplicate, ifEntityDuplicate);

// If Entity
static Relationship* followsTRelationshipIfReadOne = new FollowsTRelationship(ifEntity, readEntity);
static Relationship* followsTRelationshipIfReadDupOne = new FollowsTRelationship(ifEntityDuplicate, readEntityDuplicate);

static Relationship* followsTRelationshipIfPrintOne = new FollowsTRelationship(ifEntity, printEntity);
static Relationship* followsTRelationshipIfPrintDupOne = new FollowsTRelationship(ifEntityDuplicate, printEntityDuplicate);

static Relationship* followsTRelationshipIfAssignOne = new FollowsTRelationship(ifEntity, assignEntity);
static Relationship* followsTRelationshipIfAssignDupOne = new FollowsTRelationship(ifEntityDuplicate, assignEntityDuplicate);

static Relationship* followsTRelationshipIfCallOne = new FollowsTRelationship(ifEntity, callEntity);
static Relationship* followsTRelationshipIfCallDupOne = new FollowsTRelationship(ifEntityDuplicate, callEntityDuplicate);

static Relationship* followsTRelationshipIfWhileOne = new FollowsTRelationship(ifEntity, whileEntity);
static Relationship* followsTRelationshipIfWhileDupOne = new FollowsTRelationship(ifEntityDuplicate, whileEntityDuplicate);

static Relationship* followsTRelationshipIfIfOne = new FollowsTRelationship(ifEntity, ifEntityTwo);
static Relationship* followsTRelationshipIfIfDupOne = new FollowsTRelationship(ifEntityDuplicate, ifEntityTwoDuplicate);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Read Entity
static Relationship* nextTRelationshipReadReadOne = new NextTRelationship(readEntity, readEntityTwo);
static Relationship* nextTRelationshipReadReadDupOne = new NextTRelationship(readEntityDuplicate, readEntityTwoDuplicate);

static Relationship* nextTRelationshipReadPrintOne = new NextTRelationship(readEntity, printEntity);
static Relationship* nextTRelationshipReadPrintDupOne = new NextTRelationship(readEntityDuplicate, printEntityDuplicate);

static Relationship* nextTRelationshipReadAssignOne = new NextTRelationship(readEntity, assignEntity);
static Relationship* nextTRelationshipReadAssignDupOne = new NextTRelationship(readEntityDuplicate, assignEntityDuplicate);

static Relationship* nextTRelationshipReadCallOne = new NextTRelationship(readEntity, callEntity);
static Relationship* nextTRelationshipReadCallDupOne = new NextTRelationship(readEntityDuplicate, callEntityDuplicate);

static Relationship* nextTRelationshipReadWhileOne = new NextTRelationship(readEntity, whileEntity);
static Relationship* nextTRelationshipReadWhileDupOne = new NextTRelationship(readEntityDuplicate, whileEntityDuplicate);

static Relationship* nextTRelationshipReadIfOne = new NextTRelationship(readEntity, ifEntity);
static Relationship* nextTRelationshipReadIfDupOne = new NextTRelationship(readEntityDuplicate, ifEntityDuplicate);

// Print Entity
static Relationship* nextTRelationshipPrintReadOne = new NextTRelationship(printEntity, readEntity);
static Relationship* nextTRelationshipPrintReadDupOne = new NextTRelationship(printEntityDuplicate, readEntityDuplicate);

static Relationship* nextTRelationshipPrintPrintOne = new NextTRelationship(printEntity, printEntityTwo);
static Relationship* nextTRelationshipPrintPrintDupOne = new NextTRelationship(printEntityDuplicate, printEntityTwoDuplicate);

static Relationship* nextTRelationshipPrintAssignOne = new NextTRelationship(printEntity, assignEntity);
static Relationship* nextTRelationshipPrintAssignDupOne = new NextTRelationship(printEntityDuplicate, assignEntityDuplicate);

static Relationship* nextTRelationshipPrintCallOne = new NextTRelationship(printEntity, callEntity);
static Relationship* nextTRelationshipPrintCallDupOne = new NextTRelationship(printEntityDuplicate, callEntityDuplicate);

static Relationship* nextTRelationshipPrintWhileOne = new NextTRelationship(printEntity, whileEntity);
static Relationship* nextTRelationshipPrintWhileDupOne = new NextTRelationship(printEntityDuplicate, whileEntityDuplicate);

static Relationship* nextTRelationshipPrintIfOne = new NextTRelationship(printEntity, ifEntity);
static Relationship* nextTRelationshipPrintIfDupOne = new NextTRelationship(printEntityDuplicate, ifEntityDuplicate);

// Assign Entity
static Relationship* nextTRelationshipAssignReadOne = new NextTRelationship(assignEntity, readEntity);
static Relationship* nextTRelationshipAssignReadDupOne = new NextTRelationship(assignEntityDuplicate, readEntityDuplicate);

static Relationship* nextTRelationshipAssignPrintOne = new NextTRelationship(assignEntity, printEntity);
static Relationship* nextTRelationshipAssignPrintDupOne = new NextTRelationship(assignEntityDuplicate, printEntityDuplicate);

static Relationship* nextTRelationshipAssignAssignOne = new NextTRelationship(assignEntity, assignEntityTwo);
static Relationship* nextTRelationshipAssignAssignDupOne = new NextTRelationship(assignEntityDuplicate, assignEntityTwoDuplicate);

static Relationship* nextTRelationshipAssignCallOne = new NextTRelationship(assignEntity, callEntity);
static Relationship* nextTRelationshipAssignCallDupOne = new NextTRelationship(assignEntityDuplicate, callEntityDuplicate);

static Relationship* nextTRelationshipAssignWhileOne = new NextTRelationship(assignEntity, whileEntity);
static Relationship* nextTRelationshipAssignWhileDupOne = new NextTRelationship(assignEntityDuplicate, whileEntityDuplicate);

static Relationship* nextTRelationshipAssignIfOne = new NextTRelationship(assignEntity, ifEntity);
static Relationship* nextTRelationshipAssignIfDupOne = new NextTRelationship(assignEntityDuplicate, ifEntityDuplicate);

// Call Entity
static Relationship* nextTRelationshipCallReadOne = new NextTRelationship(callEntity, readEntity);
static Relationship* nextTRelationshipCallReadDupOne = new NextTRelationship(callEntityDuplicate, readEntityDuplicate);

static Relationship* nextTRelationshipCallPrintOne = new NextTRelationship(callEntity, printEntity);
static Relationship* nextTRelationshipCallPrintDupOne = new NextTRelationship(callEntityDuplicate, printEntityDuplicate);

static Relationship* nextTRelationshipCallAssignOne = new NextTRelationship(callEntity, assignEntity);
static Relationship* nextTRelationshipCallAssignDupOne = new NextTRelationship(callEntityDuplicate, assignEntityDuplicate);

static Relationship* nextTRelationshipCallCallOne = new NextTRelationship(callEntity, callEntityTwo);
static Relationship* nextTRelationshipCallCallDupOne = new NextTRelationship(callEntityDuplicate, callEntityTwoDuplicate);

static Relationship* nextTRelationshipCallWhileOne = new NextTRelationship(callEntity, whileEntity);
static Relationship* nextTRelationshipCallWhileDupOne = new NextTRelationship(callEntityDuplicate, whileEntityDuplicate);

static Relationship* nextTRelationshipCallIfOne = new NextTRelationship(callEntity, ifEntity);
static Relationship* nextTRelationshipCallIfDupOne = new NextTRelationship(callEntityDuplicate, ifEntityDuplicate);

// While Entity
static Relationship* nextTRelationshipWhileReadOne = new NextTRelationship(whileEntity, readEntity);
static Relationship* nextTRelationshipWhileReadDupOne = new NextTRelationship(whileEntityDuplicate, readEntityDuplicate);

static Relationship* nextTRelationshipWhilePrintOne = new NextTRelationship(whileEntity, printEntity);
static Relationship* nextTRelationshipWhilePrintDupOne = new NextTRelationship(whileEntityDuplicate, printEntityDuplicate);

static Relationship* nextTRelationshipWhileAssignOne = new NextTRelationship(whileEntity, assignEntity);
static Relationship* nextTRelationshipWhileAssignDupOne = new NextTRelationship(whileEntityDuplicate, assignEntityDuplicate);

static Relationship* nextTRelationshipWhileCallOne = new NextTRelationship(whileEntity, callEntity);
static Relationship* nextTRelationshipWhileCallDupOne = new NextTRelationship(whileEntityDuplicate, callEntityDuplicate);

static Relationship* nextTRelationshipWhileWhileOne = new NextTRelationship(whileEntity, whileEntityTwo);
static Relationship* nextTRelationshipWhileWhileDupOne = new NextTRelationship(whileEntityDuplicate, whileEntityTwoDuplicate);

static Relationship* nextTRelationshipWhileIfOne = new NextTRelationship(whileEntity, ifEntity);
static Relationship* nextTRelationshipWhileIfDupOne = new NextTRelationship(whileEntityDuplicate, ifEntityDuplicate);

// If Entity
static Relationship* nextTRelationshipIfReadOne = new NextTRelationship(ifEntity, readEntity);
static Relationship* nextTRelationshipIfReadDupOne = new NextTRelationship(ifEntityDuplicate, readEntityDuplicate);

static Relationship* nextTRelationshipIfPrintOne = new NextTRelationship(ifEntity, printEntity);
static Relationship* nextTRelationshipIfPrintDupOne = new NextTRelationship(ifEntityDuplicate, printEntityDuplicate);

static Relationship* nextTRelationshipIfAssignOne = new NextTRelationship(ifEntity, assignEntity);
static Relationship* nextTRelationshipIfAssignDupOne = new NextTRelationship(ifEntityDuplicate, assignEntityDuplicate);

static Relationship* nextTRelationshipIfCallOne = new NextTRelationship(ifEntity, callEntity);
static Relationship* nextTRelationshipIfCallDupOne = new NextTRelationship(ifEntityDuplicate, callEntityDuplicate);

static Relationship* nextTRelationshipIfWhileOne = new NextTRelationship(ifEntity, whileEntity);
static Relationship* nextTRelationshipIfWhileDupOne = new NextTRelationship(ifEntityDuplicate, whileEntityDuplicate);

static Relationship* nextTRelationshipIfIfOne = new NextTRelationship(ifEntity, ifEntityTwo);
static Relationship* nextTRelationshipIfIfDupOne = new NextTRelationship(ifEntityDuplicate, ifEntityTwoDuplicate);

