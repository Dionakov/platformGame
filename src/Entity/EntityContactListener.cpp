#include "EntityContactListener.hpp"
#include "Entities/Square.hpp"

void EntityContactListener::BeginContact(b2Contact* contact) {

	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	
	if(fixtureA->GetUserData() != 0) {

		std::string userData = static_cast<const char*>(fixtureA->GetUserData());

		if(userData == "FootSensor")
			static_cast<Square*>(bodyA->GetUserData())->onFootSensorCollision(true);
		else if(userData == "LeftSquareSide")
			static_cast<Square*>(bodyA->GetUserData())->contactLeft = true;
		else if(userData == "RightSquareSide")
			static_cast<Square*>(bodyA->GetUserData())->contactRight = true;
	}

	else if(fixtureB->GetUserData() != 0) {

		std::string userData = static_cast<const char*>(fixtureB->GetUserData());

		if(userData == "FootSensor")
			static_cast<Square*>(bodyB->GetUserData())->onFootSensorCollision(true);
		else if(userData == "LeftSquareSide")
			static_cast<Square*>(bodyB->GetUserData())->contactLeft = true;
		else if(userData == "RightSquareSide")
			static_cast<Square*>(bodyB->GetUserData())->contactRight = true;
	}
}

void EntityContactListener::EndContact(b2Contact* contact) {

	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	
	if(fixtureA->GetUserData() != 0) {

		std::string userData = static_cast<const char*>(fixtureA->GetUserData());

		if(userData == "FootSensor")
			static_cast<Square*>(bodyA->GetUserData())->onFootSensorCollision(false);
		else if(userData == "LeftSquareSide")
			static_cast<Square*>(bodyA->GetUserData())->contactLeft = false;
		else if(userData == "RightSquareSide")
			static_cast<Square*>(bodyA->GetUserData())->contactRight = false;
	}

	else if(fixtureB->GetUserData() != 0) {

		std::string userData = static_cast<const char*>(fixtureB->GetUserData());

		if(userData == "FootSensor")
			static_cast<Square*>(bodyB->GetUserData())->onFootSensorCollision(false);
		else if(userData == "LeftSquareSide")
			static_cast<Square*>(bodyB->GetUserData())->contactLeft = false;
		else if(userData == "RightSquareSide")
			static_cast<Square*>(bodyB->GetUserData())->contactRight = false;
	}
}