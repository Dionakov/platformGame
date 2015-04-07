// test file. TODO Delete when done.

#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "../WorldEntity.hpp"

class Square : public WorldEntity {

	public:
	Square(sf::RenderWindow const& window,
		   b2World const* world,
		   b2Body* body);

	void onFootSensorCollision(bool beginContact)
	{ this->numFootContacts += beginContact ? 1 : -1; }

	static b2BodyDef getBodyDef(void);

	virtual void tick(void);

	void jump(float framerate);

	bool contactLeft;
	bool contactRight;

	protected:
	int numFootContacts;
};

#endif