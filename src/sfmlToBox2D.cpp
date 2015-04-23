#include "sfmlToBox2D.hpp"
#include "constants.hpp"

sf::Vector2f physicalVecToGraphicalVec(b2Vec2 const& b2vec) {

	return sf::Vector2f(b2vec.x*PPM, b2vec.y*PPM);
}

b2Vec2 graphicalVecToPhysicalVec(sf::Vector2f const& sfvec) {

	return b2Vec2(sfvec.x/PPM, sfvec.y/PPM);
}