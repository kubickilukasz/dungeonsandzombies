#pragma once
#include "GUIElement.h"
#include "Text.h"
#include "ResumeButton.h"
#include "ChangeLevelButton.h"


#ifndef  MENUINGAME
#define MENUINGAME

class ResumeButton;
class GameManager;
class ChangeLevelButton;

class MenuInGame :public GUIElement {

	bool is_open = false;
	bool is_downed = false;

	GameManager * game_manager;

	GUIElement * background;
	ResumeButton * button_resume;
	ChangeLevelButton * button_new_game;
	ChangeLevelButton * button_exit;
	Text * menu_game_text;



public:

	MenuInGame(std::string _name, GameManager * game_manager);

	void start();

	void update();

	void unactiving();

	void activing();

};


#endif // ! MENUINGAME
