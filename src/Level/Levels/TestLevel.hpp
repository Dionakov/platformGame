#ifndef TESTLEVEL_HPP
#define TESTLEVEL_HPP

#include "../AbstractLevel.hpp"
#include "../../Entity/Entities/Square.hpp"

class TestLevel : public AbstractLevel {

	public:
	TestLevel(b2World& world, sf::RenderWindow& window);
	virtual void initialize(void);
	virtual void tick(void);
	virtual void render(void);
	virtual bool isFinished(void);
	virtual void pollEvent(sf::Event e);

	protected:
	Square* player; 
	sf::Text fpsText;
	sf::Text playerInfoText;
	sf::Clock fpsClock;
};

#endif
