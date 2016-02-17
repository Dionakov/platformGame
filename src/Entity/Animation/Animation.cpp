#include "Animation.hpp"

Animation::Animation(IntRectList subRectangles) : subRectangles(subRectangles), currentFrame(0), speed(1.f), paused(false) {}

void Animation::setSpeed(int speed) {

	if ((speed != 0) && !(speed & (speed - 1))) {

		this->speed = speed;
	}
}

void Animation::nextFrame(void) {

	if(!paused) {

		if(currentFrame == subRectangles.size())
			currentFrame = 0;
		else currentFrame++;
	}
}

void Animation::previousFrame(void) {

	if(!paused) {

		if(currentFrame == 0)
			currentFrame = subRectangles.size();
		else currentFrame--;
	}
}

void Animation::pause(void) { paused = true; }
void Animation::start(void) { paused = false; }
void Animation::stop(void) { paused = true; currentFrame = 0; }