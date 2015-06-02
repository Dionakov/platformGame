#include "Circle.hpp"
#include "../../constants.hpp"

Circle::Circle(b2World const* world, b2Body* body) : WorldEntity(world, body),numFootContacts(0), contactLeft(false), contactRight(false) {

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;

	b2CircleShape circleShape;
	circleShape.m_radius = 30.f/PPM;
	fixtureDef.shape = &circleShape;
	body->CreateFixture(&fixtureDef);

	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.f;
	fixtureDef.isSensor = true;

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(25.f/PPM, 2.f/PPM, b2Vec2(0.f, 14.f/PPM), 0);
	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef)->SetUserData((void*)"FootSensor");

	fixtureDef.isSensor = false;
	fixtureDef.friction = 300.f;
	polygonShape.SetAsBox(1.f/PPM, 48.f/PPM, b2Vec2(-28.f/PPM, -15.f), 0);
	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef)->SetUserData((void*)"LeftSquareSide");

	polygonShape.SetAsBox(1.f/PPM, 48.f/PPM, b2Vec2(28.f/PPM,-15.f), 0);
	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef)->SetUserData((void*)"RightSquareSide");

	body->SetTransform(b2Vec2(0.f,0.f),0.f);

	/*sf::CircleShape* c = new sf::CircleShape(30.f);
	c->setFillColor(sf::Color::Black);
	c->setOrigin(30.f,30.f);*/

	sf::Texture t;
	t.loadFromFile("resources/sprites/Tiles_32/separate png/tile_50.png");
	sf::Sprite* c = new sf::Sprite(t);
	c->setOrigin(16.f,16.f);

	this->graphicalElement = reinterpret_cast<GraphicalElement*>(c);
	this->body->SetUserData((void*)this);
}

void Circle::jump(void) {

	if(numFootContacts > 0)
		body->ApplyLinearImpulse(b2Vec2(0.f, -body->GetMass()*35), body->GetWorldCenter(), true);

	else if(contactLeft)
		body->ApplyLinearImpulse(b2Vec2(body->GetMass()*20, -body->GetMass()*35), body->GetWorldCenter(), true);

	else if(contactRight)
		body->ApplyLinearImpulse(b2Vec2(-body->GetMass()*20, -body->GetMass()*35), body->GetWorldCenter(), true);
}

void Circle::onBeginContact(b2Contact* contact) {

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

void Circle::onEndContact(b2Contact* contact) {

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

b2BodyDef Circle::getBodyDef(void) {

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	return bodyDef;
}

void Circle::tick() {
	this->updateGraphics();
}

