#ifndef ABSTRACTENTITY_HPP
#define ABSTRACTENTITY_HPP

/*!
 * \class AbstractEntity AbstractEntity.hpp
 * \brief Base class for game elements.
 */
class AbstractEntity {

	public:
	AbstractEntity(void) : dead(false) {}
	virtual void tick(void) = 0;
	virtual ~AbstractEntity() {}
	bool isDead(void) const { return dead; }

	protected:
	bool dead;
};

#endif