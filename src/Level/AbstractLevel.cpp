#include "AbstractLevel.hpp"

void AbstractLevel::render(void) {

	for(GraphicalEntityList::iterator it = graphicalEntities.begin(); it != graphicalEntities.end(); it++)
		window.draw(static_cast<const sf::Drawable&>(*(*it)->getGraphicalElement()));
}