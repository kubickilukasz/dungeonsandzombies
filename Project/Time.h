#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>

#ifndef  TIME_
#define TIME_

class Time
{

	static sf::Clock clock;

	static float elapsed_time;

public:

	static float time_scale;

	static std::string getStringTime();

	static float getElapsedTime();

	static float getUnscaledElapsedTime();

	static void restartClock();


};


#endif // ! TIME_