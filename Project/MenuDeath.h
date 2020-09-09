#pragma once
#include "GUIElement.h"
#include "Text.h"
#include "ChangeLevelButton.h"


#ifndef MENUDEATH
#define MENUDEATH

class ResumeButton;
class GameManager;
class ChangeLevelButton;

class MenuDeath :public GUIElement {

	GameManager * game_manager;

	GUIElement * background;
	Text * menu_game_text;

	ChangeLevelButton * try_again;
	ChangeLevelButton * button_exit;

	float timer = 0;
	float time_to_end_death = 20.0;
	float time_to_show = 25.0;
	

public:

	MenuDeath(std::string _name, GameManager * game_manager);

	void start() override;

	void update() override;


};

#endif // !MENUDEATH




