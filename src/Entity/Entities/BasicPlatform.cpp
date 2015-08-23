#include "BasicPlatform.hpp"
#include "../../constants.hpp"

BasicPlatform::BasicPlatform(b2World const* world, b2Body* body, b2Vec2 pos) : WorldEntity(world, body) {

	b2FixtureDef fixtureDef;
	fixtureDef.friction = 0.3f;
		
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(32.f/PPM, 32.f/PPM);

	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef);

	body->SetTransform(pos, 0);


	sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(64.f,64.f));
	rect->setFillColor(sf::Color::Magenta);
	rect->setOrigin(32, 32);
	

	this->graphicalElement = reinterpret_cast<GraphicalElement*>(rect);

	this->body->SetUserData((void*)this);
}

b2BodyDef BasicPlatform::getBodyDef(void) {

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	return bodyDef;
}