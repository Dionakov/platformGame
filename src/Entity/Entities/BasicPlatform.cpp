#include "BasicPlatform.hpp"
#include "../../constants.hpp"

BasicPlatform::BasicPlatform(b2World const* world, b2Body* body, b2Vec2 pos, std::string str_texture) : WorldEntity(world, body) {

	b2FixtureDef fixtureDef;
	fixtureDef.friction = 0.3f;
		
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(32.f/PPM, 32.f/PPM);

	fixtureDef.shape = &polygonShape;

	body->CreateFixture(&fixtureDef);

	body->SetTransform(pos, 0);


	if(!texture.loadFromFile(str_texture));
		std::cout << "Erreur" << std::endl;

	sprite.setTexture(texture);
	sprite.setOrigin(32, 32);
	

	this->graphicalElement = reinterpret_cast<GraphicalElement*>(&sprite);

	this->body->SetUserData((void*)this);
}

b2BodyDef BasicPlatform::getBodyDef(void) {

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	return bodyDef;
}