/*!
 * \brief A contact listener for entities.
 * \author Roch Dionnet
 */
#ifndef ENTITYCONTACTLISTENER_HPP
#define ENTITYCONTACTLISTENER_HPP

#include <Box2D/Box2D.h>

class EntityContactListener : public b2ContactListener {

	public:
	/*!
	 * \brief Delegates beginContact management to the entity it is related to.
	 * \param contact The contact information.
	 */
	void BeginContact(b2Contact* contact);

	/*!
	 * \brief Delegates endContact management to the entity it is related to.
	 * \param contact The contact information.
	 */
	void EndContact(b2Contact* contact);
};

#endif