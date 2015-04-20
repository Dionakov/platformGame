/*!
 * \file main.cpp
 * \brief main file
 * \author Roch Dionnet
 */

/* TODO
 * !!! fix erase body bug !!!
 * think about graphical entities having multiple graphicalElements
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
#include <iterator>
#include <cmath>
#include "Entity/WorldEntity.hpp"
#include "Entity/EntityContactListener.hpp"
#include "Entity/Entities/Square.hpp"
#include "Entity/Entities/BasicPlatform.hpp"
#include "Entity/Entities/BoxBoundary.hpp"
#include "Entity/Entities/TrailBullet.hpp"
#include "constants.hpp"
#include "Level/AbstractLevel.hpp"
#include "Level/Levels/TestLevel.hpp"

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

	sf::View playerView(sf::Vector2f(400.f, 300.f), sf::Vector2f(1600.f, 1200.f));

	b2World world(b2Vec2(0.f, 98.2f));

	std::vector<AbstractLevel*> levels;
	levels.push_back(new TestLevel(world, window));

	int currentLevel = 0;

	levels.at(0)->initialize();

	while(window.isOpen()) {

		sf::Event e;
		while(window.pollEvent(e)) {
		
			if(e.type == sf::Event::Closed)
				window.close();
		}
		
		levels.at(currentLevel)->tick();

		window.clear(CLEARCOLOR);

		levels.at(currentLevel)->render();

		window.display();

		if(levels.at(currentLevel)->isFinished() && currentLevel < levels.size()) {

			currentLevel++;
			levels.at(currentLevel)->initialize();
		}
			
	}

	return EXIT_SUCCESS;
}