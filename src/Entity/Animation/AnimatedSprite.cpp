#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(Animator& animator) : animator(animator), sf::Sprite() {}
AnimatedSprite::AnimatedSprite(const sf::Texture &texture, Animator& animator) : animator(animator), sf::Sprite(texture) {}

void AnimatedSprite::onGraphicsUpdate(void) {

	this->setTextureRect(animator.getCurrentSubRect());
	this->animator.nextFrame();
}

void AnimatedSprite::setCurrentAnimation(std::string animationKey) { 

	animator.setCurrentAnimation(animationKey);
}