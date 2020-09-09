#pragma once
#include "Clickable.h"
#include "MenuInGame.h"

#ifndef  RESUMEBUTTON
#define RESUMEBUTTON

class MenuInGame;

class ResumeButton :public Clickable{

	MenuInGame & menu_in_game;

public:

	ResumeButton(std::string _name, VectorInt _position, VectorInt _size, std::string texture_name, sf::Color color, sf::Color hover_color, MenuInGame & _menu_in_game);

	void onClick();

	void start();

	void update();

};

#endif

