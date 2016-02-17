/*!
 * \brief Represents a game element that has both a physical and a graphical existence.
 * \author Roch Dionnet
 */
#ifndef WORLDENTITY_HPP
#define WORLDENTITY_HPP

#include "PhysicalEntity.hpp"
#include "GraphicalEntity.hpp"
#include "../constants.hpp"

class WorldEntity : public virtual GraphicalEntity, public PhysicalEntity {

	public:
	/*!
	 * \brief Constructor.
	 * \param world
	 * \param body
	 * \see PhysicalEntity::world, PhysicalEntity::body
	 */
	WorldEntity(b2World const* world, b2Body* body) : PhysicalEntity(world, body), GraphicalEntity() {}

	protected:
	/*!
	 * \brief Update the graphics to match the physics in terms of transform.
	 */
	void matchGraphicsToPhysics(void);
};

#endif