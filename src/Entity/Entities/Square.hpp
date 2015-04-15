// test file. TODO Delete when done.

#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "../WorldEntity.hpp"

class Square : public WorldEntity {

	public:
	Square(b2World const* world, b2Body* body);

	static b2BodyDef getBodyDef(void);

	virtual void tick(void);
	virtual void onBeginContact(b2Contact* contact);
	virtual void onEndContact(b2Contact* contact);

	void jump(void);
	
	protected:
	bool contactLeft;
	bool contactRight;

	int numFootContacts;
};

#endif