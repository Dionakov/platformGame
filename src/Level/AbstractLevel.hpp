/*!
 * \brief Contains the AbstractLevel class declaration. 
 * \author Roch Dionnet
 */
#ifndef ABSTRACTLEVEL_HPP
#define ABSTRACTLEVEL_HPP

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "../Entity/GraphicalEntity.hpp"
#include "../Entity/PhysicalEntity.hpp"

typedef std::vector<GraphicalEntity*> GraphicalEntityList;
typedef std::vector<PhysicalEntity*> PhysicalEntityList;

/*!
 * \brief Represents a basic linear level, with an end condition.
 */
class AbstractLevel {

	public:
	/*!
	 * \brief Class Constructor.
	 * \param world
	 * \param window
	 * \see AbstractLevel::world, AbstractLevel::window
	 */
	AbstractLevel(b2World& world, sf::RenderWindow& window) : world(world), window(window) {}

	/*!
	 * \brief Initializes the level.
	 * Creates the entities and put them in the entity lists, among other things. 
	 */
	virtual void initialize(void) = 0;

	/*!
	 * \brief Game tick.
	 * Runs a physical frame of the level.
	 */
	virtual void tick(void) = 0;

	/*!
	 * \brief Render method.
	 * Renders the level on screen.
	 */
	virtual void render(void);

	/*!
	 * \brief Tells whether or not the level is finished.
	 * \return true if the level's end condition is met, else returns false.
	 */
	virtual bool isFinished(void) = 0;

	/*!
	 * \brief Handles an event caught by the window.
	 * \param e The event to handle.
	 */
	virtual void pollEvent(sf::Event e) {}

	protected:
	GraphicalEntityList graphicalEntities; /*!< Vector of graphical entities. */
	PhysicalEntityList physicalEntities; /*!< Vector of physical entities. */
	b2World& world; /*!< The physical world that the level takes place in. */
	sf::RenderWindow& window; /*!< The window that the level is rendered on. */
};

#endif