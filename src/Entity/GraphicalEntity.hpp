#ifndef GRAPHICALENTITY_HPP
#define GRAPHICALENTITY_HPP

#include "AbstractEntity.hpp"
#include <SFML/Graphics.hpp>

class GraphicalElement : public sf::Drawable, public sf::Transformable {
};

typedef enum Layer {

	FOREGROUND = 0,
	BACKGROUND = 10000
} Layer;

/*!
 * \class GraphicalEntity GraphicalEntity.hpp
 * \brief Represents a game element that can be displayed.
 */
class GraphicalEntity : public virtual AbstractEntity {

	public:
	GraphicalEntity(void) : AbstractEntity() {}
	virtual ~GraphicalEntity(void) {}
	GraphicalElement const* getGraphicalElement(void) const { return this->graphicalElement; }
	bool operator<(GraphicalEntity const& other) const { return this->layer < other.layer; } // TODO test this

	public:
	Layer layer;

	protected:
	GraphicalElement* graphicalElement;
};

#endif