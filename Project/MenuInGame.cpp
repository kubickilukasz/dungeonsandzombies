#include "MenuInGame.h"

MenuInGame::MenuInGame(std::string _name, GameManager * _game_manager)
	: GUIElement(_name, {0,0}, { 0,0 }, "_none", sf::Color(255, 255, 255, 255)), game_manager(_game_manager)
{}

void MenuInGame::start() {

	float mn_x = width_screen / 1920.0;
	float mn_y = height_screen / 1080.0;

	VectorInt _position = VectorInt(width_screen / 2 - 425 * mn_x, -20);

	background = createGUI(std::shared_ptr<GUIElement>(new GUIElement("_back_menu", _position, {(int)(850 * mn_x), height_screen},"back_menu" , sf::Color(255,255,255,255))));
	background->active = false;

	_position.y += 250 * mn_y;
	_position.x += 250 * mn_x;

	menu_game_text = dynamic_cast<Text*>(createGUI(std::shared_ptr<GUIElement>(new Text("_back_menu_title", _position, { (int)(24 * mn_x), 0 }, "back_menu", sf::Color(255, 255, 255, 255), "MENU GAME"))));
	menu_game_text->active = false;
	
	_position.y += 100 * mn_y;
	_position.x -= 50 * mn_x;

	button_resume = dynamic_cast<ResumeButton*>(createGUI(std::shared_ptr<GUIElement>(new ResumeButton("_back_menu", _position, { (int)(350 * mn_x) , (int)(150 * mn_y) }, "button"
												, sf::Color(255, 255, 255, 255), sf::Color(120, 120, 120, 255), *this))));
	button_resume->active = false;

	_position.y += 160 * mn_y;

	button_new_game = dynamic_cast<ChangeLevelButton*>(createGUI(std::shared_ptr<GUIElement>(new ChangeLevelButton("_menu", _position, { (int)(350 * mn_x) , (int)(150 * mn_y) }, "button"
		, sf::Color(255, 255, 255, 255), sf::Color(120, 120, 120, 255), *game_manager, 1, "RESTART"))));
	button_new_game->active = false;
	button_new_game->text->active = false;

	_position.y += 160 * mn_y;

	button_exit = dynamic_cast<ChangeLevelButton*>(createGUI(std::shared_ptr<GUIElement>(new ChangeLevelButton("_menu", _position, { (int)(350 * mn_x) , (int)(150 * mn_y) }, "button"
												, sf::Color(255, 255, 255, 255), sf::Color(120, 120, 120, 255), *game_manager, 0, "BACK TO MENU"))));
	button_exit->active = false;
	button_exit->text->active = false;

	SInputManager::instance()->blockEscape(false);

}

void MenuInGame::update() {

	if (SInputManager::instance()->getEscape()) {
		if (!is_downed) {
			is_open = !is_open;
			is_downed = true;

			if (is_open) {
				activing();
			}
			else {
				unactiving();
			}
		}
	}else {
		is_downed = false;
	}
}

void MenuInGame::unactiving() {
	Time::time_scale = 1;
	background->active = false;
	menu_game_text->active = false;
	button_resume->active = false;
	button_resume->text->active = false;
	button_new_game->active = false;
	button_new_game->text->active = false;
	button_exit->active = false;
	button_exit->text->active = false;
	is_open = false;

}

void MenuInGame::activing() {
	Time::time_scale = 0;
	background->active = true;
	menu_game_text->active = true;
	button_resume->active = true;
	button_resume->text->active = true;
	button_new_game->active = true;
	button_new_game->text->active = true;
	button_exit->active = true;
	button_exit->text->active = true;
	is_open = true;

}
