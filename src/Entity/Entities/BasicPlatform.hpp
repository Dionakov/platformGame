#ifndef BASICPLATFORM_HPP
#define BASICPLATFORM_HPP

#include "../WorldEntity.hpp"
#include <iostream>

class BasicPlatform : public WorldEntity {

	public:
		BasicPlatform(b2World const* world, b2Body* body, b2Vec2 pos, std::string str_texture = "resources/sprites/testTiles/barre.png");

	static b2BodyDef getBodyDef(void);

	virtual void tick(void)
	{ this->updateGraphics(); }

	private:
		sf::Texture texture;
		sf::Sprite sprite;

};

#endif