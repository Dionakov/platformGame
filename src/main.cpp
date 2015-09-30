/*!
 * \brief main file
 * \author Roch Dionnet
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
#include "sfmlToBox2D.hpp"
#include "Level/AbstractLevel.hpp"
#include "Level/Levels/TestLevel.hpp"

template<typename TNum>
/*!
 * \brief Converts a numerical value (int, float...) into an std::string.
 * \param num The numerical value.
 * \return The numerical value converted into an std::string.
 */
std::string numToStr(TNum num) {

	std::stringstream out;
	out << num;
	return out.str();
}

typedef std::vector<PhysicalEntity*> PhysicalEntityList;
typedef std::vector<GraphicalEntity*> GraphicalEntityList;

/*!
 * \brief Main function
 * 
 * \return EXIT_SUCCESS - The program exited successfully.
 * 
 * Entry point of the program. Contains the game loop, instanciates levels...
 */
int main() {

	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "platformGame", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);

	window.setVerticalSyncEnabled(true);

	sf::View playerView(sf::Vector2f(400.f, 300.f), sf::Vector2f(1600.f, 1200.f));

	b2World world(b2Vec2(0.f, 98.2f));

	std::vector<AbstractLevel*> levels;
	levels.push_back(new TestLevel(world, window));
	levels.push_back(new TestLevel(world, window));

	int currentLevel = 0;

	levels.at(0)->initialize();

	while(window.isOpen()) {

		sf::Event e;
		while(window.pollEvent(e)) {
		
			if(e.type == sf::Event::Closed)
				window.close();

			levels.at(currentLevel)->pollEvent(e);
		}
		
		levels.at(currentLevel)->tick();

		window.clear(CLEARCOLOR);

		levels.at(currentLevel)->render();

		window.display();

		/*if(levels.at(currentLevel)->isFinished() && currentLevel < levels.size()-1) {

			currentLevel++;
			levels.at(currentLevel)->initialize();
		}*/

		// looping on first level. Change that when done playing
		if(levels.at(currentLevel)->isFinished())
			levels.at(currentLevel)->initialize();
			
	}

	return EXIT_SUCCESS;
}