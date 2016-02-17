#include <iostream>
#include <sstream>
#include "TestLevel.hpp"
#include "../../Entity/Entities/BasicPlatform.hpp"
#include "../../Entity/Entities/BasicSlope.hpp"
#include "../../Entity/Entities/Square.hpp"
#include "../../Entity/Entities/AnimatedSquare.hpp"
#include "../../Entity/Entities/BoxBoundary.hpp"
#include "../../constants.hpp"
#include "../../sfmlToBox2D.hpp"
#include "../../Entity/EntityContactListener.hpp"

TestLevel::TestLevel(b2World& world, sf::RenderWindow& window) : AbstractLevel(world, window) {

	world.SetContactListener(new EntityContactListener);
}

void TestLevel::initialize(void) {

	// empty arrays if level was reset
	for(PhysicalEntityList::iterator it = physicalEntities.begin(); it != physicalEntities.end(); it++)
		world.DestroyBody((*it)->getBody());

	physicalEntities.clear();
	graphicalEntities.clear();

	player = new AnimatedSquare(&world, world.CreateBody(&AnimatedSquare::getBodyDef()));
	physicalEntities.push_back(player);
	graphicalEntities.push_back(player);

	BasicPlatform* platforms[6];

	platforms[0] = new BasicPlatform(&world, world.CreateBody(&BasicPlatform::getBodyDef()), graphicalVecToPhysicalVec(sf::Vector2f(6.f,126.f)), graphicalVecToPhysicalVec(sf::Vector2f((274.f-6.f)/2,(480.f-126.f)/2)));
	platforms[1] = new BasicPlatform(&world, world.CreateBody(&BasicPlatform::getBodyDef()), graphicalVecToPhysicalVec(sf::Vector2f(520.f,136.f)), graphicalVecToPhysicalVec(sf::Vector2f((852.f-520.f)/2,(188.f-136.f)/2)));
	platforms[2] = new BasicPlatform(&world, world.CreateBody(&BasicPlatform::getBodyDef()), graphicalVecToPhysicalVec(sf::Vector2f(1254.f,14.f)), graphicalVecToPhysicalVec(sf::Vector2f((1600.f-1254.f)/2,(80.f-14.f)/2)));
	platforms[3] = new BasicPlatform(&world, world.CreateBody(&BasicPlatform::getBodyDef()), graphicalVecToPhysicalVec(sf::Vector2f(160.f,860.f)), graphicalVecToPhysicalVec(sf::Vector2f((700.f-160.f)/2,(930.f-860.f)/2)));
	platforms[4] = new BasicPlatform(&world, world.CreateBody(&BasicPlatform::getBodyDef()), graphicalVecToPhysicalVec(sf::Vector2f(990.f,466.f)), graphicalVecToPhysicalVec(sf::Vector2f((1056.f-990.f)/2,(600.f-466.f)/2)));
	platforms[5] = new BasicPlatform(&world, world.CreateBody(&BasicPlatform::getBodyDef()), graphicalVecToPhysicalVec(sf::Vector2f(1330.f,460.f)), graphicalVecToPhysicalVec(sf::Vector2f((1600.f-1330.f)/2,(850.f-460.f)/2)));

	for(unsigned int i(0); i < 6; i++) {

		physicalEntities.push_back(platforms[i]);
		graphicalEntities.push_back(platforms[i]);
	}

	sf::Font* font = new sf::Font;
	if(!font->loadFromFile("resources/fonts/calibri.ttf")) {

		std::cout << "Couldn't load font." << std::endl;
		return;
	}
	fpsText = sf::Text(sf::String("xxxxxx fps"), *font, 30U);

	fpsText.setPosition(window.getSize().x - fpsText.getGlobalBounds().width - 20.f, 20.f);
	fpsText.setColor(sf::Color::Yellow);
	fpsClock.restart();
	playerInfoText = sf::Text(sf::String(""), *font, 14U);
	playerInfoText.setColor(sf::Color::Blue);
}

void TestLevel::tick(void) { 

	for(PhysicalEntityList::iterator it = physicalEntities.begin(); it != physicalEntities.end(); it++)
		(*it)->tick();

	playerInfoText.setString(player->getInfo());
	playerInfoText.setPosition(sf::Vector2f(player->getBody()->GetPosition().x*PPM+40.f,player->getBody()->GetPosition().y*PPM+40.f));

	float framerate = 1.f/fpsClock.restart().asSeconds();

	world.Step(1.f/60.f, 6, 2);
	std::ostringstream ss;
	ss << framerate;
	fpsText.setString(ss.str()+" FPS");
}

void TestLevel::pollEvent(sf::Event e) {

	if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space)
		player->jump();

	else if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {

		BasicPlatform* platform = new BasicPlatform(&world, 
													world.CreateBody(&BasicPlatform::getBodyDef()), 
													graphicalVecToPhysicalVec(window.mapPixelToCoords(sf::Vector2i(e.mouseButton.x,e.mouseButton.y))));
		graphicalEntities.push_back(platform);
		physicalEntities.push_back(platform);
	}

	else if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Right) {

		BasicSlope* slope = new BasicSlope(&world,
										   world.CreateBody(&BasicSlope::getBodyDef()),
										   graphicalVecToPhysicalVec(window.mapPixelToCoords(sf::Vector2i(e.mouseButton.x,e.mouseButton.y))));
		graphicalEntities.push_back(slope);
		physicalEntities.push_back(slope);
	}

	else if(e.type==sf::Event::KeyPressed && e.key.code == sf::Keyboard::E)
		player->impulseDown();
}

void TestLevel::render(void) {

	AbstractLevel::render();
	
	window.draw(playerInfoText);
	window.setView(window.getDefaultView());
	window.draw(fpsText);

	window.setView(sf::View(physicalVecToGraphicalVec(player->getBody()->GetPosition()), sf::Vector2f(1600.f,1200.f)));
}

bool TestLevel::isFinished(void) {

	return player->getBody()->GetPosition().y > 100.f;
}