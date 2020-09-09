#include <SFML/Graphics.hpp>
#include <iostream>
#include "Log.h"
#include "Singleton.h"
#include "Logger.h"
#include "GameManager.h"

typedef Singleton<Logger> sLogger;

int main(int argc, char** argv)
{

	Singleton<Logger>::instance()->add({ "_main" , "Function main..." });

	GameManager gameManager;
	
	gameManager.start();

	if (!Singleton<Logger>::instance()->saveToFile()){
		std::cout << "Error saving log file!" << std::endl;
	}else {
		std::cout << "Save log file!" << std::endl;
	}

	return 0;
}