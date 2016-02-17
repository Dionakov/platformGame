/*!
 * \brief A level used for testing.
 * \author Roch Dionnet
 */
#ifndef TESTLEVEL_HPP
#define TESTLEVEL_HPP

#include "../AbstractLevel.hpp"
#include "../../Entity/Entities/AnimatedSquare.hpp"

class TestLevel : public AbstractLevel {

	public:
	TestLevel(b2World& world, sf::RenderWindow& window);
	virtual void initialize(void);
	virtual void tick(void);
	virtual void render(void);
	virtual bool isFinished(void);
	virtual void pollEvent(sf::Event e);

	protected:
	AnimatedSquare* player; /*!< The rectangle-shaped player. */ 
	sf::Text fpsText; /*!< A text which shows the number of FPS. */
	sf::Text playerInfoText; /*!< A text which shows some info on the player. */
	sf::Clock fpsClock; /*!< A clock which is reset each frame, used to count the number of FPS. */
};

#endif
