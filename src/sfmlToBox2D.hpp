#ifndef SFMLTOBOX2D_HPP
#define SFMLTOBOX2D_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

sf::Vector2f physicalVecToGraphicalVec(b2Vec2 const& b2vec);

b2Vec2 graphicalVecToPhysicalVec(sf::Vector2f const& sfvec);
#endif