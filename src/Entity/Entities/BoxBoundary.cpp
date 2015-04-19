#include "BoxBoundary.hpp"
#include <cmath>

b2BodyDef BoxBoundary::getBodyDef(void) {

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	return bodyDef;
}

void BoxBoundary::set(b2Vec2 pos, b2Vec2 size) {

	b2FixtureDef fixtureDef;
	fixtureDef.friction = 0.3f;

	b2Vec2 vertices[5] = {
		b2Vec2(0.f,0.f),
		b2Vec2(size.x*(31.f/30.f),0.f),
		b2Vec2(size.x*(31.f/30.f),size.y*(31.f/30.f)),
		b2Vec2(0.f,size.y*(31.f/30.f)),
		b2Vec2(0.f,0.f)
	};

	b2ChainShape chainShape;
	chainShape.CreateChain(vertices, 5);

	fixtureDef.shape = &chainShape;

	body->CreateFixture(&fixtureDef);
	body->SetTransform(pos, 0);

	sf::RectangleShape* s = new sf::RectangleShape(sf::Vector2f(size.x*PPM*(31.f/30.f), size.y*PPM*(31.f/30.f)));
	s->setFillColor(sf::Color(255, 255, 255, 0));
	s->setOutlineThickness((size.x < size.y ? size.x : size.y)*PPM/30.f);
	s->setOutlineColor(sf::Color(40, 40, 40));

	this->graphicalElement = reinterpret_cast<GraphicalElement*>(s);

	this->layer = BACKGROUND;
}