#include "Animator.hpp"

void Animator::setCurrentAnimation(unsigned int currentAnimation) {

	if(currentAnimation < subRects.size()-1) {

		this->currentAnimation = currentAnimation;
		this->currentFrame = 0;
	}
}

void Animator::setCurrentFrame(unsigned int currentFrame) {

	if(currentFrame < subRects.at(currentAnimation).size()-1)
		this->currentFrame = (float)currentFrame;
}

void Animator::onTick(void) {

	if(!paused) {

		if(currentFrame < subRects.at(currentAnimation).size()-speed)
			currentFrame+=speed;
		else currentFrame = 0;
	}
}