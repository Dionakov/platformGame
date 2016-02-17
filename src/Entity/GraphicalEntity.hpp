/*!
 * \brief Contains the GraphicalEntity and GraphicalElement class declarations.
 * \author Roch Dionnet
 */
#ifndef GRAPHICALENTITY_HPP
#define GRAPHICALENTITY_HPP

#include "AbstractEntity.hpp"
#include <SFML/Graphics.hpp>

/*!
 * \brief This class is used to represent an element that is both transformable and drawable.
 * With polymorphism, it can be used as an SFML Sprite or an SFML Shape.
 */
class GraphicalElement : public sf::Drawable, public sf::Transformable {};

/*!
 * \brief Represents a game element that can be displayed.
 */
class GraphicalEntity : public virtual AbstractEntity {

	public:
	/*!
	 * \brief Default constructor.
	 */
	GraphicalEntity(bool animated = false) : AbstractEntity(), animated(animated) {}

	/*!
	 * \brief Virtual destructor.
	 */
	virtual ~GraphicalEntity(void) {}

	/*!
	 * \brief graphicalElement class variable getter.
	 * \return the graphicalElement class variable.
	 */
	GraphicalElement const* getGraphicalElement(void) const { return this->graphicalElement; }

	protected:
	GraphicalElement* graphicalElement; /*!< A pointer on the graphicalElement that can be displayed */
	bool animated; /*!< Tells if the graphical element is animated. */
};

#endif