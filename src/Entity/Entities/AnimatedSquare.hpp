// test file. TODO Delete when done.

#ifndef ANIMATEDSQUARE_HPP
#define ANIMATEDSQUARE_HPP

#include "../WorldEntity.hpp"
#include "../../Animation/Animator.hpp"

class AnimatedSquare : public WorldEntity {

	public:
	AnimatedSquare(b2World const* world, b2Body* body);

	static b2BodyDef getBodyDef(void);

	virtual void onBeginContact(b2Contact* contact);
	virtual void onEndContact(b2Contact* contact);
	virtual void tick(void);
	void impulseDown(void);

	std::string getInfo(void) const;

	void jump(void);
	
	protected:
	bool contactLeft;
	bool contactRight;
	bool contactBottomRight;
	bool contactBottomLeft;

	int numFootContacts;
	sf::Texture squareTexture;
	Animator animator;
};

#endif