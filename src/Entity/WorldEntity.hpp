#ifndef WORLDENTITY_HPP
#define WORLDENTITY_HPP

#include "PhysicalEntity.hpp"
#include "GraphicalEntity.hpp"

/*!
 * \class WorldEntity WorldEntity.hpp
 * \brief represents a game element that has a physical and visual existence.
 */
class WorldEntity : public virtual GraphicalEntity, public PhysicalEntity {

	public:
	WorldEntity(b2World const* world, b2Body* body) : PhysicalEntity(world, body), GraphicalEntity() {}
	virtual void tick(void) = 0;

	protected:
	void updateGraphics(void);
};

#endif