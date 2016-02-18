#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

typedef std::vector<std::vector<sf::IntRect>> AnimationsRects;

class Animator {

	public:
	Animator() : currentAnimation(0), currentFrame(0) {}
	void setSubRects(AnimationsRects subRects) { this->subRects = subRects; }
	void setCurrentAnimation(unsigned int currentAnimation) {

		if(currentAnimation < subRects.size()-1) {

			this->currentAnimation = currentAnimation;
			this->currentFrame = 0;
		}
	}

	void setCurrentFrame(unsigned int currentFrame) {

		if(currentFrame < subRects.at(currentAnimation).size()-1)
			this->currentFrame = currentFrame;

	}
	void onTick(void) {

		if(currentFrame < subRects.at(currentAnimation).size()-1)
			currentFrame++;
		else currentFrame = 0;
	}

	sf::IntRect getCurrentTextureRect(void) const {
		return subRects.at(currentAnimation).at(currentFrame);
	}
	protected:
	AnimationsRects subRects;
	int currentAnimation;
	int currentFrame;
};

#endif