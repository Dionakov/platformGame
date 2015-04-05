#include "Square.hpp"
#include <iostream>
#include "../../constants.hpp"

Square::Square(sf::RenderWindow const& window, 
			   b2World const* world, 
			   b2Body* body)
			   : WorldEntity(window, world, body),
			   numFootContacts(0),
			   contactLeft(false),
			   contactRight(false)
{
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
		
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(29.f/PPM, 30.f/PPM);
		
	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef);

	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.f;
	fixtureDef.isSensor = true;

	polygonShape.SetAsBox(25.f/PPM, 2.f/PPM, b2Vec2(0.f, 29.f/PPM), 0);
	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef)->SetUserData((void*)"FootSensor");

	fixtureDef.isSensor = false;
	fixtureDef.friction = 300.f;
	polygonShape.SetAsBox(1.f/PPM, 28.f/PPM, b2Vec2(-28.f/PPM, 0.f), 0);
	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef)->SetUserData((void*)"LeftSquareSide");

	polygonShape.SetAsBox(1.f/PPM, 28.f/PPM, b2Vec2(28.f/PPM,0.f), 0);
	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef)->SetUserData((void*)"RightSquareSide");

	body->SetTransform(b2Vec2(300.f/PPM, 300.f/PPM), 0);

	sf::RectangleShape* s = new sf::RectangleShape(sf::Vector2f(60.f,60.f));
	s->setFillColor(sf::Color::Black);
	s->setOrigin(30.f,30.f);

	this->drawable = reinterpret_cast<GraphicalElement*>(s);

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
			body->SetLinearVelocity(b2Vec2(-500.f/PPM, body->GetLinearVelocity().y));
			
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) &&
				!contactRight)
			body->SetLinearVelocity(b2Vec2(500.f/PPM, body->GetLinearVelocity().y));
		else
			body->SetLinearVelocity(b2Vec2(0.f, body->GetLinearVelocity().y));
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

void Square::jump(void) {

	if(numFootContacts > 0)
		body->ApplyLinearImpulse(b2Vec2(0.f, -body->GetMass()*35), body->GetWorldCenter(), true);

	else if(contactLeft)
		body->ApplyLinearImpulse(b2Vec2(body->GetMass()*20, -body->GetMass()*35), body->GetWorldCenter(), true);

	else if(contactRight)
		body->ApplyLinearImpulse(b2Vec2(-body->GetMass()*20, -body->GetMass()*35), body->GetWorldCenter(), true);
}