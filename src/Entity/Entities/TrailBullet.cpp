#include "TrailBullet.hpp"
#include "../../constants.hpp"

TrailBullet::TrailBullet(b2World const* world, b2Body* body, b2Vec2 pos, bool directionIsRight) 
	: WorldEntity(world, body), directionIsRight(directionIsRight), startX(pos.x)
{
	b2FixtureDef fixtureDef;
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(20.f/PPM, 3.f/PPM);
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);
	body->SetTransform(pos, 0);

	sf::RectangleShape* s = new sf::RectangleShape(sf::Vector2f(40.f,6.f));
	s->setFillColor(sf::Color::Yellow);
	s->setOrigin(20.f, 3.f);
	this->graphicalElement = reinterpret_cast<GraphicalElement*>(s);
	this->body->SetUserData(this);
}

void TrailBullet::tick(void) { 
	
	if(abs(body->GetPosition().x - startX)>=300.f/PPM)
		dead = true;
	
	// TODO fix this
	body->SetTransform(b2Vec2(body->GetPosition().x+(directionIsRight ? 1.f : -1.f), body->GetPosition().y), 0);
	this->matchGraphicsToPhysics(); 
}

b2BodyDef TrailBullet::getBodyDef(void) {

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	return bodyDef;
}

void TrailBullet::onBeginContact(b2Contact* contact) {

	dead = true;
}