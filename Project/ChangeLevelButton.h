#pragma once
#include "Clickable.h"
#include "GameManager.h"

#ifndef  CHANGELEVELBUTTON
#define CHANGELEVELBUTTON

class GameManager;

class ChangeLevelButton :public Clickable {

	GameManager & game_manager;
	int id_level;
	std::string text_content;

public:

	ChangeLevelButton(std::string _name, VectorInt _position, VectorInt _size, std::string texture_name, sf::Color color, sf::Color hover_color, GameManager & _game_manager, const int _id_level, std::string content);

	void onClick();

	void start();


};

#endif
