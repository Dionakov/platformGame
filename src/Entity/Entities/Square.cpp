#include "Square.hpp"
#include <iostream>
#include "../../constants.hpp"

Square::Square(b2World const* world, b2Body* body) : WorldEntity(world, body), numFootContacts(0), contactLeft(false), contactRight(false) {
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
		
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(29.f/PPM, 40.f/PPM);
		
	fixtureDef.shape = &polygonShape;

	sq = body->CreateFixture(&fixtureDef);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0.f,10.f/PPM);
	circleShape.m_radius = 30.f/PPM;

	fixtureDef.shape = &circleShape;
	//circle = body->CreateFixture(&fixtureDef);

	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.f;
	fixtureDef.isSensor = true;

	polygonShape.SetAsBox(25.f/PPM, 2.f/PPM, b2Vec2(0.f, 39.f/PPM), 0);
	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef)->SetUserData((void*)"FootSensor");

	fixtureDef.isSensor = false;
	fixtureDef.friction = 300.f;
	polygonShape.SetAsBox(1.f/PPM, 38.f/PPM, b2Vec2(-28.f/PPM, 0.f), 0);
	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef)->SetUserData((void*)"LeftSquareSide");

	polygonShape.SetAsBox(1.f/PPM, 38.f/PPM, b2Vec2(28.f/PPM,0.f), 0);
	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef)->SetUserData((void*)"RightSquareSide");

	body->SetTransform(b2Vec2(300.f/PPM, 300.f/PPM), 0);

	sf::RectangleShape* s = new sf::RectangleShape(sf::Vector2f(60.f,80.f));
	s->setFillColor(sf::Color::Black);
	s->setOrigin(30.f,40.f);

	this->graphicalElement = reinterpret_cast<GraphicalElement*>(s);

	this->body->SetUserData((void*)this);
}

b2BodyDef Square::getBodyDef(void) {

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	return bodyDef;
}

void Square::tick(void) {

		// keyboard movement
	if(numFootContacts > 0) { // on ground

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
			!contactLeft)
			body->SetLinearVelocity(b2Vec2(-600.f/PPM, body->GetLinearVelocity().y));
			
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) &&
				!contactRight)
			body->SetLinearVelocity(b2Vec2(600.f/PPM, body->GetLinearVelocity().y));
		else {
			body->SetLinearVelocity(b2Vec2(0.f, body->GetLinearVelocity().y));
			body->ApplyForceToCenter(b2Vec2(0.f,-500.f),true);
		}
	}

	else { // jumping or falling

		if(contactLeft || contactRight)
			body->ApplyForceToCenter(b2Vec2(0.f,-60.f*body->GetMass()), true);

		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x*0.98f, body->GetLinearVelocity().y));

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !contactLeft)
			body->ApplyForceToCenter(b2Vec2(-80.f*body->GetMass(), 0), true);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !contactRight)
			body->ApplyForceToCenter(b2Vec2(80.f*body->GetMass(), 0), true);
	}

	this->updateGraphics();
}

void Square::onBeginContact(b2Contact* contact) {

	// TODO see if this can be done in a cleaner way

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	
	if(fixtureA->GetUserData() != 0) {

		std::string userData = static_cast<const char*>(fixtureA->GetUserData());

		if(userData == "FootSensor")
			numFootContacts++;
		else if(userData == "LeftSquareSide")
			contactLeft = true;
		else if(userData == "RightSquareSide")
			contactRight = true;
	}

	else if(fixtureB->GetUserData() != 0) {

		std::string userData = static_cast<const char*>(fixtureB->GetUserData());

		if(userData == "FootSensor")
			numFootContacts++;
		else if(userData == "LeftSquareSide")
			contactLeft = true;
		else if(userData == "RightSquareSide")
			contactRight = true;
	}
}

void Square::onEndContact(b2Contact* contact) {

	// TODO see if this can be done in a cleaner way

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	
	if(fixtureA->GetUserData() != 0) {

		std::string userData = static_cast<const char*>(fixtureA->GetUserData());

		if(userData == "FootSensor")
			numFootContacts--;
		else if(userData == "LeftSquareSide")
			contactLeft = false;
		else if(userData == "RightSquareSide")
			contactRight = false;
	}

	else if(fixtureB->GetUserData() != 0) {

		std::string userData = static_cast<const char*>(fixtureB->GetUserData());

		if(userData == "FootSensor")
			numFootContacts--;
		else if(userData == "LeftSquareSide")
			contactLeft = false;
		else if(userData == "RightSquareSide")
			contactRight = false;
	}
}

void Square::jump(void) {

	if(numFootContacts > 0)
		body->ApplyLinearImpulse(b2Vec2(0.f, -body->GetMass()*35), body->GetWorldCenter(), true);

	else if(contactLeft)
		body->ApplyLinearImpulse(b2Vec2(body->GetMass()*20, -body->GetMass()*35), body->GetWorldCenter(), true);

	else if(contactRight)
		body->ApplyLinearImpulse(b2Vec2(-body->GetMass()*20, -body->GetMass()*35), body->GetWorldCenter(), true);
}