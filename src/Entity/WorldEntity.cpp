#include "WorldEntity.hpp"
#include "../constants.hpp"

void WorldEntity::updateGraphics(void) {
	
	this->graphicalElement->setPosition(body->GetPosition().x*PPM, body->GetPosition().y*PPM);
	this->graphicalElement->setRotation(body->GetAngle() * 180.f / b2_pi);
}