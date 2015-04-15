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
	virtual ~GraphicalEntity() {}
	GraphicalElement const* getDrawable(void) const { return this->drawable; }
	bool operator<(GraphicalEntity const& other) const { return this->layer < other.layer; } // TODO test this
	Layer getLayer(void) const { return this->layer; }

	public:
	Layer layer;

	protected:
	GraphicalElement* drawable;
};

#endif