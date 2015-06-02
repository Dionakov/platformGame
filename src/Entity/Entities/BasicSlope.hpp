#ifndef BASICSLOPE_HPP
#define BASICSLOPE_HPP

#include "../WorldEntity.hpp"

class BasicSlope : public WorldEntity {

	public:
	BasicSlope(b2World const* world, b2Body* body, b2Vec2 pos);
	static b2BodyDef getBodyDef(void);

	virtual void tick(void)
	{ this->updateGraphics(); }
};

#endif