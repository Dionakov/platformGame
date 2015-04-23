#include "TestLevel.hpp"
#include "../../Entity/Entities/BasicPlatform.hpp"
#include "../../Entity/Entities/Square.hpp"
#include "../../constants.hpp"
#include "../../sfmlToBox2D.hpp"
#include "../../Entity/EntityContactListener.hpp"

TestLevel::TestLevel(b2World& world, sf::RenderWindow& window) : AbstractLevel(world, window) {

	world.SetContactListener(new EntityContactListener);
}

void TestLevel::initialize(void) {

	BasicPlatform* platform = new BasicPlatform(&world, world.CreateBody(&BasicPlatform::getBodyDef()), b2Vec2(5.f, 30.f));
	physicalEntities.push_back(platform);
	graphicalEntities.push_back(platform);	

	player = new Square(&world, world.CreateBody(&Square::getBodyDef()));
	physicalEntities.push_back(player);
	graphicalEntities.push_back(player);
}

void TestLevel::tick(void) { 

	for(PhysicalEntityList::iterator it = physicalEntities.begin(); it != physicalEntities.end(); it++)
		(*it)->tick();

	world.Step(1.f/60.f, 6, 2);
}

void TestLevel::render(void) {

	AbstractLevel::render();

	window.setView(sf::View(physicalVecToGraphicalVec(player->getBody()->GetPosition()), sf::Vector2f(1600.f,1200.f)));
}

bool TestLevel::isFinished(void) {

	return false;
}