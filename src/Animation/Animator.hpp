#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

typedef std::vector<std::vector<sf::IntRect>> AnimationsRects;

class Animator {

	public:
	Animator(float speed=1.0f) : currentAnimation(0), currentFrame(0.f), speed(speed) {}
	void setSubRects(AnimationsRects subRects) { this->subRects = subRects; }
	void setCurrentAnimation(unsigned int currentAnimation);

	void setCurrentFrame(unsigned int currentFrame);
	void onTick(void);

	sf::IntRect getCurrentTextureRect(void) const {
		return subRects.at(currentAnimation).at((int)currentFrame);
	}
	protected:
	AnimationsRects subRects;
	int currentAnimation;
	float currentFrame;
	float speed; // in frames per tick
};

#endif