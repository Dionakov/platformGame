#ifndef WORLDENTITY_HPP
#define WORLDENTITY_HPP

#include "PhysicalEntity.hpp"
#include "GraphicalEntity.hpp"

/*!
 * \class WorldEntity WorldEntity.hpp
 * \brief represents a game element that has a physical and visual existence.
 */
class WorldEntity : public GraphicalEntity, public PhysicalEntity {

	public:
	WorldEntity(sf::RenderWindow const& window, b2World const* world, b2Body* body) : PhysicalEntity(world, body), GraphicalEntity(window) {}
	virtual void tick(void);

	protected:
	void updateGraphics(void);
};

#endif