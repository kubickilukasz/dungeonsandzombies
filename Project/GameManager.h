#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Singleton.h"
#include "Logger.h"
#include "Config.h"
#include "Level.h"
#include "Log.h"
#include "AssetManager.h"
#include "Time.h"
#include <iostream>

#ifndef GAMEMANAGER
#define GAMEMANAGER

class Level;

class GameManager {

private:

	sf::RenderWindow window;
	Level * current_level = nullptr;
	int id_level_to_clear;
	bool end_game = false;
	std::vector<Level> levels;


	void run();

	void createLevels();


public: 

	GameManager();

	//ustawia wszystkie dane okna
	void start();

	//tworzy instacje objektów
	void loadLevel(const int id_level);

	void endGame();


	~GameManager();


};

#endif
