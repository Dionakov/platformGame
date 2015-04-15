#ifndef TRAILBULLET_HPP
#define TRAILBULLET_HPP

#include "../WorldEntity.hpp"

class TrailBullet : public WorldEntity {

	public:
	TrailBullet(b2World const* world, b2Body* body, b2Vec2 pos, bool directionIsRight);

	static b2BodyDef getBodyDef(void);

	virtual void tick(void);
	virtual void onBeginContact(b2Contact* contact);
	//isOutOfBounds ?

	protected:
	bool directionIsRight;
	float startX;
};

#endif