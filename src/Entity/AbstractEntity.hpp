/*!
 * \brief Contains the AbstractEntity class declaration. 
 * \author Roch Dionnet
 */
#ifndef ABSTRACTENTITY_HPP
#define ABSTRACTENTITY_HPP

/*!
 * \brief Base class for game entities.
 */
class AbstractEntity {

	public:
	/*!
	 * \brief Default constructor.
	 */
	AbstractEntity(void) : dead(false) {}

	/*!
	 * \brief Runs a physical frame of the entity.
	 */
	virtual void tick(void) = 0;

	/*!
	 * \brief Destructor.
	 */
	virtual ~AbstractEntity(void) {}

	/*!
	 * \brief dead member variable getter.
	 * \return dead member variable.
	 * \see dead
	 */
	bool isDead(void) const { return dead; }

	protected:

	bool dead; /*!< Tells whether or not the entity is considered as dead. */
};

#endif