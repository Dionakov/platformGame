#include "WorldEntity.hpp"

void WorldEntity::tick(void) {

	this->updateGraphics();
}

void WorldEntity::updateGraphics(void) {
	
	this->drawable->setPosition(body->GetPosition().x*30.F, body->GetPosition().y*30.f);
	this->drawable->setRotation(body->GetAngle() * 180.f / b2_pi);
}