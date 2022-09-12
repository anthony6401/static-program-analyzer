#include "Relationship.h"


class ParentTRelationship : public Relationship {
public:
	ParentTRelationship(Entity* leftEntity, Entity* rightEntity);
};
