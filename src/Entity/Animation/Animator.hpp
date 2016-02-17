/*!
 * \brief Manages a sprite's animations.
 * \author Roch Dionnet
 */
#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include <map>
#include <string>
#include "Animation.hpp"

typedef std::map<std::string, Animation*> AnimationList;

class Animator {

	public:
	Animator(AnimationList animations, std::string firstAnimation);
	void setCurrentAnimation(const std::string& animationKey);
	const Animation& getCurrentAnimation(void) const { return currentAnimation; };
	sf::IntRect getCurrentSubRect(void) const;
	void nextFrame(void);
	void previousFrame(void);
	void pause(void);
	void start(void);
	void stop(void);

	protected:
	Animation& currentAnimation;
	AnimationList animations;
};

#endif