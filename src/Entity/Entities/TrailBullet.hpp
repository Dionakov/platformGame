#ifndef TRAILBULLET_HPP
#define TRAILBULLET_HPP

#include "../WorldEntity.hpp"

class TrailBullet : public WorldEntity {

	public:
	TrailBullet(sf::RenderWindow const& window,
		        b2World const* world,
				b2Body* body,
				b2Vec2 pos,
				bool directionIsRight);

	static b2BodyDef getBodyDef(void);

	virtual void tick(void);
	//isOutOfBounds ?

	protected:
	bool directionIsRight;
};

#endif