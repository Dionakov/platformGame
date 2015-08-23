#include "BasicPlatform.hpp"
#include "../../constants.hpp"
#include "../../sfmlToBox2D.hpp"

BasicPlatform::BasicPlatform(b2World const* world, b2Body* body, b2Vec2 pos, b2Vec2 halfsize) : WorldEntity(world, body) {

	b2FixtureDef fixtureDef;
	fixtureDef.friction = 0.3f;
		
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(halfsize.x,halfsize.y);

	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef);

	body->SetTransform(b2Vec2(pos.x-halfsize.x,pos.y-halfsize.y), 0);


	sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(halfsize.x*PPM*2,halfsize.y*PPM*2));
	rect->setFillColor(sf::Color::Magenta);
	rect->setOrigin(physicalVecToGraphicalVec(halfsize));
	

	this->graphicalElement = reinterpret_cast<GraphicalElement*>(rect);

	this->body->SetUserData((void*)this);
}

b2BodyDef BasicPlatform::getBodyDef(void) {

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	return bodyDef;
}