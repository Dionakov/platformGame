#ifndef ABSTRACTENTITY_HPP
#define ABSTRACTENTITY_HPP

/*!
 * \class AbstractEntity AbstractEntity.hpp
 * \brief Base class for game elements.
 */
class AbstractEntity {

	public:
	virtual void tick(void) = 0;
	virtual ~AbstractEntity() {};
};

#endif