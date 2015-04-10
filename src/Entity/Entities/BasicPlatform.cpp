#include "BasicPlatform.hpp"
#include "../../constants.hpp"

BasicPlatform::BasicPlatform(sf::RenderWindow const& window, 
							 b2World const* world, 
							 b2Body* body, 
							 b2Vec2 pos)
							 : WorldEntity(window, world, body)
{
	b2FixtureDef fixtureDef;
	fixtureDef.friction = 0.3f;
		
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(160.f/PPM, 10.f/PPM);
		
	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef);
	body->SetTransform(pos, 0);

	sf::RectangleShape* s = new sf::RectangleShape(sf::Vector2f(320.f,20.f));
	s->setFillColor(sf::Color(110, 110, 110));
	s->setOrigin(160.f,10.f);

	this->drawable = reinterpret_cast<GraphicalElement*>(s);

	this->body->SetUserData((void*)this);
}

b2BodyDef BasicPlatform::getBodyDef(void) {

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	return bodyDef;
}