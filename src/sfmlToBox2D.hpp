/*!
 * \brief Provides some function that convert Box2D units into SFML units and vice-versa.
 * \author Roch Dionnet
 */
#ifndef SFMLTOBOX2D_HPP
#define SFMLTOBOX2D_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

/*!
 * \brief Converts an SFML Vector2f vector into a Box2D b2Vec2 vector.
 * \param b2vec The Vector2f vector to be converted.
 * \return The converted b2Vec2 vector.
 */
sf::Vector2f physicalVecToGraphicalVec(b2Vec2 const& b2vec);

/*!
 * \brief Converts an SFML Vector2f vector into a Box2D b2Vec2 vector.
 * \param sfvec The Vector2f vector to be converted.
 * \return The converted b2Vec2 vector.
 */
b2Vec2 graphicalVecToPhysicalVec(sf::Vector2f const& sfvec);
#endif