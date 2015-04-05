#ifndef BOXBOUNDARY_HPP
#define BOXBOUNDARY_HPP

#include "../PhysicalEntity.hpp"
#include "../../constants.hpp"

class BoxBoundary : public PhysicalEntity {

	public:
	BoxBoundary(b2World const* world, b2Body* body) : PhysicalEntity(world, body) {

		this->body->SetUserData((void*)"BoxBoundary");
	}

	static b2BodyDef getBodyDef(void);

	virtual void tick(void) {}

	void set(b2Vec2 pos, b2Vec2 size);
};

#endif