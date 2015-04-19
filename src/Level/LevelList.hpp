#ifndef LEVELLIST_HPP
#define LEVELLIST_HPP

#include <map>
#include <vector>
#include <Box2D/Box2D.h>
#include "../Entity/AbstractEntity.hpp"

class LevelList {

	protected:
	typedef std::map<AbstractEntity*, b2Transform> Level;
	typedef std::vector<Level> LevelVector;

	public:

};

#endif