#ifndef ABSTRACTLEVEL_HPP
#define ABSTRACTLEVEL_HPP

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "../Entity/GraphicalEntity.hpp"
#include "../Entity/PhysicalEntity.hpp"

typedef std::vector<GraphicalEntity*> GraphicalEntityList;
typedef std::vector<PhysicalEntity*> PhysicalEntityList;

class AbstractLevel {

	public:
	AbstractLevel(b2World& world, sf::RenderWindow& window) : world(world), window(window) {}
	virtual void initialize(void) = 0;
	virtual void tick(void) = 0;
	virtual void render(void);
	virtual bool isFinished(void) = 0;
	virtual void pollEvent(sf::Event e) {}

	protected:
	GraphicalEntityList graphicalEntities;
	PhysicalEntityList physicalEntities;
	b2World& world;
	sf::RenderWindow& window;
};

#endif