/*!
 * \file main.cpp
 * \brief main file
 * \author Roch Dionnet
 */

/* TODO
 * fix boxboundary bug
 * think about graphical entities having multiple drawables
 * finish code clean up
 * think about a way to integrate levels
 * think about gamestates
 */

#include <iostream>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <cmath>
#include "Entity/WorldEntity.hpp"
#include "Entity/EntityContactListener.hpp"
#include "Entity/Entities/Square.hpp"
#include "Entity/Entities/BasicPlatform.hpp"
#include "Entity/Entities/BoxBoundary.hpp"
#include "constants.hpp"

template<typename TNum>
std::string numToStr(TNum num) {

	std::stringstream out;
	out << num;
	return out.str();
}

/*!
 * \fn int main
 * \brief main function
 * 
 * \return EXIT_SUCCESS - The program exited successfully.
 * 
 * TODO write detailled description
 */
typedef std::vector<PhysicalEntity*> PhysicalEntityList;
typedef std::vector<GraphicalEntity*> GraphicalEntityList;

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "platformGame", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(36);
	window.setVerticalSyncEnabled(false);

	sf::View view(sf::Vector2f(400.f, 300.f), sf::Vector2f(1600.f, 1200.f));
	window.setView(view);

	GraphicalEntityList graphicalEntities;
	PhysicalEntityList physicalEntities;

	sf::Font font;
	sf::Text fpsText;
	font.loadFromFile("resources/fonts/AUGUSTUS.TTF");
	fpsText.setFont(font);
	fpsText.setString("xxx fps");
	fpsText.setCharacterSize(30);
	fpsText.setColor(sf::Color::Yellow);

	fpsText.setPosition(800-fpsText.getGlobalBounds().width - 20, 20);

	sf::Clock fpsClock;

	b2World world(b2Vec2(0.f, 98.2f));

	Square* sq = new Square(window, &world, world.CreateBody(&Square::getBodyDef()));
	graphicalEntities.push_back(sq);
	physicalEntities.push_back(sq);

	BoxBoundary* wb = new BoxBoundary(window, &world, world.CreateBody(&BoxBoundary::getBodyDef()));
	wb->set(b2Vec2(0,0), b2Vec2(1300/PPM,1000/PPM));
	graphicalEntities.push_back(wb);
	physicalEntities.push_back(wb);

	BasicPlatform* platform2 = new BasicPlatform(window, &world, world.CreateBody(&BasicPlatform::getBodyDef()), b2Vec2(500.f/PPM, 200.f/PPM));
	graphicalEntities.push_back(platform2);
	physicalEntities.push_back(platform2);

	EntityContactListener cl;
	world.SetContactListener(&cl);

	while(window.isOpen()) {

		float framerate = 1.f/fpsClock.restart().asSeconds();

		sf::Event e;
		while(window.pollEvent(e)) {

			if(e.type == sf::Event::Closed)
				window.close();

			else if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space)
				sq->jump();

			else if(e.type == sf::Event::MouseButtonPressed) {

				sf::Vector2f sfmousePos = window.mapPixelToCoords(sf::Vector2i(e.mouseButton.x, e.mouseButton.y), view);
				b2Vec2 mousePos = b2Vec2(sfmousePos.x/PPM, sfmousePos.y/PPM);
				BasicPlatform* platform = new BasicPlatform(window, &world, world.CreateBody(&BasicPlatform::getBodyDef()), mousePos);
				graphicalEntities.push_back(platform);
				physicalEntities.push_back(platform);
			}
		}

		fpsText.setString(sf::String(numToStr(floorf(framerate+0.5f))+" fps"));

		view.setCenter(sq->getDrawable()->getPosition());
		window.setView(view);

		std::sort(graphicalEntities.begin(), graphicalEntities.end());

		for(PhysicalEntityList::iterator it = physicalEntities.begin(); it != physicalEntities.end(); it++)
			(*it)->tick();
		
		world.Step(1.f/framerate, 6, 2);
		window.clear(CLEARCOLOR);
		for(GraphicalEntityList::iterator it = graphicalEntities.begin(); it != graphicalEntities.end(); it++)
			window.draw(*(*it)->getDrawable());

		// hud
		window.setView(window.getDefaultView());

		window.draw(fpsText);

		window.display();
	}
	return EXIT_SUCCESS;
}