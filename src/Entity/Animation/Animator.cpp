#include "Animator.hpp"
#include "Animation.hpp"

Animator::Animator(AnimationList animations, std::string firstAnimationKey) : animations(animations), currentAnimation(*(animations[firstAnimationKey])) {

}

void Animator::setCurrentAnimation(const std::string& animationKey) {

	if(animations.find(animationKey) != animations.end()) {

		currentAnimation = *(animations[animationKey]);
		currentAnimation.stop();
		currentAnimation.start();
	}
}

sf::IntRect Animator::getCurrentSubRect(void) const {

	return currentAnimation.getCurrentFrame();
}

void Animator::nextFrame(void) {

	currentAnimation.nextFrame();
}

void Animator::previousFrame(void) {

	currentAnimation.previousFrame();
}

void Animator::pause(void) { currentAnimation.pause(); }
void Animator::start(void) { currentAnimation.start(); }
void Animator::stop(void) { currentAnimation.stop(); }