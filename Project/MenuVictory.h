#pragma once
#include "GUIElement.h"
#include "Text.h"
#include "ChangeLevelButton.h"

#ifndef MENUVICTORY
#define MENUVICTORY

class MenuVictory :public GUIElement {

	GameManager * game_manager;

	GUIElement * background;
	Text * menu_game_text;
	Text * text_1;
	Text * text_2;

	ChangeLevelButton * button_exit;

	float timer = 0;
	float time_to_show = 25.0;


public:

	MenuVictory(std::string _name, GameManager * game_manager);

	void start() override;

	void update() override;

};

#endif // !MENUVICTORY



