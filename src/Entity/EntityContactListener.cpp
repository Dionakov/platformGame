#include "EntityContactListener.hpp"
#include "Entities/Square.hpp"

void EntityContactListener::BeginContact(b2Contact* contact) {

	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	if(bodyA->GetUserData())
		reinterpret_cast<PhysicalEntity*>(bodyA->GetUserData())->onBeginContact(contact);
	if(bodyB->GetUserData())
		reinterpret_cast<PhysicalEntity*>(bodyB->GetUserData())->onBeginContact(contact);
}

void EntityContactListener::EndContact(b2Contact* contact) {

	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	if(bodyA->GetUserData())
		reinterpret_cast<PhysicalEntity*>(bodyA->GetUserData())->onEndContact(contact);
	if(bodyB->GetUserData())
		reinterpret_cast<PhysicalEntity*>(bodyB->GetUserData())->onEndContact(contact);
}