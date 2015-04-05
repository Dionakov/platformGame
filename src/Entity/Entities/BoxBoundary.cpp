#include "BoxBoundary.hpp"

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
		b2Vec2(size.x,0.f),
		b2Vec2(size.x,size.y),
		b2Vec2(0.f,size.y),
		b2Vec2(0.f,0.f)
	};

	b2ChainShape chainShape;
	chainShape.CreateChain(vertices, 5);

	fixtureDef.shape = &chainShape;

	body->CreateFixture(&fixtureDef);
	body->SetTransform(pos, 0);
}