#include "Time.h"

 sf::Clock Time::clock = sf::Clock();
 float Time::elapsed_time = 0;
 float Time::time_scale = 1;

std::string Time::getStringTime() {

	std::time_t raw_time;
	struct std::tm  time_info;
	char buffer[80];

	std::time(&raw_time);
	localtime_s(&time_info, &raw_time);
	std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &time_info);

	return std::string(buffer);

	return "";
}

float Time::getElapsedTime() {
	return elapsed_time * time_scale;
}

float Time::getUnscaledElapsedTime() {
	return elapsed_time;
}

void Time::restartClock() {

	elapsed_time = (float)clock.getElapsedTime().asMicroseconds() / 100000;
	clock.restart();

}


