/*!
 * \brief Contains the PhysicalEntity class declaration.
 * \author Roch Dionnet
 */
#ifndef PHYSICALENTITY_HPP
#define PHYSICALENTITY_HPP

#include <Box2D/Box2D.h>
#include "AbstractEntity.hpp"

/*!
 * \brief Represents a game element, physics-wise.
 */ 
class PhysicalEntity : public virtual AbstractEntity {

	public:
	/*!
	 * \brief Constructor.
	 * \param world
	 * \param body
	 * \see PhysicalEntity::world, PhysicalEntity::body
	 */
	PhysicalEntity(b2World const* world, b2Body* body) : AbstractEntity(), world(world), body(body) {}

	/*!
	 * \brief body member variable getter.
	 * \return The body member variable.
	 */
	b2Body* getBody(void) const { return this->body; } // not const. TODO See if there's a better way to do it.

	/*!
	 * \brief Contains what the entity should do when a contact begins.
	 * \param contact The contact information.
	 */
	virtual void onBeginContact(b2Contact* contact) {}

	/*!
	 * \brief Contains what the entity shoukd do when a contact ends.
	 * \param contact The contact information.
	 */
	virtual void onEndContact(b2Contact* contact) {}

	protected:
	b2Body* body; /*!< The physical body registered in world. */
	b2World const* world; /*!< The world that the physical body will interact with. */
};

#endif