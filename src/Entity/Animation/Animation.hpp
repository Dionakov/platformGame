#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>

typedef std::vector<sf::IntRect> IntRectList;

class Animation {

	public:
    Animation(IntRectList subRectangles);
	void setSpeed(int speed);
	int getSpeed(void) const { return speed; }
	void nextFrame(void);
	void previousFrame(void);
	void pause(void);
	void start(void);
	void stop(void);
	sf::IntRect getCurrentFrame(void) const { return subRectangles.at(currentFrame); }

	protected:
	bool paused;
	int speed;
	int currentFrame;
	IntRectList subRectangles;
};

#endif