#ifndef ENTITYCONTACTLISTENER_HPP
#define ENTITYCONTACTLISTENER_HPP

#include <Box2D/Box2D.h>

class EntityContactListener : public b2ContactListener {

	public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

#endif