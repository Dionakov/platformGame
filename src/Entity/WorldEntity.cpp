#include "WorldEntity.hpp"
#include "../constants.hpp"
#include "Animation/AnimatedSprite.hpp"

void WorldEntity::updateGraphics(void) {
	
	if(animated) {

		reinterpret_cast<AnimatedSprite*>(this->graphicalElement)->onGraphicsUpdate();
	}

	this->graphicalElement->setPosition(body->GetPosition().x*PPM, body->GetPosition().y*PPM);
	this->graphicalElement->setRotation(body->GetAngle() * 180.f / b2_pi);
}