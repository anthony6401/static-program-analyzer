#pragma once

#include "EntityObject.h"
#include "models/Relationship/Relationship.h"
#include "models/Relationship/UsesRelationship.h"
#include "models/Relationship/ModifyRelationship.h"

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
