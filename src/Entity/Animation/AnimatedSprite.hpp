#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Animator.hpp"

class AnimatedSprite : public sf::Sprite {

	public:
	AnimatedSprite(const sf::Texture &texture, Animator& animator);
	AnimatedSprite(Animator& animator);
	void onGraphicsUpdate(void);
	void setCurrentAnimation(std::string animationKey);

	protected:
	Animator& animator;
};

#endif