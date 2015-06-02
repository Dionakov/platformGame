#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "../WorldEntity.hpp"

class Circle : public WorldEntity {

	public:
	Circle(b2World const* world, b2Body* body);

	static b2BodyDef getBodyDef(void);

	virtual void tick(void);
	
};

#endif