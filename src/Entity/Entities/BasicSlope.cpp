#include "BasicSlope.hpp"
#include "../../constants.hpp"

BasicSlope::BasicSlope(b2World const* world, b2Body* body, b2Vec2 pos) : WorldEntity(world, body) {

	b2FixtureDef fixtureDef;
	fixtureDef.friction = 0.3f;

	b2Vec2 vertices[3] = {
		b2Vec2(0.f,0.f),
		b2Vec2(460.f/PPM,0.f),
		b2Vec2(460.f/PPM,-190.f/PPM)
	};

	b2PolygonShape polygonShape;
	polygonShape.Set(vertices, 3);
	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef);
	body->SetTransform(pos, 0);

	sf::ConvexShape* c = new sf::ConvexShape(3);
	c->setPoint(0, sf::Vector2f(0.f,0.f));
	c->setPoint(1, sf::Vector2f(460.f,0.f));
	c->setPoint(2, sf::Vector2f(460.f,-190.f));

	c->setFillColor(sf::Color(110,110,110));
	this->graphicalElement = reinterpret_cast<GraphicalElement*>(c);
	this->body->SetUserData((void*)this);
}

b2BodyDef BasicSlope::getBodyDef(void) {

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	return bodyDef;
}