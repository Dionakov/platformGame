/*!
 * \file main.cpp
 * \brief main file
 * \author Roch Dionnet
 */

/* TODO
 * !!! fix erase body bug !!!
 * think about graphical entities having multiple drawables
 * finish code clean up
 * think about a way to integrate levels
 * think about gamestates
 *
 * finish the TrailBullet prototype class
 * more generally, restructurate the code quickly before it goes unsustainable.
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
#include "Entity/Entities/TrailBullet.hpp"
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

	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "platformGame", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	window.setVerticalSyncEnabled(true);

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

	fpsText.setPosition(window.getSize().x-fpsText.getGlobalBounds().width - 10, 10);

	sf::Clock fpsClock;

	b2World world(b2Vec2(0.f, 98.2f));

	Square* sq = new Square(&world, world.CreateBody(&Square::getBodyDef()));
	graphicalEntities.push_back(sq);
	physicalEntities.push_back(sq);

	BoxBoundary* wb = new BoxBoundary(&world, world.CreateBody(&BoxBoundary::getBodyDef()));
	wb->set(b2Vec2(0,0), b2Vec2(2000/PPM,1000/PPM));
	graphicalEntities.push_back(wb);
	physicalEntities.push_back(wb);

	BasicPlatform* platform2 = new BasicPlatform(&world, world.CreateBody(&BasicPlatform::getBodyDef()), b2Vec2(500.f/PPM, 200.f/PPM));
	graphicalEntities.push_back(platform2);
	physicalEntities.push_back(platform2);

	world.SetContactListener(new EntityContactListener());

	while(window.isOpen()) {

		float framerate = 1.f/fpsClock.restart().asSeconds();

		sf::Event e;
		while(window.pollEvent(e)) {

			if(e.type == sf::Event::Closed)
				window.close();

			else if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space)
				sq->jump();

			else if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Left) {

				TrailBullet* b = new TrailBullet(&world, world.CreateBody(&TrailBullet::getBodyDef()), 
					b2Vec2(sq->getBody()->GetPosition().x-(50.f/PPM), sq->getBody()->GetPosition().y),false);
				graphicalEntities.push_back(b);
				physicalEntities.push_back(b);
			}

			else if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Right) {

				TrailBullet* b = new TrailBullet(&world, world.CreateBody(&TrailBullet::getBodyDef()), 
					b2Vec2(sq->getBody()->GetPosition().x+(50.f/PPM), sq->getBody()->GetPosition().y),true);
				graphicalEntities.push_back(b);
				physicalEntities.push_back(b);
			}

			else if(e.type == sf::Event::MouseButtonPressed) {

				sf::Vector2f sfmousePos = window.mapPixelToCoords(sf::Vector2i(e.mouseButton.x, e.mouseButton.y), view);
				b2Vec2 mousePos = b2Vec2(sfmousePos.x/PPM, sfmousePos.y/PPM);
				BasicPlatform* platform = new BasicPlatform(&world, world.CreateBody(&BasicPlatform::getBodyDef()), mousePos);
				graphicalEntities.push_back(platform);
				physicalEntities.push_back(platform);
			}
		}

		fpsText.setString(sf::String(numToStr(floorf(framerate+0.5f))+" fps"));

		view.setCenter(sq->getDrawable()->getPosition());
		window.setView(view);

		std::sort(graphicalEntities.begin(), graphicalEntities.end());

		for(PhysicalEntityList::iterator it = physicalEntities.begin(); it != physicalEntities.end();) {

			if((*it)->isDead())
				//(*it)->destroyBody();
				it = physicalEntities.erase(it);
			else {

				(*it)->tick();
				it++;
			}
		}

		world.Step(1.f/(framerate <= 30.f ? 30.f : (framerate>=300.f ? 300.f : framerate)), 6, 2);
		window.clear(CLEARCOLOR);
		for(GraphicalEntityList::iterator it = graphicalEntities.begin(); it != graphicalEntities.end();) {
			
			if((*it)->isDead())
				it = graphicalEntities.erase(it);
			else {

				window.draw(*(*it)->getDrawable());
				it++;
			}
		}

		// hud
		window.setView(window.getDefaultView());

		window.draw(fpsText);

		window.display();
	}

	return EXIT_SUCCESS;
}