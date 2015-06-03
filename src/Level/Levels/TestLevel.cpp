#include <iostream>
#include <sstream>
#include "TestLevel.hpp"
#include "../../Entity/Entities/BasicPlatform.hpp"
#include "../../Entity/Entities/BasicSlope.hpp"
#include "../../Entity/Entities/Square.hpp"
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

	//Chargement niveau
	sf::Image bitmap;
	if(!bitmap.loadFromFile("resources/levels/niveau.png"));
		std::cout << "Erreur resources/levels/niveau.png" << std::endl;

	for(int i = 0; i < bitmap.getSize().x; i++)
	{
		for(int j = 0; j < bitmap.getSize().y; j++)
		{
			sf::Color col = bitmap.getPixel(i, j);
			int val = col.r * pow(2, 16) + col.g * pow(2,8) + col.b;
			//std::cout << val << std::endl;
			if(val != 0)
			{
				float x = (i * 64) / PPM;
				float y = (j * 64) / PPM;

				BasicPlatform* platform = new BasicPlatform(&world, world.CreateBody(&BasicPlatform::getBodyDef()), b2Vec2(x, y), "resources/sprites/testTiles/" +  std::to_string(val) + ".png");
				physicalEntities.push_back(platform);
				graphicalEntities.push_back(platform);
			}
		}
	}




	for(unsigned int i = 0; i < 10; i++) {

		platform = new BasicPlatform(&world,world.CreateBody(&BasicPlatform::getBodyDef()),b2Vec2(5.f+(i*160.f/PPM),30.f));
		physicalEntities.push_back(platform);
		graphicalEntities.push_back(platform);
	}

	BoxBoundary* bb = new BoxBoundary(&world,world.CreateBody(&BoxBoundary::getBodyDef()));
	bb->set(b2Vec2(0.f,0.f),b2Vec2(2000.f/PPM,1300.f/PPM));
	physicalEntities.push_back(bb);
	graphicalEntities.push_back(bb);

	player = new Square(&world, world.CreateBody(&Square::getBodyDef()));
	physicalEntities.push_back(player);
	graphicalEntities.push_back(player);

<<<<<<< HEAD
=======


>>>>>>> 46dca4cfb7270d68c27469d9d17948bd4d411eca
	sf::Font* font = new sf::Font;
	if(!font->loadFromFile("resources/fonts/calibri.ttf")) {

		std::cout << "Couldn't load font." << std::endl;
		return;
	}
<<<<<<< HEAD
	fpsText = sf::Text(sf::String("xxxxxx fps"), *font, 30U);
=======
	fpsText = sf::Text(sf::String("xx fps"), *font, 50U);
>>>>>>> 46dca4cfb7270d68c27469d9d17948bd4d411eca
	fpsText.setPosition(window.getSize().x - fpsText.getGlobalBounds().width - 20.f, 20.f);
	fpsText.setColor(sf::Color::Yellow);
	fpsClock.restart();
}

void TestLevel::tick(void) { 

	for(PhysicalEntityList::iterator it = physicalEntities.begin(); it != physicalEntities.end(); it++)
		(*it)->tick();

	float framerate = 1.f/fpsClock.restart().asSeconds();

<<<<<<< HEAD
	world.Step(1.f/60.f, 6, 2);
=======
	world.Step(1.f/30.f, 6, 2);
>>>>>>> 46dca4cfb7270d68c27469d9d17948bd4d411eca
	std::ostringstream ss;
	ss << framerate;
	fpsText.setString(ss.str()+" fps");
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

}

void TestLevel::render(void) {

	AbstractLevel::render();
	window.setView(window.getDefaultView());
	window.draw(fpsText);

	window.setView(sf::View(physicalVecToGraphicalVec(player->getBody()->GetPosition()), sf::Vector2f(1600.f,1200.f)));
}

bool TestLevel::isFinished(void) {

	return player->getBody()->GetPosition().y > 100.f;
}