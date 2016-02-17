#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>

typedef AnimationsRects std::vector<std::vector<sf::IntRect>>;

class Animator {

	public:
	Animator() : currentAnimation(0), currentFrame(0) {}
	void setSubRects(AnimationsRects subRects) { this.subRects = subRects; }
	void setCurrentAnimation(unsigned int currentAnimation) {

		if(currentAnimation < subRects.size())
			this.currentAnimation = currentAnimation;
	}

	void setCurrentFrame(unsigned int currentFrame) {

		if(currentFrame < subRects.at(currentAnimation).size())
			this.currentFrame = currentFrame;

	}
	protected:
	AnimationsRects subRects;
	int currentAnimation;
	int currentFrame;
}

#endif