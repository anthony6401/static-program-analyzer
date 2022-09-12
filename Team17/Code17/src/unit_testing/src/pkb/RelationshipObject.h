#pragma once

#include "EntityObject.h"
#include "models/Relationship/Relationship.h"
#include "models/Relationship/UsesRelationship.h"
#include "models/Relationship/ModifyRelationship.h"
#include "models/Relationship/ParentRelationship.h"
#include "models/Relationship/ParentTRelationship.h"

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
