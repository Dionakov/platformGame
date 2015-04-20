#include "WorldEntity.hpp"

void WorldEntity::updateGraphics(void) {
	
	this->graphicalElement->setPosition(body->GetPosition().x*30.F, body->GetPosition().y*30.f);
	this->graphicalElement->setRotation(body->GetAngle() * 180.f / b2_pi);
}