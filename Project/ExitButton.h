#pragma once
#include "Clickable.h"
#include "GameManager.h"

#ifndef EXITBUTTON
#define EXITBUTTON

class GameManager;

class ExitButton :public Clickable {

	GameManager & game_manager;

public:

	ExitButton(std::string _name, VectorInt _position, VectorInt _size, std::string texture_name, sf::Color color, sf::Color hover_color, GameManager & _game_manager);

	void onClick();

	void start();

};


#endif // !EXITBUTTON



