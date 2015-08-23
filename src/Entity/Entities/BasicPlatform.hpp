#ifndef BASICPLATFORM_HPP
#define BASICPLATFORM_HPP

#include "../WorldEntity.hpp"
#include <iostream>
#include "../../sfmlToBox2D.hpp"

class BasicPlatform : public WorldEntity {

	public:
		BasicPlatform(b2World const* world, b2Body* body, b2Vec2 pos, b2Vec2 halfsize = graphicalVecToPhysicalVec(sf::Vector2f(256.f,32.f)));

	static b2BodyDef getBodyDef(void);

	virtual void tick(void) { this->updateGraphics(); }

	private:
		sf::Texture texture;
};

#endif