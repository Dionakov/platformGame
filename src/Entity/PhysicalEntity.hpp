#ifndef PHYSICALENTITY_HPP
#define PHYSICALENTITY_HPP

#include <Box2D/Box2D.h>
#include "AbstractEntity.hpp"

/*!
 * \class PhysicalEntity PhysicalEntity.hpp
 * \brief Represents a game element that doesn't need to be drawn but has a physical body
 */ 
class PhysicalEntity : public virtual AbstractEntity {

	public:
	PhysicalEntity(b2World const* world, b2Body* body) : AbstractEntity(), world(world), body(body) {}
	b2Body const* getBody(void) const { return this->body; }
	virtual void onBeginContact(b2Contact* contact) {}
	virtual void onEndContact(b2Contact* contact) {}

	protected:
	b2Body* body;
	b2World const* world;
};

#endif